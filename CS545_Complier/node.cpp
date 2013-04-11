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

Program::Program(Identifier* id, std::vector<Identifier*>* params,
		std::vector<Declare*>* declares, std::vector<Subprogram*>* subs,
		StatementBlock* body) {
	this->id = id;
	this->params = params;
	this->declares = declares;
	this->subs = subs;
	this->body = body;
}

Program::~Program() {
	delete id;
	clearVector(params);
	clearVector(declares);
	clearVector(subs);
	delete body;
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
		context->pushFrame(*ite);
		(*ite)->evaluate(context);
		context->popFrame();
	}
	// Evaluate body
	body->evaluate(context);
}

void Program::gencode(AsmContext* context) {
	// Gen data section
	context->section("data");
	context->label("intformat");
	context->declare("string", "%d\n");

	// Gen text section
	context->header();
	context->label("_start");

	// TODO Handle activation record

	// Generate procedure for subroutines
	for (std::vector<Subprogram*>::iterator ite = subs->begin();
			ite != subs->end(); ite++) {
		(*ite)->gencode(context);
	}

	body->gencode(context);

	// Gen exit code
	context->mov(eax, 1);
	context->mov(ebx, 0);
	context->interrupt(0x80);
	context->ret();
	// Gen tail code
	context->tail();
}

Function::Function(Identifier* id, std::vector<Param*>* params, Type* rettype,
		std::vector<Declare*>* declares, StatementBlock* body) {
	this->id = id;
	this->params = params;
	this->rettype = get_type_pointer(rettype);
	this->declares = declares;
	this->body = body;
}

Function::~Function() {
	delete id;
	clearVector(params);
	rettype.reset();
	clearVector(declares);
	delete body;
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
	context->label(id->name);
	// TODO Handle activation record

	body->gencode(context);
}

void Subprogram::evaluate(EvalContext* context) {
	for (std::vector<Declare*>::iterator ite = declares->begin();
			ite != declares->end(); ite++) {
		context->addDeclare((*ite)->name->name, (*ite));
	}
	for (std::vector<Param*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		context->addDeclare((*ite)->name->name, (*ite));
	}
	body->evaluate(context);
}

Procedure::Procedure(Identifier* id, std::vector<Param*>* params,
		std::vector<Declare*>* declares, StatementBlock* block) {
	this->id = id;
	this->params = params;
	this->declares = declares;
	this->body = block;
}

Procedure::~Procedure() {
	delete id;
	clearVector(params);
	clearVector(declares);
	delete body;
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

}

