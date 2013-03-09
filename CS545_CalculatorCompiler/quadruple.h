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

#define NO_AVAIL_REG 10
#define REG_LOCKED 20

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
	}

	Value(const char* name) {
		this->type = TYPE_VAR;
		this->var = new char[strlen(name)];
		strcpy(var, name);
		this->value = 0;
		temp = false;
	}

	~Value() {
		delete var;
	}
};

class Quadruple {
public:
	Value* result;
	OPR opr;
	Value* left;
	Value* right;

	Quadruple(Value* result, OPR opr, Value* left, Value *right) {
		this->result = result;
		this->opr = opr;
		this->left = left;
		this->right = right;
	}

	virtual ~Quadruple();
};

class QuadNode;

extern Register reg(int index);

class RegContext {
private:
	std::map<Register,QuadNode*>* nodes;
	std::map<Register,bool>* locks;
	int nextpointer;
public:

	RegContext() {
		nodes = new std::map<Register,QuadNode*>();
		locks = new std::map<Register,bool>();
		nextpointer = 0;
	}
	virtual ~RegContext() {
		delete nodes;
		delete locks;
	}
	
	Register next() {
		Register retval = unknown;
		int start = nextpointer;
		while(nextpointer - start < 4) {
			retval = reg((nextpointer++)%4);
			if(!islock(retval))
				return retval;
		}
		return unknown;
	}

	Register avail() {
		for(int i = 0 ; i < 4 ; i++) {
			if(get(reg(i)) == NULL)
				return reg(i);
		}
		return unknown;
	}	

	QuadNode* get(Register reg) {
		if(nodes->find(reg) == nodes->end())
			return NULL;
		return nodes->find(reg)->second;
	}

	void clean(Register reg) {
		if(islock(reg))
			throw REG_LOCKED;
		nodes->erase(reg);
	}

	void put(Register reg, QuadNode* node) {
		if(islock(reg) && get(reg) != node)
			throw REG_LOCKED;
		nodes->insert(std::pair<Register,QuadNode*>(reg,node));
	}

	void lock(Register reg) {
		locks->insert(std::pair<Register,bool>(reg,true));
	}

	void unlock(Register reg) {
		locks->erase(reg);
	}
	
	bool islock(Register reg) {
		return locks->find(reg) != locks->end() && locks->find(reg)->second;
	}
};	


class QuadNode {
public:
	// For uniquely identify the nodes
	int number;

	// For storing quadruple infos
	Value* value;
	std::vector<Value*>* synonym;
	QuadNode* left;
	QuadNode* right;
	OPR opr;

	// For quadruple generation
	bool processed;
	Quadruple* origin;

	// For labeling
	int ilabel;

	// For code generation
	int refCount;
	Register loc;
	bool memory;

	QuadNode(Value* value);
	QuadNode(OPR opr, QuadNode* left, QuadNode* right);
	virtual ~QuadNode();
	/*
	 * Deal with synonyms
	 */
	void addSynonym(Value* name);
	void removeSynonym(Value* name);
	void cleanSynonym();

	void label(int flag);
	
	/**
	 * usenow: means the node's register will be used to store its calculation result.
	 * For a temp node with no further use, a store operation can be avoided.
	 */
	void gencleanregasm(AsmContext* context, RegContext* regc,bool usenow);
	void genloadregasm(AsmContext* context);
	/**
	 * allowtemp: whether store temp variables
	 */
	void genstoreasm(AsmContext* context, bool allowtemp);
	void genasm(AsmContext* context, RegContext* regc);
};

#endif /* QUADRUPLE_H_ */
