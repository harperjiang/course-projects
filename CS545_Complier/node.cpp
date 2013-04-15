/*
 * node.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: harper
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tr1/memory>
#include "node.h"
#include "exception.h"
#include "parser.h"

#define _TYPE_REAL 1
#define _TYPE_INT 2
#define _TYPE_BOOL 3
Type* TYPE_REAL = new BasicType(_TYPE_REAL);
Type* TYPE_INT = new BasicType(_TYPE_INT);
Type* TYPE_BOOL = new BasicType(_TYPE_BOOL);
std::tr1::shared_ptr<Type> TYPE_REAL_P = std::tr1::shared_ptr<Type>(TYPE_REAL);
std::tr1::shared_ptr<Type> TYPE_INT_P = std::tr1::shared_ptr<Type>(TYPE_INT);
std::tr1::shared_ptr<Type> TYPE_BOOL_P = std::tr1::shared_ptr<Type>(TYPE_BOOL);

#define _CALL_READ 1
#define _CALL_WRITE 2

std::tr1::shared_ptr<Type> get_type_pointer(Type* type) {
	if (type == TYPE_REAL)
		return TYPE_REAL_P;
	if (type == TYPE_INT)
		return TYPE_INT_P;
	if (type == TYPE_BOOL)
		return TYPE_BOOL_P;
	return std::tr1::shared_ptr<Type>(type);
}

template<class V>
void clearVector(V* avec) {
	for (typename V::iterator it = avec->begin(); it != avec->end(); ++it) {
		delete (*it);
	}
	avec->clear();
}

void Node::setloc(YYLTYPE loc) {
	if (this->loc == NULL) {
		this->loc = new YYLTYPE();
	}
	this->loc->first_column = loc.first_column;
	this->loc->first_line = loc.first_line;
	this->loc->last_column = loc.last_column;
	this->loc->last_line = loc.last_line;
}

void Node::setloc(YYLTYPE* from, YYLTYPE* to) {
	if (this->loc == NULL) {
		this->loc = new YYLTYPE();
	}
	this->loc->first_column = from->first_column;
	this->loc->first_line = from->first_line;
	this->loc->last_column = to->last_column;
	this->loc->last_line = to->last_line;
}

Routine::Routine(Identifier* id, std::vector<Declare*>* declares,
		std::vector<Subprogram*>* subs, StatementBlock* body) :
		Node() {
	this->id = id;
	this->declares = declares;
	this->subs = subs;
	this->body = body;

	this->declareTable = new std::map<char*, Declare*, comp>();
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		declareTable->insert(
				std::pair<char*, Declare*>((*ite)->name->name, *ite));
	}

	this->subTable = new std::map<char*, Subprogram*, comp>();
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		subTable->insert(
				std::pair<char*, Subprogram*>((*ite)->id->name, (*ite)));
	}

	this->actrecord = NULL;
}

Routine::~Routine() {
	delete id;

	delete actrecord;
	declareTable->clear();
	delete declareTable;

	clearVector(declares);
	delete declares;
	clearVector(subs);
	delete subs;
	delete body;
}

Declare* Routine::getDeclare(char* id) {
	if (declareTable->find(id) != declareTable->end()) {
		return declareTable->find(id)->second;
	}
	return NULL;
}

Subprogram* Routine::getSub(char* id) {
	if (subTable->find(id) != subTable->end()) {
		return subTable->find(id)->second;
	}
	return NULL;
}

Program::Program(Identifier* id, std::vector<Identifier*>* params,
		std::vector<Declare*>* declares, std::vector<Subprogram*>* subs,
		StatementBlock* body) :
		Routine(id, declares, subs, body) {
	this->params = params;

	this->actrecord = new ActivationRecord(true);
}

Program::~Program() {
	clearVector(params);
	delete params;
}

void Program::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[Program]", id->name);
	for (std::vector<Identifier*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	body->print(file, level + 1);
}

void Program::evaluate(EvalContext* context) {
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		context->addDeclare((*ite)->name->name, (*ite));
	}
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		context->addSub((*ite)->id->name, *ite);
	}
	// Evaluate Subprograms
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->evaluate(context);
	}
	// Evaluate body
	body->evaluate(context);
}

void Program::gencode(AsmContext* context) {
	context->access(this);
	// Gen data section
	context->section("data");
	context->label("intwrite");
	context->declare("string", "%d\\n");
	context->label("intread");
	context->declare("string", "%d");
	context->label("realwrite");
	context->declare("string", "%f\\n");
	context->label("realread");
	context->declare("string", "%f");

	// Gen text section
	context->header();

	// Handle activation record
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		actrecord->add(*ite);
	}

	// Generate procedure for subroutines
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->gencode(context);
	}
	// Program body starts here
	context->label("main");

	actrecord->gencode(context);
	body->gencode(context);
	// Clean activation record
	actrecord->genclean(context);

	// Gen exit code
	context->mov(eax, 1);
	context->mov(ebx, 0);
	context->interrupt(0x80);
	context->ret();
	// Gen tail code
	context->tail();
	context->done();

}

Subprogram::Subprogram(Identifier* id, std::vector<Param*>* params,
		std::vector<Declare*>* declares, std::vector<Subprogram*>* subs,
		StatementBlock* body) :
		Routine(id, declares, subs, body) {
	this->params = params;

	this->actrecord = new ActivationRecord(false);

	for (std::vector<Param*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		declareTable->insert(
				std::pair<char*, Declare*>((*ite)->name->name, *ite));
	}
}

Subprogram::~Subprogram() {
	clearVector(params);
	delete params;
}

void Subprogram::evaluate(EvalContext* context) {
	context->pushFrame(this);
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		context->addDeclare((*ite)->name->name, (*ite));
	}
	for (std::vector<Param*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		context->addDeclare((*ite)->name->name, (*ite));
	}
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		context->addSub((*ite)->id->name, (*ite));
	}
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->evaluate(context);
	}
	body->evaluate(context);
	context->popFrame();
}

Function::Function(Identifier* id, std::vector<Param*>* params, Type* rettype,
		std::vector<Declare*>* declares, std::vector<Subprogram*>* subs,
		StatementBlock* body) :
		Subprogram(id, params, declares, subs, body) {
	this->rettype = get_type_pointer(rettype);
	this->returnstmt = NULL;
	this->returnlabel = NULL;
}

Function::~Function() {
	rettype.reset();
	returnstmt = NULL;
	returnlabel = NULL;
}

Type* Function::getType() {
	return this->rettype.get();
}

void Function::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[Function]", id->name);
	rettype->print(file, level + 1);
	for (std::vector<Param*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	body->print(file, level + 1);
}

void Function::gencode(AsmContext* context) {
	context->access(this);
	returnlabel = context->genlabel();

	// Handle activation record
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		actrecord->add(*ite);
	}
	for (int i = params->size() - 1; i >= 0; i--) {
		actrecord->addparam(params->at(i));
	}

	// Generate procedure for subroutines
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->gencode(context);
	}
	// Generating code for this
	context->label(id->name);

	actrecord->gencode(context);
	body->gencode(context);

	context->label(returnlabel);
	actrecord->genclean(context);
	context->ret();

	context->done();
}

void Function::evaluate(EvalContext* context) {
	Subprogram::evaluate(context);
	if (!(getType()->equals(TYPE_INT) || getType()->equals(TYPE_REAL))) {
		context->record(error_type_mismatch(this));
	}
	if (returnstmt == NULL) {
		context->record(error_no_return(this));
	}
}

Procedure::Procedure(Identifier* id, std::vector<Param*>* params,
		std::vector<Declare*>* declares, std::vector<Subprogram*>* subs,
		StatementBlock* block) :
		Subprogram(id, params, declares, subs, block) {
}

Procedure::~Procedure() {
}

void Procedure::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[Procedure]", id->name);
	for (std::vector<Param*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
	body->print(file, level + 1);
}

void Procedure::gencode(AsmContext* context) {
	context->access(this);

	// Handle activation record
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		actrecord->add(*ite);
	}
	for (int i = params->size() - 1; i >= 0; i--) {
		actrecord->addparam(params->at(i));
	}

	// Generate procedure for subroutines
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->gencode(context);
	}
	// Generating code for this
	context->label(id->name);

	actrecord->gencode(context);
	body->gencode(context);
	actrecord->genclean(context);

	context->ret();

	context->done();
}

Declare::Declare(Type* t, Identifier* id) :
		Node() {
	this->name = id;
	this->type = get_type_pointer(t);
}

Declare::~Declare() {
	delete name;
	type.reset();
}

void Declare::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[Declare]");
	type.get()->print(file, level + 1);
	name->print(file, level + 1);
}

Type* Declare::getType() {
	return type.get();
}

Param::Param(Type* e, Identifier* id) :
		Declare(e, id) {
}

void Param::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[Param]");
	type.get()->print(file, level + 1);
	name->print(file, level + 1);
}

Type::Type() :
		Node() {

}

Type::~Type() {

}

BasicType::BasicType(int t) :
		Type() {
	type = t;
}

BasicType::~BasicType() {

}

void BasicType::print(FILE* file, int level) {
	Node::print(file, level);
	switch (this->type) {
	case _TYPE_INT:
		fprintf(file, "%s%s\n", "[Type]", "Int");
		break;
	case _TYPE_REAL:
		fprintf(file, "%s%s\n", "[Type]", "Real");
		break;
	case _TYPE_BOOL:
		fprintf(file, "%s%s\n", "[Type]", "Bool");
		break;
	default:
		return;
	}
}

const char* BasicType::description() {
	switch (this->type) {
	case _TYPE_INT:
		return "Int";
	case _TYPE_BOOL:
		return "Bool";
	case _TYPE_REAL:
		return "Real";
	default:
		throw ILLEGAL_TYPE;
	}
}

bool BasicType::equals(Type* t) {
	return this == t;
}

ArrayType::ArrayType(Type* t, int begin, int end) :
		Type() {
	this->basic = get_type_pointer(t);
	this->begin = begin;
	this->end = end;
	this->desc = new char[20 + strlen(t->description())];
	strcpy(desc, "Array of ");
	strcat(desc, t->description());
}

ArrayType::~ArrayType() {
	basic.reset();
	delete desc;
}

void ArrayType::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[ArrayType]");
	basic.get()->print(file, level + 1);
}

const char* ArrayType::description() {
	return desc;
}

Type* ArrayType::getBasic() {
	return basic.get();
}

bool ArrayType::equals(Type* another) {
	if (typeid(*another) == typeid(ArrayType)) {
		return getBasic()->equals(((ArrayType*) another)->getBasic());
	}
	return this == another;
}

IfStatement::IfStatement(Expression* cond, Statement* thenbody,
		Statement* elsebody) :
		Statement() {
	this->condition = cond;
	this->thenbody = thenbody;
	this->elsebody = elsebody;
}

IfStatement::~IfStatement() {
	delete this->condition;
	delete this->thenbody;
	delete this->elsebody;
}

void IfStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[IfStatement]");
	condition->print(file, level + 1);
	thenbody->print(file, level + 1);
	if (elsebody != NULL)
		elsebody->print(file, level + 1);
}

void IfStatement::evaluate(EvalContext* context) {
	condition->evaluate(context);
	// Condition must be boolean type
	if (!TYPE_BOOL->equals(condition->getType())) {
		context->record(error_type_mismatch(condition, TYPE_BOOL));
	}
	thenbody->evaluate(context);
	if (elsebody != NULL)
		elsebody->evaluate(context);
}

void IfStatement::gencode(AsmContext* context) {
	char* elselabel = context->genlabel();
	char* endlabel = context->genlabel();
	condition->gencode(context);
	context->cmp(eax, 1);
	context->jne(elselabel);
	thenbody->gencode(context);
	context->jmp(endlabel);
	context->label(elselabel);
	if (elsebody != NULL)
		elsebody->gencode(context);
	context->label(endlabel);
}

WhileStatement::WhileStatement(Expression* cond, Statement* body) :
		Statement() {
	this->condition = cond;
	this->body = body;
	this->endlabel = NULL;
}

WhileStatement::~WhileStatement() {
	delete condition;
	delete body;
	endlabel = NULL;
}

void WhileStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[WhileStatement]");
	condition->print(file, level + 1);
	body->print(file, level + 1);
}

void WhileStatement::evaluate(EvalContext* context) {
	condition->evaluate(context);
// Condition must be boolean type
	if (!TYPE_BOOL->equals(condition->getType())) {
		context->record(error_type_mismatch(condition, TYPE_BOOL));
	}
	body->evaluate(context);
}

void WhileStatement::gencode(AsmContext* context) {
	char* startlabel = context->genlabel();
	endlabel = context->genlabel();
	context->access(this);
	context->label(startlabel);
	condition->gencode(context);
	context->cmp(eax, 1);
	context->jne(endlabel);

	body->gencode(context);
	context->jmp(startlabel);
	context->label(endlabel);
	context->done();
}

ForStatement::ForStatement(Identifier* var, Expression* from, Expression* to,
		Statement* body) :
		Statement() {
	this->variable = var;
	this->from = from;
	this->to = to;
	this->body = body;
}

ForStatement::~ForStatement() {
	delete variable;
	delete from;
	delete to;
	delete body;
}

void ForStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[ForStatement]");
	variable->print(file, level + 1);
	from->print(file, level + 1);
	to->print(file, level + 1);
	body->print(file, level + 1);
}

void ForStatement::evaluate(EvalContext* context) {
	variable->evaluate(context);
	if (variable->getType() == NULL)
		return;
	if (variable->getType() != TYPE_INT) {
		context->record(::error_type_mismatch(variable, TYPE_INT));
	}
	from->evaluate(context);
	to->evaluate(context);
	if (from->getType() == NULL || to->getType() == NULL)
		return;
	if (from->getType() != TYPE_INT) {
		context->record(::error_type_mismatch(from, TYPE_INT));
	}
	if (to->getType() != TYPE_INT) {
		context->record(::error_type_mismatch(to, TYPE_INT));
	}
	body->evaluate(context);
}

void ForStatement::gencode(AsmContext* context) {
	char* begin = context->genlabel();
	char* end = context->genlabel();

	from->gencode(context);
	variable->genaddr(context);
	context->mov(edx, eax, 2);

	context->label(begin);
	to->gencode(context);
	variable->genaddr(context);
	context->mov(ebx, edx, 1);
	context->cmp(ebx, eax);
	context->jg(end);
	body->gencode(context);
	context->jmp(begin);
	context->label(end);
}

AssignStatement::AssignStatement(Variable* lval, Expression* rval) :
		Statement() {
	this->leftval = lval;
	this->rightval = rval;
	this->isreturn = false;
	this->function = NULL;
}

AssignStatement::~AssignStatement() {
	delete leftval;
	delete rightval;
	this->function = NULL;
}

void AssignStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[AssignStatement]");
	leftval->print(file, level + 1);
	rightval->print(file, level + 1);
}

void AssignStatement::evaluate(EvalContext* context) {
	Node* funcnode = context->findhistory(typeid(Function).name());
	rightval->evaluate(context);
	if (funcnode != NULL) {
		Function* function = (Function*) funcnode;
		if (typeid(*leftval) == typeid(Identifier)
				&& function->id->equals((Identifier*) leftval)) {
			// This is a return statement
			isreturn = true;
			this->function = function;
			function->returnstmt = this;
			if (!function->getType()->equals((rightval->getType()))) {
				context->record(
						error_type_mismatch(rightval, function->getType()));
			}
			return;
		} else {
			// an assignment in function, check whether it access non-local var
			leftval->evaluate(context);
			Declare* dec = leftval->getdeclare();
			if (NULL == function->getDeclare(dec->name->name)) {
				// Not a local var
				context->record(error_update_non_local(this));
			}
			return;
		}
	}
	// This is not an assignment in function
	isreturn = false;
	leftval->evaluate(context);
	// Variable may be undeclared
	if (leftval->getType() == NULL)
		return;
	if (!leftval->getType()->equals(rightval->getType())) {
		context->record(error_type_mismatch(leftval, rightval->getType()));
	}

}

void AssignStatement::gencode(AsmContext* context) {
	if (isreturn) {
		rightval->gencode(context);
		context->jmp(this->function->returnlabel);
	} else {
		rightval->gencode(context);
		if (TYPE_REAL->equals(rightval->getType())) {
			leftval->genaddr(context);
			context->fstp(edx, 0);
		} else {
			if (typeid(*leftval) != typeid(Identifier)) {
				context->push(eax);
			}
			leftval->genaddr(context);
			if (typeid(*leftval) != typeid(Identifier)) {
				context->pop(eax);
			}
			context->mov(edx, eax, 2);
		}
	}
}

StatementBlock::StatementBlock(std::vector<Statement*>* stmts) :
		Statement() {
	this->statements = stmts;
}

StatementBlock::~StatementBlock() {
	clearVector(this->statements);
}

void StatementBlock::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[StatementBlock]");
	for (std::vector<Statement*>::iterator ite = statements->begin();
			ite != statements->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
}

void StatementBlock::evaluate(EvalContext* context) {
	for (std::vector<Statement*>::iterator ite = statements->begin();
			ite != statements->end(); ite++) {
		(*ite)->evaluate(context);
	}
}

void StatementBlock::gencode(AsmContext* context) {
	// TODO Use quadruple
	for (std::vector<Statement*>::iterator ite = statements->begin();
			ite != statements->end(); ite++) {
		(*ite)->gencode(context);
	}
}

CallStatement::CallStatement(CallExpression* call) :
		Statement() {
	this->callexp = call;
}

CallStatement::~CallStatement() {
	delete callexp;
}

void CallStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[CallStatement]");
	callexp->print(file, level + 1);
}

void CallStatement::evaluate(EvalContext* context) {
	callexp->evaluate(context);
}

void CallStatement::gencode(AsmContext* context) {
	callexp->gencode(context);
}

BreakStatement::BreakStatement() :
		Statement() {
	parent = NULL;
}

BreakStatement::~BreakStatement() {
	parent = NULL;
}

void BreakStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[BreakStatement]");
}

void BreakStatement::evaluate(EvalContext* context) {
//  Check whether in a while loop
	Node* node = context->findhistory(typeid(WhileStatement).name());
	if (NULL != node) {
		parent = (WhileStatement*) node;
		return;
	}
	context->record(error_break_not_in_loop(this));
}

void BreakStatement::gencode(AsmContext* context) {
	context->jmp(parent->endlabel);
}

ReturnStatement::ReturnStatement(Expression* exp) :
		Statement() {
	this->retvalue = exp;
}

ReturnStatement::~ReturnStatement() {
	delete retvalue;
}

void ReturnStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[ReturnStatement]");
	if (NULL != retvalue)
		retvalue->print(file, level + 1);
}

void ReturnStatement::evaluate(EvalContext* context) {
	if (retvalue != NULL)
		retvalue->evaluate(context);
	Subprogram* current = context->getCurrent();
	Function* function = dynamic_cast<Function*>(current);
	if (NULL == function) { // Not a function, should not have return
		context->record(error_ret_in_proc(this));
	}
	if (retvalue != NULL && !function->getType()->equals(retvalue->getType())) {
		context->record(::error_type_mismatch(retvalue, function->getType()));
	}
}

void ReturnStatement::gencode(AsmContext* context) {
	if (retvalue != NULL) {
		retvalue->gencode(context);
	}
	// Return value already stored in eax
	context->ret();
}

CallExpression::CallExpression(Identifier* name,
		std::vector<Expression*>* params) :
		Expression() {
	this->callname = name;
	this->params = params;
	this->source = NULL;
}

CallExpression::~CallExpression() {
	delete callname;
	clearVector(params);
}

void CallExpression::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[CallExpression]", this->callname->name);
	for (std::vector<Expression*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
}

void CallExpression::evaluate(EvalContext* context) {
	Subprogram* sub = context->getSub(callname->name);
	if (sub != NULL) {
		source = sub;
	} else {
		context->record(error_no_sub(this));
		return;
	}
	if (sub->params->size() != this->params->size()) {
		context->record(error_arg_mismatch(this));
		return;
	}
	for (int i = 0; i < (int) sub->params->size(); i++) {
		Expression* realparam = this->params->at(i);
		Param* def = sub->params->at(i);
		realparam->evaluate(context);
		if (NULL == realparam->getType())
			continue;
		if (!realparam->getType()->equals(def->getType())) {
			context->record(error_type_mismatch(realparam, def->getType()));
		}
	}
}

Type * CallExpression::getType() {
	if (NULL == source || typeid(*source) == typeid(Procedure))
		return NULL;
	Function* function = (Function*) source;
	return function->rettype.get();
}

void CallExpression::gencode(AsmContext* context) {
	// Push parameters
	for (std::vector<Expression*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->gencode(context);

		if (TYPE_REAL->equals((*ite)->getType())) {
			context->sub(esp, 4);
			context->fstp(esp);
		} else {
			context->push(eax);
		}
	}

	// Stack Structure:

	// high_end
	// ....
	// params
	// base_callframe
	// ret_addr
	// old ebp
	//  <-----ebp
	// local_var

	// Find the caller & parent
	Routine* owner = NULL;
	Routine* parent = NULL;
	std::vector<Node*>* history = context->gethistory();
	for (int i = history->size() - 1; i >= 0; i--) {
		Node* n = history->at(i);
		if (typeid(*n) == typeid(Program) || typeid(*n) == typeid(Function)
				|| typeid(*n) == typeid(Procedure)) {
			if (owner == NULL) {
				owner = (Routine*) n;
			} else {
				parent = (Routine*) n;
				break;
			}
		}
	}
	// call type : 0:up->down 1:slibling 2:child->parent
	int calltype = 0;
	// Owner won't be null as we know there is a Program in history
	if (parent == NULL) {
		// start from main, up call down
		calltype = 0;
	} else if (NULL != owner->getSub(callname->name)) {
		calltype = 0;
	} else if (parent->getSub(callname->name) != NULL
			&& parent->getSub(owner->id->name) == owner) {
		calltype = 1;
	} else {
		calltype = 2;
	}

	switch (calltype) {
	case 2:
		//TODO dunno how to do this...
		break;
	case 1: // slibling, copy frame reference
		context->push(ebp, 8);
		break;
	case 0: // parent call child, child copy parent's frame reference
		context->push(ebp);
		break;
	default:
		break;
	}

	context->call(callname->name);
}

SysCall::SysCall(int type, std::vector<Expression*>* params) :
		CallExpression(NULL, params) {
	this->type = type;
}

SysCall::~SysCall() {

}

void SysCall::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[SysCall]", type == _CALL_READ ? "read" : "write");
	for (std::vector<Expression*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->print(file, level + 1);
	}
}

void SysCall::evaluate(EvalContext* context) {
	if (params->size() != 1) {
		context->record(error_arg_mismatch(this));
	}
	Expression* param = params->at(0);
	param->evaluate(context);
	if (param->getType() == NULL) {
		return;
	}
	if (param->getType() != TYPE_INT && param->getType() != TYPE_REAL) {
		context->record(error_type_mismatch(param, "int or real"));
	}
	if (type == _CALL_READ && typeid(*param) != typeid(Identifier)
			&& typeid(*param) != typeid(ArrayElement)) {
		context->record(error_arg_mismatch(this));
	}
}

Type * SysCall::getType() {
	return NULL;
}

void SysCall::gencode(AsmContext* context) {
	Expression* param = params->at(0);
	if (type == _CALL_READ) {
		Variable* var = (Variable*) param;
		// push the address
		var->genaddr(context);
		context->push(edx);
		// push the format
		if (TYPE_REAL->equals(param->getType())) {
			context->push("realread");
		} else {
			context->push("intread");
		}
		context->call("scanf");
	}
	if (type == _CALL_WRITE) {
		// Float need to be converted to double
		// push the value to print
		param->gencode(context);
		if (TYPE_REAL->equals(param->getType())) {
			context->sub(esp, 8);
			context->fstp(esp, 0, true);
			context->push("realwrite");
		} else {
			context->push(eax);
			context->push("intwrite");
		}
		context->call("printf");
	}
}

ArithExpression::ArithExpression(Expression* l, AOPR opr, Expression* r) :
		Expression() {
	this->left = l;
	this->opr = opr;
	this->right = r;
}

ArithExpression::~ArithExpression() {
	delete this->left;
	delete this->right;
}

void ArithExpression::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[ArithExpression]");
	if (left != NULL)
		left->print(file, level + 1);
	right->print(file, level + 1);
}

void ArithExpression::evaluate(EvalContext* context) {
	if (left != NULL)
		left->evaluate(context);
	right->evaluate(context);
	if (left != NULL) {
		if (left->getType() == NULL || right->getType() == NULL)
			return;
		if (!left->getType()->equals(right->getType())) {
			context->record(error_type_mismatch(this));
			return;
		}
		if (opr == _MOD && TYPE_REAL->equals(left->getType())) {
			context->record(error_type_mismatch(this, TYPE_INT));
		}
	}
}

Type * ArithExpression::getType() {
	return right->getType();
}

void ArithExpression::gencode(AsmContext* context) {
	if (TYPE_REAL->equals(right->getType())) {
		if (NULL != left) {
			left->gencode(context);// r1
		} else {
			context->fldz();
		}
		right->gencode(context); // r0
		switch (opr) {
		case _ADD:
			context->faddp();
			break;
		case _SUB:
			context->fsubp();
			break;
		case _MUL:
			context->fmulp();
			break;
		case _DIV:
			context->fdivp();
			break;
		default:		// No mod here
			break;
		}
	} else {
		right->gencode(context);
		context->push(eax);
		if (NULL != left) {
			left->gencode(context);
		} else {
			context->mov(eax, 0);
		}
		context->pop(ebx);
		switch (opr) {
		case _ADD:
			context->add(eax, ebx);
			break;
		case _SUB:
			context->sub(eax, ebx);
			break;
		case _MUL:
			context->mul(ebx);
			break;
		case _DIV:
			context->mov(edx, 0);
			context->div(ebx);
			break;
		case _MOD:
			context->mov(edx, 0);
			context->div(ebx);
			context->mov(eax, edx);
			break;
		default:
			break;
		}
	}
}

RelExpression::RelExpression(Expression* l, ROPR opr, Expression* r) :
		Expression() {
	this->left = l;
	this->opr = opr;
	this->right = r;
}

RelExpression::~RelExpression() {
	delete this->left;
	delete this->right;
}

void RelExpression::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[RelExpression]");

	left->print(file, level + 1);
	right->print(file, level + 1);
}

void RelExpression::evaluate(EvalContext* context) {
	left->evaluate(context);
	right->evaluate(context);
	if (left->getType() == NULL || right->getType() == NULL) {
		return;
	}
	if (!left->getType()->equals(right->getType())) {
		context->record(error_type_mismatch(this));
	}
	if (!TYPE_INT->equals(left->getType())
			&& !TYPE_REAL->equals(left->getType())) {
		context->record(::error_type_mismatch(this, "int or real"));
	}
}

Type * RelExpression::getType() {
	return TYPE_BOOL;
}

void RelExpression::gencode(AsmContext* context) {
	char* tlabel = context->genlabel();
	char* elabel = context->genlabel();
	if (TYPE_REAL->equals(left->getType())) {
		right->gencode(context); // ST1
		left->gencode(context); // ST0
		context->fcomip(1);
		context->ffree(0);
		// ZF-PF-CF
		// ST0 > ST1  000
		// ST0 < ST1  001
		// ST0 = ST1  100
		switch (opr) {
		case _EQ:
			// ZF = 0
			context->je(tlabel);
			break;
		case _NEQ:
			// ZF != 0
			context->jne(tlabel);
			break;
		case _GT:
			// ZF = 0 && PF = 0 && CF = 0
			context->ja(tlabel);
			break;
		case _GTE:
			// PF = 0 && CF = 0
			context->jae(tlabel);
			break;
		case _LT:
			// ZF = 0 && PF = 0 && CF = 1
			context->jb(tlabel);
			break;
		case _LTE:
			// PF = 0, ZF != CF
			context->jbe(tlabel);
			break;
		default:
			return;
		}
	} else {
		right->gencode(context);
		context->push(eax);
		left->gencode(context);
		context->pop(ebx);
		context->cmp(eax, ebx);

		switch (opr) {
		case _EQ:
			// ZF = 0
			context->je(tlabel);
			break;
		case _NEQ:
			// ZF != 0
			context->jne(tlabel);
			break;
		case _GT:
			// ZF != 0 && SF = 0
			context->jg(tlabel);
			break;
		case _GTE:
			// SF = 0
			context->jge(tlabel);
			break;
		case _LT:
			// ZF != 0 && SF = 1
			context->jl(tlabel);
			break;
		case _LTE:
			// SF = 1
			context->jle(tlabel);
			break;
		default:
			return;
		}
	}
	context->mov(eax, 0);
	context->jmp(elabel);
	context->label(tlabel);
	context->mov(eax, 1);
	context->label(elabel);
}

LogicExpression::LogicExpression(Expression* l, LOPR opr, Expression* r) :
		Expression() {
	this->left = l;
	this->opr = opr;
	this->right = r;
}

LogicExpression::~LogicExpression() {
	delete this->left;
	delete this->right;
}

void LogicExpression::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[LogicExpression]");
	if (left != NULL)
		left->print(file, level + 1);
	right->print(file, level + 1);
}

void LogicExpression::evaluate(EvalContext* context) {
	if (left != NULL)
		left->evaluate(context);
	right->evaluate(context);
	if (left != NULL && !left->getType()->equals(TYPE_BOOL)) {
		context->record(error_type_mismatch(left, TYPE_BOOL));
	}
	if (!right->getType()->equals(TYPE_BOOL)) {
		context->record(error_type_mismatch(right, TYPE_BOOL));
	}
}

Type * LogicExpression::getType() {
	return TYPE_BOOL;
}

void LogicExpression::gencode(AsmContext* context) {
	right->gencode(context);
	if (left != NULL) {
		context->push(eax);
		left->gencode(context);
		context->pop(ebx);
		switch (opr) {
		case _AND:
			context->land(eax, ebx);
			break;
		case _OR:
			context->lor(eax, ebx);
			break;
		default:
			break;
		}
	} else {
		context->lnot(eax);
	}
}

IntConstant::IntConstant(int val) :
		NumConstant() {
	this->value = val;
}

IntConstant::~IntConstant() {

}

Type * IntConstant::getType() {
	return TYPE_INT;
}

void IntConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%d\n", "[IntConstant]", value);
}

void IntConstant::gencode(AsmContext* context) {
	context->mov(eax, value);
}

RealConstant::RealConstant(float val) :
		NumConstant() {
	this->value = val;
}

RealConstant::~RealConstant() {

}

void RealConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%f\n", "[RealConstant]", value);
}

Type * RealConstant::getType() {
	return TYPE_REAL;
}

void RealConstant::gencode(AsmContext* context) {
	if (value == 0.0f) {
		context->fldz();
		return;
	}
	if (value == 1.0f) {
		context->fld1();
		return;
	}
// Get IEEE 745 Representation of float number;
	unsigned int* uint = (unsigned int*) &value;
	context->mov(eax, *uint);
	context->sub(esp, 4);
	context->mov(esp, eax, 2);
	context->fld(esp, 0);
	context->add(esp, 4);
}

BoolConstant::BoolConstant(bool val) :
		Expression() {
	this->value = val;
}

BoolConstant::~BoolConstant() {

}

void BoolConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[BoolConstant]", value ? "true" : "false");
}

Type * BoolConstant::getType() {
	return TYPE_BOOL;
}

void BoolConstant::gencode(AsmContext* context) {
	context->mov(eax, value ? 1 : 0);
}

Declare * Variable::getdeclare() {
	return declare;
}

Identifier::Identifier(char* name) :
		Variable() {
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
	declare = NULL;
	iscall = false;
	subprogram = NULL;
}

Identifier::~Identifier() {
	delete name;
}

void Identifier::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[Identifier]", name);
}

void Identifier::evaluate(EvalContext* context) {
	declare = context->getDeclare(this->name);
	if (NULL == declare) {
		subprogram = context->getSub(this->name);
		if (NULL == subprogram) {
			context->record(error_undefined_id(this));
		} else if (subprogram->params->size() != 0) {
			context->record(error_arg_mismatch(this));
		} else {
			iscall = true;
		}
	} else {
		iscall = false;
	}
}

Type * Identifier::getType() {
	if (declare == NULL)
		return NULL;
	return declare->type.get();
}

Identifier * Identifier::getId() {
	return this;
}

void Identifier::gencode(AsmContext* context) {
	genaddr(context);
	if (TYPE_REAL->equals(getType())) {
		context->fld(edx);
	} else {
		context->mov(eax, edx, 1);
	}
}

void Identifier::genaddr(AsmContext* context) {
	int level = 0;
	ActivationRecord* actrecord = context->getActRecord(name, &level);
	int offset = actrecord->offset(name);
	if (0 == level) {
		context->lea(edx, ebp, offset);
	} else {
		context->mov(edx, ebp);
		for (int i = 0; i < level; i++) {
			// point to the frame
			context->add(edx, 8);
			context->mov(edx, edx, 1);
		}
		context->add(edx, offset);
	}
}

bool Identifier::equals(const Identifier* another) const {
	return strcmp(this->name, another->name) == 0;
}

ArrayElement::ArrayElement(Identifier * id, Expression * val) :
		Variable() {
	this->name = id;
	this->index = val;
}

ArrayElement::~ArrayElement() {
	delete name;
	delete index;
}

void ArrayElement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[ArrayElement]");
	name->print(file, level + 1);
	index->print(file, level + 1);
}

void ArrayElement::evaluate(EvalContext* context) {
	Declare* dec = context->getDeclare(this->name->name);
	if (NULL == dec) {
		context->record(error_undefined_id(this->name));
	} else {
		this->declare = dec;
	}
// Check array type
	if (typeid(*(dec->getType())) != typeid(ArrayType)) {
		context->record(error_type_mismatch(this));
	}
	index->evaluate(context);
	if (index->getType() == NULL)
		return;
	if (index->getType() != TYPE_INT) {
		context->record(::error_type_mismatch(index, TYPE_INT));
	}
}

Type * ArrayElement::getType() {
	if (NULL == declare) {
		return NULL;
	}
	return ((ArrayType*) declare->getType())->basic.get();
}

Identifier * ArrayElement::getId() {
	return name;
}

void ArrayElement::genaddr(AsmContext* context) {
	ArrayType* arraytype = (ArrayType*) declare->getType();
	int begin = arraytype->begin;
	index->gencode(context);
	context->sub(eax, begin);
	context->mov(ebx, 4);
	context->mul(ebx);
	name->genaddr(context);
	context->add(edx, eax);
}

void ArrayElement::gencode(AsmContext* context) {
	genaddr(context);
	if (TYPE_REAL->equals(getType())) {
		context->fld(edx);
	} else {
		context->mov(eax, edx, 1);
	}
}