Declare::Declare(Type* t, Identifier* id) {
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

ArrayType::ArrayType(Type* t, int begin, int end) {
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

bool ArrayType::operator ==(const ArrayType& another) const {
	return basic.get() == another.basic.get();
}

const char* ArrayType::description() {
	return desc;
}

IfStatement::IfStatement(Expression* cond, Statement* thenbody,
		Statement* elsebody) {
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
	if (TYPE_BOOL != condition->getType()) {
		context->record(error_type_mismatch(condition, TYPE_BOOL));
	}
	thenbody->evaluate(context);
	if (elsebody != NULL)
		elsebody->evaluate(context);
}

void IfStatement::gencode(AsmContext* context) {
	char* elselabel = context->genlabel();
	condition->gencode(context);
	context->jne(elselabel);
	thenbody->gencode(context);
	context->label(elselabel);
	if (elsebody != NULL)
		elsebody->gencode(context);
}

WhileStatement::WhileStatement(Expression* cond, Statement* body) {
	this->condition = cond;
	this->body = body;
}

WhileStatement::~WhileStatement() {
	delete condition;
	delete body;
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
	if (TYPE_BOOL != condition->getType()) {
		context->record(error_type_mismatch(condition, TYPE_BOOL));
	}
	body->evaluate(context);
}

void WhileStatement::gencode(AsmContext* context) {
	char* startlabel = context->genlabel();
	char* endlabel = context->genlabel();
	context->label(startlabel);
	condition->gencode(context);
	// TODO is this correct?
	context->jne(endlabel);
	body->gencode(context);
	context->jmp(startlabel);
	context->label(endlabel);
}

AssignStatement::AssignStatement(Variable* lval, Expression* rval) {
	this->leftval = lval;
	this->rightval = rval;
}

AssignStatement::~AssignStatement() {
	delete leftval;
	delete rightval;
}

void AssignStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[AssignStatement]");
	leftval->print(file, level + 1);
	rightval->print(file, level + 1);
}

void AssignStatement::evaluate(EvalContext* context) {
	leftval->evaluate(context);
	rightval->evaluate(context);
	if (leftval->getType() != rightval->getType()) {
		context->record(error_type_mismatch(leftval, rightval->getType()));
	}
	// TODO If AssignStatement is an ReturnStatement
}

void AssignStatement::gencode(AsmContext* context) {

}

StatementBlock::StatementBlock(std::vector<Statement*>* stmts) {
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

CallStatement::CallStatement(CallExpression* call) {
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

BreakStatement::BreakStatement() {

}

BreakStatement::~BreakStatement() {

}

void BreakStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[BreakStatement]");
}

void BreakStatement::evaluate(EvalContext* context) {
	// TODO Check whether in a while loop

}

ReturnStatement::ReturnStatement(Expression* exp) {
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
	if (retvalue != NULL && function->getType() != retvalue->getType()) {
		context->record(::error_type_mismatch(retvalue, function->getType()));
	}
}

void ReturnStatement::gencode(AsmContext* context) {
	if (retvalue != NULL) {
		retvalue->gencode(context);
	}
	// TODO store return value in eax
	context->ret();
}

CallExpression::CallExpression(Identifier* name,
		std::vector<Expression*>* params) {
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
	for (int i = 0; i < sub->params->size(); i++) {
		Expression* realparam = this->params->at(i);
		Param* def = sub->params->at(i);
		realparam->evaluate(context);
		if (realparam->getType() != def->getType()) {
			context->record(error_type_mismatch(realparam, def->getType()));
		}
	}
}

Type* CallExpression::getType() {
	if (NULL == source || typeid(source) == typeid(Procedure))
		return NULL;
	Function* function = (Function*) source;
	return function->rettype.get();
}

void CallExpression::gencode(AsmContext* context) {
	for (std::vector<Expression*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->gencode(context);
		context->push(eax);
	}
	context->push(params->size());
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
		// write can write everything
		context->record(error_arg_mismatch(this));
	}
}

Type* SysCall::getType() {
	return NULL;
}

void SysCall::gencode(AsmContext* context) {
	// TODO
	if (type == _CALL_READ) {
		context->call("scanf");
	}
	if (type == _CALL_WRITE) {
		context->call("printf");
	}
}

ArithExpression::ArithExpression(Expression* l, AOPR opr, Expression* r) {
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
	if (left != NULL && (left->getType() != right->getType())) {
		context->record(error_type_mismatch(this));
	}
}

Type* ArithExpression::getType() {
	return right->getType();
}

RelExpression::RelExpression(Expression* l, ROPR opr, Expression* r) {
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
	if (left != NULL)
		left->evaluate(context);
	right->evaluate(context);
	if (left != NULL && (left->getType() != right->getType())) {
		context->record(error_type_mismatch(this));
	}
}

Type* RelExpression::getType() {
	return TYPE_BOOL;
}

LogicExpression::LogicExpression(Expression* l, LOPR opr, Expression* r) {
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
	if (left != NULL && left->getType() != TYPE_BOOL) {
		context->record(error_type_mismatch(left, TYPE_BOOL));
	}
	if (right->getType() != TYPE_BOOL) {
		context->record(error_type_mismatch(right, TYPE_BOOL));
	}
}

Type* LogicExpression::getType() {
	return TYPE_BOOL;
}

IntConstant::IntConstant(int val) {
	this->value = val;
}

IntConstant::~IntConstant() {

}

Type* IntConstant::getType() {
	return TYPE_INT;
}

void IntConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%d\n", "[IntConstant]", value);
}

RealConstant::RealConstant(double val) {
	this->value = val;
}

RealConstant::~RealConstant() {
}

void RealConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%f\n", "[RealConstant]", value);
}

Type* RealConstant::getType() {
	return TYPE_REAL;
}

BoolConstant::BoolConstant(bool val) {
	this->value = val;
}

BoolConstant::~BoolConstant() {

}

void BoolConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[BoolConstant]", value ? "true" : "false");
}

Type* BoolConstant::getType() {
	return TYPE_BOOL;
}

Identifier::Identifier(char* name) :
		Variable() {
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
	declare = NULL;
}

Identifier::~Identifier() {
	delete name;
}

void Identifier::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[Identifier]", name);
}

void Identifier::evaluate(EvalContext* context) {
	Declare* dec = context->getDeclare(this->name);
	if (NULL == dec) {
		context->record(error_undefined_id(this));
	} else {
		this->declare = dec;
	}
}

Type* Identifier::getType() {
	if (declare == NULL)
		return NULL;
	return declare->type.get();
}

ArrayElement::ArrayElement(Identifier* id, Expression* val) :
		Variable() {
	this->name = id;
	this->index = val;
}

ArrayElement::~ArrayElement() {
	delete name;
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
}

Type* ArrayElement::getType() {
	if (NULL == declare) {
		return NULL;
	}
	return declare->type.get();
}
