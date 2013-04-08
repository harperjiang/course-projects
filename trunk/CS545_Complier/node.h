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

class Node {
public:
	Node() {
	}
	;
	virtual ~Node() {
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
};

class Subprogram: public Node {
public:
	Identifier* id;
	std::vector<Param*>* params;
	std::vector<Declare*>* declares;
	StatementBlock* body;
};

class Function: public Subprogram {
public:
	std::tr1::shared_ptr<Type> rettype;

	Function(Identifier*, std::vector<Param*>*, Type*, std::vector<Declare*>*,
			StatementBlock*);
	virtual ~Function();
};

class Procedure: public Subprogram {
public:
	Procedure(Identifier*, std::vector<Param*>*, std::vector<Declare*>*,
			StatementBlock*);
	virtual ~Procedure();
};

/**
 * Basic blocks
 */
class Declare: public Node {
public:
	Identifier* name;
	std::tr1::shared_ptr<Type> type;
	Declare(Type* type, Identifier* name);
	virtual ~Declare();
};

class Param: public Node {
public:
	Identifier* name;
	std::tr1::shared_ptr<Type> type;
	Param(Type*, Identifier*);
	virtual ~Param();
};

class Type: public Node {
public:
	Type() {
	}
	;
	virtual ~Type() {
	}
	;
};

class BasicType: public Type {
public:
	int type;
	BasicType(int t) {
		type = t;
	}
	virtual ~BasicType();
};

class ArrayType: public Type {
public:
	std::tr1::shared_ptr<Type> basic;
	int begin;
	int end;

	ArrayType(Type* basic, int begin, int end);
	virtual ~ArrayType();
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
	;
	virtual ~Statement() {
	}
	;
};

class IfStatement: public Statement {
public:
	Expression* condition;
	Statement* thenbody;
	Statement* elsebody;

	IfStatement(Expression*, Statement*, Statement*);
	virtual ~IfStatement();
};

class WhileStatement: public Statement {
public:
	Expression* condition;
	Statement* body;

	WhileStatement(Expression*, Statement*);
	virtual ~WhileStatement();
};

class AssignStatement: public Statement {
public:
	Variable* leftval;
	Expression* rightval;

	AssignStatement(Variable*, Expression*);
	virtual ~AssignStatement();
};

class StatementBlock: public Statement {
public:
	std::vector<Statement*>* statements;

	StatementBlock(std::vector<Statement*>*);
	virtual ~StatementBlock();
};

class CallStatement: public Statement {
public:
	CallExpression* callexp;

	CallStatement(CallExpression*);
	virtual ~CallStatement();
};

class BreakStatement: public Statement {
public:
	BreakStatement();
	virtual ~BreakStatement();
};

/**
 * Expressions
 */
class Expression: public Node {
public:
	Expression() {
	}
	;
	virtual ~Expression() {
	}
	;
};

class CallExpression: public Expression {
public:
	Identifier* callname;
	std::vector<Expression*>* params;

	CallExpression(Identifier* callname, std::vector<Expression*>* params);
	virtual ~CallExpression();
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
};

class Variable: public Expression {
public:
	Variable() {
	}
	;
	virtual ~Variable() {
	}
	;
};

class NumConstant: public Expression {
public:
	NumConstant() {
	}
	;
	virtual ~NumConstant() {
	}
	;
};

class IntConstant: public NumConstant {
public:
	int value;
	IntConstant(int val);
	virtual ~IntConstant();
};

class RealConstant: public NumConstant {
public:
	double value;
	RealConstant(double val);
	virtual ~RealConstant();
};

class BoolConstant: public Expression {
public:
	bool value;
	BoolConstant(bool val);
	virtual ~BoolConstant();
};

class Identifier: public Variable {
public:
	char* name;
	Identifier(char* name);
	virtual ~Identifier();
};

class ArrayElement: public Variable {
public:
	Identifier* name;
	Expression* index;

	ArrayElement(Identifier*, Expression* index);
	virtual ~ArrayElement();
};

#endif /* NODE_H_ */
