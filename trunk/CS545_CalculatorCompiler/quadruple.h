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

class QuadNode {
public:
	Value* value;
};


#endif /* QUADRUPLE_H_ */
