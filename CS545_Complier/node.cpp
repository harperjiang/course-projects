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

#define _TYPE_REAL 1
#define _TYPE_INT 2
BasicType* TYPE_REAL = new BasicType(_TYPE_REAL);
BasicType* TYPE_INT = new BasicType(_TYPE_INT);

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

Function::Function(Identifier* id, std::vector<Param*>* params, Type* rettype,
		std::vector<Declare*>* declares, StatementBlock* body) {
	this->id = id;
	this->params = params;
	this->rettype = std::tr1::shared_ptr<Type>(rettype);
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

Declare::Declare(Type* type, Identifier* id) {
	this->name = id;
	this->type = std::tr1::shared_ptr<Type>(type);
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

Param::Param(Type* type, Identifier* id) {
	this->type = std::tr1::shared_ptr<Type>(type);
	this->name = id;
}

Param::~Param() {
	type.reset();
	delete name;
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
	case _TYPE_REAL:
		fprintf(file, "%s%s\n", "[Type]", "Real");
	default:
		return;
	}
}

ArrayType::ArrayType(Type* type, int begin, int end) {
	this->basic = std::tr1::shared_ptr<Type>(type);
	this->begin = begin;
	this->end = end;
}

ArrayType::~ArrayType() {
	basic.reset();
}

void ArrayType::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[ArrayType]");
	basic.get()->print(file, level + 1);
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

BreakStatement::BreakStatement() {

}

BreakStatement::~BreakStatement() {

}

void BreakStatement::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[BreakStatement]");
}

CallExpression::CallExpression(Identifier* name,
		std::vector<Expression*>* params) {
	this->callname = name;
	this->params = params;
}

CallExpression::~CallExpression() {
	delete callname;
	clearVector(params);
}

void CallExpression::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[CallExpression]");
	for (std::vector<Expression*>::iterator ite = params->begin();
			ite != params->end(); ite++) {
		(*ite)->print(file, level + 1);
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

IntConstant::IntConstant(int val) {
	this->value = val;
}

IntConstant::~IntConstant() {

}

void IntConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[IntConstant]");
}

RealConstant::RealConstant(double val) {
	this->value = val;
}

RealConstant::~RealConstant() {
}

void RealConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[RealConstant]");
}

BoolConstant::BoolConstant(bool val) {
	this->value = val;
}

BoolConstant::~BoolConstant() {

}

void BoolConstant::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s\n", "[BoolConstant]");
}

Identifier::Identifier(char* name) {
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
}

Identifier::~Identifier() {
	delete name;
}

void Identifier::print(FILE* file, int level) {
	Node::print(file, level);
	fprintf(file, "%s%s\n", "[Identifier]", name);
}

ArrayElement::ArrayElement(Identifier* id, Expression* val) {
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
