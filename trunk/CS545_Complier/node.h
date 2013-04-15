/*
 * node.h
 *
 *  Created on: Apr 7, 2013
 *      Author: harper
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <map>
#include <tr1/memory>
#include "eval_context.h"
#include "asm_context.h"
#include "act_record.h"

struct YYLTYPE;

class Node {
public:
	YYLTYPE* loc;
	Node() {
		loc = NULL;
	}
	virtual ~Node() {
	}
	virtual void print(FILE* file, int level) {
		for (int i = 0; i < level; i++)
			fprintf(file, "\t");
	}
	virtual void evaluate(EvalContext* context) {
	}
	virtual void gencode(AsmContext* context) {
	}
	void setloc(YYLTYPE loc);
	void setloc(YYLTYPE* from, YYLTYPE* to);
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

class Routine: public Node {
protected:
	std::map<char*, Declare*, comp>* declareTable;
	std::map<char*, Subprogram*, comp>* subTable;
public:
	Identifier* id;
	std::vector<Declare*> *declares;
	std::vector<Subprogram*> *subs;
	StatementBlock* body;

	ActivationRecord* actrecord;

	Routine(Identifier*, std::vector<Declare*>*, std::vector<Subprogram*>*,
			StatementBlock*);
	Declare* getDeclare(char*);
	Subprogram* getSub(char*);

	virtual ~Routine();
};

class Program: public Routine {
private:
public:
	std::vector<Identifier*> *params;
	Program(Identifier*, std::vector<Identifier*>*, std::vector<Declare*>*,
			std::vector<Subprogram*>*, StatementBlock*);
	virtual ~Program();
	void print(FILE*, int);
	void evaluate(EvalContext* context);
	void gencode(AsmContext* context);
};

class Subprogram: public Routine {
private:
public:
	std::vector<Param*>* params;

	int level;

	Subprogram(Identifier*, std::vector<Param*>*, std::vector<Declare*>*,
			std::vector<Subprogram*>*, StatementBlock*);
	virtual ~Subprogram();

	void evaluate(EvalContext* context);
};

class AssignStatement;

class Function: public Subprogram {
public:
	char* returnlabel;
	AssignStatement* returnstmt;
	std::tr1::shared_ptr<Type> rettype;

	Function(Identifier*, std::vector<Param*>*, Type*, std::vector<Declare*>*,
			std::vector<Subprogram*>*, StatementBlock*);
	virtual ~Function();

	Type* getType();

	void print(FILE*, int);
	void evaluate(EvalContext* context);
	void gencode(AsmContext*);
};

class Procedure: public Subprogram {
public:
	Procedure(Identifier*, std::vector<Param*>*, std::vector<Declare*>*,
			std::vector<Subprogram*>*, StatementBlock*);
	virtual ~Procedure();

	void print(FILE*, int);
	void gencode(AsmContext*);
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
	Type* getType();
};

class Param: public Declare {
public:
	Param(Type*, Identifier*);

	void print(FILE*, int);
};

class Type: public Node {
public:
	Type();
	virtual ~Type();
	virtual const char* description() = 0;
	virtual bool equals(Type*) = 0;
};

class BasicType: public Type {
public:
	int type;
	BasicType(int t);
	virtual ~BasicType();

	void print(FILE* file, int level);
	const char* description();
	virtual bool equals(Type*);
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

	const char* description();
	virtual bool equals(Type*);
	Type* getBasic();
};
/**
 * Statements
 */
class Expression;
class Variable;
class CallExpression;

class Statement: public Node {
public:
	Statement() :
			Node() {
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
	void gencode(AsmContext*);
};

class WhileStatement: public Statement {
public:
	Expression* condition;
	Statement* body;
	// For BreakStatement to jump out
	char* endlabel;

	WhileStatement(Expression*, Statement*);
	virtual ~WhileStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
	void gencode(AsmContext*);
};

class ForStatement: public Statement {
public:
	Identifier* variable;
	Expression* from;
	Expression* to;
	Statement* body;

	ForStatement(Identifier*, Expression*, Expression*, Statement*);
	virtual ~ForStatement();

	void print(FILE*, int);
	void evaluate(EvalContext*);
	void gencode(AsmContext*);
};

class AssignStatement: public Statement {
private:
	bool isreturn;
	Function* function;
public:
	Variable* leftval;
	Expression* rightval;

	AssignStatement(Variable*, Expression*);
	virtual ~AssignStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
	void gencode(AsmContext*);
};

class StatementBlock: public Statement {
public:
	std::vector<Statement*>* statements;

	StatementBlock(std::vector<Statement*>*);
	virtual ~StatementBlock();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
	void gencode(AsmContext* context);
};

class CallStatement: public Statement {
public:
	CallExpression* callexp;

	CallStatement(CallExpression*);
	virtual ~CallStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
	void gencode(AsmContext*);
};

class BreakStatement: public Statement {
private:
	WhileStatement* parent;
public:
	BreakStatement();
	virtual ~BreakStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
	void gencode(AsmContext*);
};

class ReturnStatement: public Statement {
public:
	Expression* retvalue;
	ReturnStatement(Expression*);
	virtual ~ReturnStatement();

	void print(FILE* file, int level);
	void evaluate(EvalContext* context);
	void gencode(AsmContext*);
};

/**
 * Expressions
 */
class Expression: public Node {
public:
	Expression() :
			Node() {
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
	void gencode(AsmContext*);
};

class SysCall: public CallExpression {
public:
	int type;
	SysCall(int, std::vector<Expression*>*);
	virtual ~SysCall();
	void print(FILE*, int);
	void evaluate(EvalContext* context);
	Type* getType();
	void gencode(AsmContext*);
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
	void gencode(AsmContext*);
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
	void gencode(AsmContext*);
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
	void gencode(AsmContext*);
};

class NumConstant: public Expression {
public:
	NumConstant() :
			Expression() {
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
	void gencode(AsmContext*);
};

class RealConstant: public NumConstant {
public:
	float value;
	RealConstant(float val);
	virtual ~RealConstant();

	void print(FILE*, int);
	Type* getType();
	void gencode(AsmContext*);
};

class BoolConstant: public Expression {
public:
	bool value;
	BoolConstant(bool val);
	virtual ~BoolConstant();

	void print(FILE*, int);
	Type* getType();
	void gencode(AsmContext*);
};

class Variable: public Expression {
protected:
	Declare* declare;
public:
	Variable() :
			Expression() {
		declare = NULL;
	}
	virtual ~Variable() {
	}
	virtual Identifier* getId() = 0;
	// Assembly code to put the address of variable to edx
	virtual void genaddr(AsmContext*) =0;
	Declare* getdeclare();
};

class Identifier: public Variable {
protected:
	bool iscall;
	Subprogram* subprogram;
public:
	char* name;
	Identifier(char* name);
	virtual ~Identifier();

	void print(FILE*, int);
	void evaluate(EvalContext*);
	Type* getType();
	Identifier* getId();
	void genaddr(AsmContext*);
	void gencode(AsmContext*);
	bool equals(const Identifier* another) const;
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
	Identifier* getId();
	void genaddr(AsmContext*);
	void gencode(AsmContext*);
};

#endif /* NODE_H_ */
