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
		strcpy(var,name);		
		this->value = 0;
		temp = false;
	}	
	char* content() {
		char* buffer = new char[20];
		if(type == TYPE_VAR) {
			strcpy(buffer,var);
		} else {
			sprintf(buffer,"%d",value);
		}
		return buffer;
	}
	~Value(){
		delete var;
	}
};


class Quadruple {
public:
	Value* result;
	OPR opr;
	Value* left;
	Value* right;

	Quadruple(Value* result,OPR opr, Value* left, Value *right) {
		this->result = result;
		this->opr = opr;
		this->left = left;
		this->right = right;
	}
	virtual ~Quadruple();
};

static int QUAD_COUNTER = 0;

class QuadNode {
public:
	int number;
	Value* value;	
	std::vector<char*>* synonym;
	QuadNode* left;
	QuadNode* right;
	OPR opr;

	QuadNode(Value* value) {
		number = QUAD_COUNTER ++; 
		this->value = value;
		this->left = NULL;
		this->right = NULL; 
		this->synonym = new std::vector<char*>();
	}

	QuadNode(OPR opr, QuadNode* left, QuadNode* right) {
		number = QUAD_COUNTER ++;
		this->opr = opr;
		this->left = left;
		this->right = right;
		this->synonym = new std::vector<char*>();
	}

	void addSynonym(char* name) {
		synonym->push_back(name);
	}

	void removeSynonym(char* name) {
		for(std::vector<char*>::iterator it = synonym->begin();it!= synonym->end();it++) {
			if(strcmp(name,*it)==0)
				synonym->erase(it);
				break;
		}
	}
};


#endif /* QUADRUPLE_H_ */
