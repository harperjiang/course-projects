/*
 * node.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: harper
 */

#include <string.h>
#include <stdlib.h>
#include <tr1/memory>
#include "node.h"

int _TYPE_REAL = 1;
int _TYPE_INT = 2;
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

Declare::Declare(Type* type, Identifier* id) {
	this->name = id;
	this->type = std::tr1::shared_ptr<Type>(type);
}

Declare::~Declare() {
	delete name;
	type.reset();
}

Param::Param(Type* type, Identifier* id) {
	this->type = std::tr1::shared_ptr<Type>(type);
	this->name = id;
}

Param::~Param() {
	type.reset();
	delete name;
}

BasicType::~BasicType() {

}

ArrayType::ArrayType(Type* type, int begin, int end) {
	this->basic = std::tr1::shared_ptr<Type>(type);
	this->begin = begin;
	this->end = end;
}

ArrayType::~ArrayType() {
	basic.reset();
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

WhileStatement::WhileStatement(Expression* cond, Statement* body) {
	this->condition = cond;
	this->body = body;
}

WhileStatement::~WhileStatement() {
	delete condition;
	delete body;
}

AssignStatement::AssignStatement(Variable* lval, Expression* rval) {
	this->leftval = lval;
	this->rightval = rval;
}

AssignStatement::~AssignStatement() {
	delete leftval;
	delete rightval;
}

StatementBlock::StatementBlock(std::vector<Statement*>* stmts) {
	this->statements = stmts;
}

StatementBlock::~StatementBlock() {
	clearVector(this->statements);
}

CallStatement::CallStatement(CallExpression* call) {
	this->callexp = call;
}

CallStatement::~CallStatement() {
	delete callexp;
}

BreakStatement::BreakStatement() {

}

BreakStatement::~BreakStatement() {

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

ArithExpression::ArithExpression(Expression* l, AOPR opr, Expression* r) {
	this->left = l;
	this->opr = opr;
	this->right = r;
}

ArithExpression::~ArithExpression() {
	delete this->left;
	delete this->right;
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

LogicExpression::LogicExpression(Expression* l, LOPR opr, Expression* r) {
	this->left = l;
	this->opr = opr;
	this->right = r;
}

LogicExpression::~LogicExpression() {
	delete this->left;
	delete this->right;
}

IntConstant::IntConstant(int val) {
	this->value = val;
}

IntConstant::~IntConstant() {

}

RealConstant::RealConstant(double val) {
	this->value = val;
}

RealConstant::~RealConstant() {
}

BoolConstant::BoolConstant(bool val) {
	this->value = val;
}

BoolConstant::~BoolConstant() {

}

Identifier::Identifier(char* name) {
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
}

Identifier::~Identifier() {
	delete name;
}

ArrayElement::ArrayElement(Identifier* id, Expression* val) {
	this->name = id;
	this->index = val;
}

ArrayElement::~ArrayElement() {
	delete name;
}
