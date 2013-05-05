/*
 * quadruple.h
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#ifndef QUADRUPLE_H_
#define QUADRUPLE_H_

#include <stdlib.h>
#include "common.h"
#include "asm_context.h"
#include "node.h"

class RegContext;

typedef enum _ValueType {
	TYPE_NUM, TYPE_VAR

} ValueType;

class Value {
public:
	ValueType type;
	bool temp;
	int value;
	char* var;

	Value(int val) {
		this->type = TYPE_NUM;
		this->value = val;
		this->var = NULL;
		temp = false;
		init();
	}

	Value(const char* name) {
		this->type = TYPE_VAR;
		this->var = new char[strlen(name)];
		strcpy(var, name);
		this->value = 0;
		temp = false;
		init();
	}

	void init();

	~Value() {
		delete var;
	}
};

typedef enum _QuadOpr {
	QUAD_ASSIGN,
	QUAD_ADD, QUAD_SUB, QUAD_MUL, QUAD_DIV, QUAD_MOD,
	QUAD_PARAM, QUAD_CALL,
	QUAD_ADDR,
	QUAD_LOAD, QUAD_SAVE,
	QUAD_NONE
} QuadOpr;

extern Register reg(int index);

class QuadNode {
protected:
	void gentwinasm(AsmContext*, RegContext*);
	void genallocregasm(AsmContext*, RegContext*);
public:
	// For uniquely identify the nodes
	int number;

	// For storing quadruple infos
	Value* value;
	std::vector<Value*>* synonym;
	QuadNode* left;
	QuadNode* right;
	QuadOpr opr;

	// For quadruple generation
	bool processed;

	// For code generation
	int refCount;
	Register loc;
	bool memory;

	void init();
	QuadNode(Value* value);
	QuadNode(QuadOpr opr, QuadNode* left, QuadNode* right);
	virtual ~QuadNode();
	/*
	 * Deal with synonyms
	 */
	void addSynonym(Value* name);
	void removeSynonym(Value* name);
	void cleanSynonym();
	
	/**
	 * usenow: means the node's register will be used to store its calculation result.
	 * For a temp node with no further use, a store operation can be avoided in this way.
	 */
	void gencleanregasm(AsmContext* context, RegContext* regc, bool usenow);
	void genloadregasm(AsmContext* context, RegContext* regc);
	/**
	 * allowtemp: whether store temp variables
	 */
	void genstoreasm(AsmContext* context, RegContext* regc, bool allowtemp);
	void genasm(AsmContext* context, RegContext* regc);
};

#endif /* QUADRUPLE_H_ */
