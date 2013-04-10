/*
 * node.h
 *
 *  Created on: Apr 7, 2013
 *      Author: harper
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <tr1/memory>
#include "eval_context.h"

class Node {
public:
	int beginRow;
	int endRow;
	int beginColumn;
	int endColumn;
	Node() {
		beginRow = 0;
		endRow = 0;
		beginColumn = 0;
		endColumn = 0;
	}
	virtual ~Node() {
	}
	virtual void print(FILE* file, int level) {
		for (int i = 0; i < level; i++)
			fprintf(file, "\t");
	}
	virtual void evaluate(EvalContext* context) {
	}
	;
};
/**
 * Program Structures
 */
class Identifier;
class Declare;
class Subprogram;
class StatementBlock;
class Param;
class Type;

class Program: public Node {
public:
	Identifier* id;
	std::vector<Identifier*> *params;
	std::vector<Declare*> *declares;
	std::vector<Subprogram*> *subs;
	StatementBlock* body;

	Program(Identifier*, std::vector<Identifier*>*, std::vector<Declare*>*,
			std::vector<Subprogram*>*, StatementBlock*);
	virtual ~Program();
	void print(FILE*, int);
	void evaluate(EvalContext* context);
};

class Subprogram: public Node {
public:
	Identifier* id;
	std::vector<Param*>* params;
	std::vector<Declare*>* declares;
	StatementBlock* body;

	void evaluate(EvalContext* context);
};

class Function: public Subprogram {
public:
	std::tr1::shared_ptr<Type> rettype;

	Function(Identifier*, std::vector<Param*>*, Type*, std::vector<Declare*>*,
			StatementBlock*);
	virtual ~Function();

	void print(FILE*, int);
};

class Procedure: public Subprogram {
public:
	Procedure(Identifier*, std::vector<Param*>*, std::vector<Declare*>*,
			StatementBlock*);
	virtual ~Procedure();

	void print(FILE*, int);
};

/**
 * Basic blocks
 */
class Declare: public Node {
public:
	Identifier* name;
	std::tr1::shared_ptr<Type> type;
	Declare(Type*, Identifier*);
	virtual ~Declare();

	void print(FILE*, int);
};

class Param: public Declare {
public:
	Param(Type*, Identifier*);

	void print(FILE*, int);
};

class Type: public Node {
public:
	Type() {
	}
	virtual ~Type() {
	}
	virtual const char* description() = 0;
};

class BasicType: public Type {
public:
	int type;
	BasicType(int t) {
		type = t;
	}
	virtual ~BasicType();

	void print(FILE* file, int level);
	const char* description();
};

class ArrayType: public Type {
private:
	char* desc;
public:
	std::tr1::shared_ptr<Type> basic;
	int begin;
	int end;

	ArrayType(Type*, int, int);
	virtual ~ArrayType();

	void print(FILE* file, int level);

	// overloading == operator
	bool operator ==(const ArrayType& another) const;
	const char* description();
};
/**
 * Statements
 */
class Expression;
class Variable;
class CallExpression;

class Statement: public Node {
public:
	Statement() {
	}
	virtual ~Statement() {
	}
};

class IfStatement: public Statement {
public:
	Expression* condition;
	Statement* thenbody;
	Statement* elsebody;

	IfStatement(Expression*, Statement*, Statement*);
	virtual ~IfStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
};

class WhileStatement: public Statement {
public:
	Expression* condition;
	Statement* body;

	WhileStatement(Expression*, Statement*);
	virtual ~WhileStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
};

class AssignStatement: public Statement {
public:
	Variable* leftval;
	Expression* rightval;

	AssignStatement(Variable*, Expression*);
	virtual ~AssignStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
};

class StatementBlock: public Statement {
public:
	std::vector<Statement*>* statements;

	StatementBlock(std::vector<Statement*>*);
	virtual ~StatementBlock();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
};

class CallStatement: public Statement {
public:
	CallExpression* callexp;

	CallStatement(CallExpression*);
	virtual ~CallStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
};

class BreakStatement: public Statement {
public:
	BreakStatement();
	virtual ~BreakStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
};

/**
 * Expressions
 */
class Expression: public Node {
public:
	Expression() {
	}
	virtual ~Expression() {
	}

	virtual Type* getType() = 0;
};

class CallExpression: public Expression {
private:
	Subprogram* source;
public:
	Identifier* callname;
	std::vector<Expression*>* params;

	CallExpression(Identifier* callname, std::vector<Expression*>* params);
	virtual ~CallExpression();

	void print(FILE*, int);
	void evaluate(EvalContext* context);
	Type* getType();
};

typedef enum _AOPR {
	_ADD, _SUB, _MUL, _DIV, _MOD
} AOPR;

class ArithExpression: public Expression {
public:
	Expression* left;
	AOPR opr;
	Expression* right;

	ArithExpression(Expression* l, AOPR opr, Expression* r);
	virtual ~ArithExpression();

	void print(FILE*, int);
	void evaluate(EvalContext* context);
	Type* getType();
};

typedef enum _ROPR {
	_GT, _LT, _EQ, _NEQ, _GTE, _LTE
} ROPR;

class RelExpression: public Expression {
public:
	Expression* left;
	ROPR opr;
	Expression* right;

	RelExpression(Expression*, ROPR, Expression*);
	virtual ~RelExpression();

	void print(FILE*, int);
	void evaluate(EvalContext* context);
	Type* getType();
};

typedef enum _LOPR {
	_AND, _OR, _NOT
} LOPR;

class LogicExpression: public Expression {
public:
	Expression* left;
	LOPR opr;
	Expression* right;

	LogicExpression(Expression*, LOPR, Expression*);
	virtual ~LogicExpression();

	void print(FILE*, int);
	void evaluate(EvalContext* context);
	Type* getType();
};

class Variable: public Expression {
protected:
	Declare* declare;
public:
	Variable() {
		declare = NULL;
	}
	virtual ~Variable() {
	}
};

class NumConstant: public Expression {
public:
	NumConstant() {
	}
	virtual ~NumConstant() {
	}
	virtual void evaluate(EvalContext* context) {
		// Do nothing
	}
};

class IntConstant: public NumConstant {
public:
	int value;
	IntConstant(int val);
	virtual ~IntConstant();

	void print(FILE*, int);
	Type* getType();
};

class RealConstant: public NumConstant {
public:
	double value;
	RealConstant(double val);
	virtual ~RealConstant();

	void print(FILE*, int);
	Type* getType();
};

class BoolConstant: public Expression {
public:
	bool value;
	BoolConstant(bool val);
	virtual ~BoolConstant();

	void print(FILE*, int);
	Type* getType();
};

class Identifier: public Variable {
public:
	char* name;
	Identifier(char* name);
	virtual ~Identifier();

	void print(FILE*, int);
	void evaluate(EvalContext*);
	Type* getType();
};

class ArrayElement: public Variable {
public:
	Identifier* name;
	Expression* index;

	ArrayElement(Identifier*, Expression* index);
	virtual ~ArrayElement();

	void print(FILE*, int);
	void evaluate(EvalContext*);
	Type* getType();
};

#endif /* NODE_H_ */
