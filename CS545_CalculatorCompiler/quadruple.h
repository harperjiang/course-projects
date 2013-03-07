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

extern Register reg(int index);

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

class QuadNode;

class RegContext {
public:
	std::map<int,QuadNode*>* nodes;
	int* locks;
	RegContext() {
		nodes = new std::map<int,QuadNode*>();
		locks = new int[4];
	}
	virtual ~RegContext() {
		delete nodes;
		delete locks;
	}
	
	int get() {
		for(int i = 0; i < 4; i++) {
			if(nodes->end() == nodes->find(i))
				return i;
		}
		return -1;
	}

	int next() {
		for(int i = 0 ; i < 4; i++) {
			if(!locks[i])
				return i;
		}
		return -1;
	}

	QuadNode* get(int i) {
		return nodes->find(i)->second;
	}

	void clean(int reg) {
		nodes->erase(reg);
	}
	void put(int reg, QuadNode* node) {
		nodes->insert(std::pair<int,QuadNode*>(reg,node));
	}

	void lock(int reg) {
		locks[reg] = 1;
	}

	void unlock(int reg) {
		locks[reg] = 0;
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
	int loc;
	bool memory;

	QuadNode(Value* value) {
		number = QUAD_COUNTER++;
		this->value = value;
		this->left = NULL;
		this->right = NULL;
		this->synonym = new std::vector<Value*>();
		origin = NULL;
		processed = false;

		ilabel = 0;
		loc = -1;
		memory = false;
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
	
		ilabel = 0;
		loc= -1;
		memory = false;
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

	void label(int flag) {
		int llabel = 0;
		int rlabel = 0;
		if(left == NULL && right == NULL) {// leaf
			ilabel = flag; // rightmost has 1, other has 0
			return;
		}
		int newflag = 1;
		if(left != NULL) {
			left->label(newflag--);
			llabel = left->ilabel;
		}
		if(right != NULL) {
			right->label(newflag--);
			rlabel =right->ilabel;
		}
		this->ilabel = (llabel == rlabel)?llabel+1:(llabel>=rlabel?llabel:rlabel);
	}


	void clearReg(AsmContext* context,RegContext* regc, int regindex) {
		QuadNode* regNode = regc->get(regindex);
		if(regNode != NULL) {
			if(!regNode->memory && regNode->synonym->size() != 0) {
				MemoryUnit* mu = context->find(regNode->value->var);
				context->mov(mu->getPosition(),reg(regindex),0);	
				regNode->memory = true;
			}
			regc->clean(regNode->loc);
			regNode->loc = 0;
		}
	}


	void genasm(AsmContext* context, RegContext* regc) {
		if(left == NULL && right == NULL) {
			// leaf
			// move it to register		
			int avail = regc->get();	
			if(-1 == avail) {
				// Clean an unlock register 	
				int next = regc->next();
				QuadNode* curEax = regc->get(next);
				if(!(curEax->memory)) {
					// Save to memory
					MemoryUnit* memLoc = context->find(curEax->synonym->at(0)->var);
					context->mov(memLoc->getPosition(),reg(next),2);
					curEax->memory = true;
				}
				curEax->loc = 0;
				avail = next;
			}
			regc->put(avail, this);
			this->loc = avail;
			if(value->type == TYPE_NUM) {
				context->mov(reg(avail), value->value);
				store(context);
			} else {
				this->memory = true;
				MemoryUnit* memloc = context->find(value->var);
				context->mov(reg(avail),memloc->getPosition(),1); 
			}
			
		} else if(left == NULL) {
			right->genasm(context,regc);
			// Uniary operations, call and param
			switch(opr) {
			case OCALL:
				context->push(1);
				context->call("_print");
				break;
			case OPARAM:
				context->push(reg(right->loc));
				break;
			default:
				break;
			}
		} else {
			right->genasm(context,regc);
			regc->lock(right->loc);
			left->genasm(context,regc);
			regc->unlock(right->loc);
			Register dest = reg(left->loc);
			Register src = reg(right->loc);
			switch(opr) {
			case OADD:
				context->add(dest,src);
				this->loc = left->loc;
				this->memory = false;
				break;
			case OSUB:
				context->sub(dest,src);
				this->loc = left->loc;
				this->memory = false;
				break;
			case OMUL:
				// Clear edx
				clearReg(context,regc,3);
				context->push(eax);
				context->push(src);
				context->push(dest);
				context->pop(eax);
				context->pop(edx);
				context->mul(edx);	
				if(dest != eax)	
					context->mov(dest,eax);
				if(dest == eax) {
					context->pop(edx);
				} else {
					context->pop(eax);
				}
				break;	
			case ODIV:
				// Clear edx
				clearReg(context,regc,3);
				context->push(eax);
				context->push(ebx);

				context->push(dest);
				context->push(src);
				
				context->pop(ebx);
				context->pop(eax);
				context->mov(edx,0);
				
				context->div(ebx);

				context->mov(dest,eax);

				if(dest==ebx) {
					context->pop(eax);
				} else {
					context->pop(ebx);
				}
				if(dest == eax) {
					context->pop(edx);
				} else {
					context->pop(eax);
				}

				break;
			case OMOD:
				clearReg(context,regc,3);
				context->push(eax);
				context->push(ebx);
				
				context->push(dest);
				context->push(src);
				
				context->pop(ebx);
				context->pop(eax);
				
				context->mov(edx,0);
				context->div(ebx);

				context->mov(dest,edx);
				
				if(dest == ebx) 
					context->pop(eax);
				else	
					context->pop(ebx);
				if(dest == eax)
					context->pop(edx);
				else 
					context->pop(eax);

				break;
			default:
				break;
			}
			this->loc = left->loc;
			MemoryUnit* mu = context->find(this->value->var);
			context->mov(mu->getPosition(),reg(this->loc),0);
			this->memory = true;
		}
	}

	void store(AsmContext* context) {
		if(!memory && loc != -1) {
			for(std::vector<Value*>::iterator it = synonym->begin(); it != synonym->end();it++) {
				Value* val = *it;
				MemoryUnit* mu = context->find(val->var,0);
				context->mov(mu->getPosition(),reg(loc),0);
			}
		}
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
			case OCALL:
				quads->push_back(this->origin);
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
