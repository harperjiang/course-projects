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
		strcpy(var, name);
		this->value = 0;
		temp = false;
	}
	char* content() {
		char* buffer = new char[20];
		if (type == TYPE_VAR) {
			strcpy(buffer, var);
		} else {
			sprintf(buffer, "%d", value);
		}
		return buffer;
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

	void genasm(AsmContext* context) {
		switch (opr) {
		case OADD:

		case OSUB:
		case OMUL:
		case ODIV:
		case OMOD:
		case OASSIGN:
		case OPARAM:
		case OCALL:
		default:
			break;
		}
	}
};

static int QUAD_COUNTER = 0;

class QuadNode {
public:
	int number;

	Value* value;
	std::vector<Value*>* synonym;
	QuadNode* left;
	QuadNode* right;
	OPR opr;

	bool processed;
	Quadruple* origin;

	QuadNode(Value* value) {
		number = QUAD_COUNTER++;
		this->value = value;
		this->left = NULL;
		this->right = NULL;
		this->synonym = new std::vector<Value*>();
		origin = NULL;
		processed = false;
	}

	QuadNode(OPR opr, QuadNode* left, QuadNode* right) {
		number = QUAD_COUNTER++;
		this->opr = opr;
		this->left = left;
		this->right = right;
		this->synonym = new std::vector<Value*>();
		this->value = NULL;
		origin = NULL;
		processed = false;
	}

	void addSynonym(Value* name) {
		synonym->push_back(name);
	}

	void removeSynonym(Value* name) {
		for (std::vector<Value*>::iterator it = synonym->begin();
				it != synonym->end(); it++) {
			if (name == *it) {
				synonym->erase(it);
				break;
			}
		}
	}

	void cleanSynonym() {
		if (this->left != NULL)
			this->left->cleanSynonym();
		if (this->right != NULL)
			this->right->cleanSynonym();
		std::vector<Value*>* newnames = new std::vector<Value*>();
		for (std::vector<Value*>::iterator it = synonym->begin();
				it != synonym->end(); it++) {
			if (!(*it)->temp)
				newnames->push_back(*it);
		}
		if (newnames->size() == 0 && synonym->size() != 0) {
			newnames->push_back(synonym->at(0));
		}
		delete this->synonym;
		this->synonym = newnames;
	}

	void genQuads(std::vector<Quadruple*>* quads) {
		if (this->left != NULL && !this->left->processed) {
			this->left->genQuads(quads);
		}
		if (this->right != NULL && !this->right->processed) {
			this->right->genQuads(quads);
		}

		Quadruple* quad = NULL;
		if (left != NULL || right != NULL) {
			// Not a constant node
			switch (this->opr) {
			case OPARAM:
				quad = new Quadruple(NULL, OPARAM, NULL, this->right->value);
				quads->push_back(quad);
				break;
			default:
				// binary operators
				quad = new Quadruple(this->synonym->at(0), this->opr,
						this->left->value, this->right->value);
				quads->push_back(quad);
				this->value = this->synonym->at(0);
				break;
			}
		} else {
			switch (opr) {
			case OCALL:
				quads->push_back(this->origin);
				break;
			case OASSIGN:
				for (std::vector<Value*>::iterator it = synonym->begin();
						it != synonym->end(); it++) {
					if (this->value == *it)
						// Assign to itself is nonsense
						continue;
					if (it == synonym->begin()) {
						quad = new Quadruple(*it, OASSIGN, NULL, value);
					} else {
						quad = new Quadruple(*it, OASSIGN, NULL,
								synonym->at(0));
					}
					quads->push_back(quad);
				}
				break;
			default:
				break;
			}
		}
		this->processed = true;
	}
};

#endif /* QUADRUPLE_H_ */
