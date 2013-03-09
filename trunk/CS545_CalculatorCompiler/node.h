/*
 * node.h
 *
 *  Created on: Feb 7, 2013
 *      Author: harper
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>

#include "common.h"
#include "eval_context.h"
#include "asm_context.h"
#include "quad_context.h"

class Node {
public:
	virtual void evaluate(EvalContext* context) {
	}
	virtual void genasm(AsmContext* context)=0;

	virtual void genquad(QuadContext* context) {

	}

	virtual void print(FILE* output, int level) {
		for (int i = 0; i < level; i++)
			fprintf(output, "\t");
	}
	virtual ~Node() {
	}
};

class Expression: public Node {
public:
	virtual ~Expression();
};

class Identifier: public Expression {
public:
	char* name;
	Identifier(char* n) {
		name = new char[strlen(n)];
		strcpy(this->name, n);
	}
	~Identifier();
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void genquad(QuadContext* context);
	void print(FILE* output, int level);
};

class NumConstant: public Expression {
public:
	int value;
	NumConstant(int val) {
		this->value = val;
	}
	~NumConstant();
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void genquad(QuadContext* context);
	void print(FILE* output, int level);
};

class ArithExpression: public Expression {
public:
	Expression * left;
	Expression* right;
	OPR opr;
	ArithExpression(Expression*l, OPR o, Expression*r) {
		this->left = l;
		this->right = r;
		this->opr = o;
	}
	~ArithExpression() {
		delete this->left;
		delete this->right;
	}
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void genquad(QuadContext* context);
	void print(FILE* output, int level);
};

class Statement: public Node {
public:
	virtual void evaluate(EvalContext* context)=0;
	virtual void genasm(AsmContext* context)=0;
	virtual void genquad(QuadContext* context)=0;
	virtual void print(FILE*output, int level)=0;
	virtual ~Statement() {
	}
};

class AssignStatement: public Statement {
public:
	Identifier*id;
	Expression* value;
	AssignStatement(Identifier* id, Expression* val) {
		this->id = id;
		this->value = val;
	}
	~AssignStatement() {
		delete id;
		delete value;
	}
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void genquad(QuadContext* context);
	void print(FILE* output, int level);
};

class PrintStatement: public Statement {
public:
	Expression* expression;
	PrintStatement(Expression* exp) {
		this->expression = exp;
	}
	~PrintStatement() {
		delete this->expression;
	}
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void genquad(QuadContext* context);
	void print(FILE* output, int level);
};

class Statements: public Node {
public:
	std::vector<Statement*>* statements;
	Statements() {
		this->statements = new std::vector<Statement*>();
	}
	~Statements();
	void insert(Statement* stmt, int index) {
		this->statements->insert(this->statements->begin() + index, stmt);
	}
	Statement* get(int index) {
		return this->statements->at(index);
	}
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void print(FILE* output, int level);
};

class StatementBlock : public Statement {
public:
	Statements *content;
	StatementBlock() {
		content = NULL;
	}
	~StatementBlock();
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void genquad(QuadContext* context);
	void print(FILE* output, int level);
};

class Program : public Node {
public:
	StatementBlock *block;
	Program() {
		block = NULL;
	}
	~Program();
	void evaluate(EvalContext* context);
	void genasm(AsmContext* context);
	void print(FILE* output, int level);
};

#endif /* NODE_H_ */
