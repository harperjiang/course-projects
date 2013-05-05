/*
 * quadruple.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#include "quadruple.h"
#include "memory_pool.h"
#include "act_record.h"
#include "reg_context.h"

static int QUAD_COUNTER = 0;

MemoryPool<Value>* valuePool = new MemoryPool<Value>();
MemoryPool<QuadNode>* quadnodePool = new MemoryPool<QuadNode>();

void Value::init() {
	valuePool->add(this);
}

void QuadNode::init() {	
	number = QUAD_COUNTER++;

	processed = false;
	synonym = new std::vector<Value*>();
	loc= unknown;
	memory = false;
	refCount = 0;
	quadnodePool->add(this);
}

QuadNode::QuadNode(Value* value) {
	init();
	this->value = value;
	this->left = NULL;
	this->right = NULL;
	this->opr = QUAD_NONE;
}

QuadNode::QuadNode(QuadOpr opr, QuadNode* left, QuadNode* right) {
	init();	
	this->opr = opr;
	this->left = left;
	this->right = right;
	this->value = NULL;
}

QuadNode::~QuadNode() {
	if(synonym!= NULL) {
		synonym->clear();
		delete synonym;
	}
	synonym = NULL;
	left = NULL;
	right = NULL;
}

void QuadNode::addSynonym(Value* name) {
	this->removeSynonym(name);
	synonym->push_back(name);
}

void QuadNode::removeSynonym(Value* name) {
	for (std::vector<Value*>::iterator it = synonym->begin(); it != synonym->end(); it++) {
		if (name == *it) {
			synonym->erase(it);
			return;
		}
	}
}

void QuadNode::cleanSynonym() {
	if (left != NULL)
		left->cleanSynonym();
	if (right != NULL)
		right->cleanSynonym();
	if(synonym == NULL || synonym->size() == 0)
		return;
	refCount = synonym->size();
	Value* reserve = NULL;
	
	for (std::vector<Value*>::iterator it = synonym->begin(); it != synonym->end(); it++) {
		if (!(*it)->temp) {
			reserve = *it;
			break;
		}
	}
	if (reserve == NULL) {
		reserve = synonym->at(0);
		synonym->erase(synonym->begin());
	}
	
	synonym->clear();
	delete synonym;
	synonym = NULL;
	
	if(this->value != NULL && this->value->type == TYPE_NUM) {
		value->var = new char[strlen(reserve->var)];
		strcpy(value->var,reserve->var);
		value->temp = reserve->temp;
	} else {
		value = reserve;
	}
}

void QuadNode::genstoreasm(AsmContext* context, RegContext* regc, bool allowtemp) {
	if(!memory && loc != unknown) {
		if(value->temp && !allowtemp)
			return;
		if(NULL == value->var)
			return;
		if(value->temp) { // temp value in heap
			int offset = context->inHeap(value->var);
			Register temp = edx;
			if(edx == loc) {
				temp = esi;
			}
			if(regc->get(temp) != NULL)
				context->push(temp);
			context->mov(temp, "heap");
			context->add(temp, offset);
			context->mov(temp, loc, 2);
			if(regc->get(temp) != NULL)			
				context->pop(temp);
		} else {
			int level = 0;
			ActivationRecord* actrecord = context->getActRecord(value->var, &level);
			int offset = actrecord->offset(value->var);
			Register temp = edx;
			if(edx == loc) {
				temp = esi;
			}
			if(regc->get(temp) != NULL)			
				context->push(temp);
			if (0 == level) {
				context->lea(temp, ebp, offset);
			} else {
				context->mov(temp, ebp);
				for (int i = 0; i < level; i++) {
					// point to the frame
					context->add(temp, 8);
					context->mov(temp, temp, 1);
				}
				context->add(temp, offset);
			}
			context->mov(temp,loc,2);
			if(regc->get(temp) != NULL)
				context->pop(temp);
		}
		memory = true;
	}	
}

void QuadNode::genloadregasm(AsmContext* context, RegContext* regc) {
	if(memory && loc != unknown) {
		if(value->temp) {
			int offset = context->inHeap(value->var);
			if(loc != edx && regc->get(edx) != NULL) {
				context->push(edx);
			}
			context->mov(edx, "heap");
			context->add(edx, offset);
			context->mov(loc, edx, 1);
			if(loc != edx && regc->get(edx) != NULL) {
				context->pop(edx);
			}
		} else {
			int level = 0;
			ActivationRecord* actrecord = context->getActRecord(value->var, &level);
			int offset = actrecord->offset(value->var);
			if(loc != edx && regc->get(edx) != NULL)
				context->push(edx);
			if (0 == level) {
				context->lea(edx, ebp, offset);
			} else {
				context->mov(edx, ebp);
				for (int i = 0; i < level; i++) {
					// point to the frame
					context->add(edx, 8);
					context->mov(edx, edx, 1);
				}
				context->add(edx, offset);
			}		
			context->mov(loc,edx,1);
			if(loc != edx && regc->get(edx) != NULL)
				context->pop(edx);
			return;
		}
	}
}

void QuadNode::gencleanregasm(AsmContext* context, RegContext* regc, bool usenow) {
	// if use now, check the ref count, 
	// if ref count == 0, this item can be ignored safely
	if(!(usenow && refCount <= 0))
		genstoreasm(context,regc,true);
	regc->clean(loc);
	loc = unknown;
}

void QuadNode::gentwinasm(AsmContext* context, RegContext* regc) {
	left->genasm(context,regc);
	right->genasm(context,regc);
	if(left->loc == unknown) {
		// left was thrown out, get it back
		Register avail = regc->avail();	
		if(avail == unknown) {
			// Randomly choose a register
			Register next = regc->next();
			regc->get(next)->gencleanregasm(context,regc,false);
			avail = next;
		}
		regc->put(avail, left);
		left->loc = avail;
		// Gen load asm
		left->genloadregasm(context,regc);
	}
}

void QuadNode::genallocregasm(AsmContext* context, RegContext* regc) {
	Register avail;
	if(this->loc != unknown)
		return;
	// Allocate 
	avail = regc->avail();
	if(avail == unknown) {
		// Clean an unlock register 	
		Register next = regc->next();
		regc->get(next)->gencleanregasm(context,regc,false);
		avail = next;
	}
	regc->put(avail, this);
	this->loc = avail;
}

void QuadNode::genasm(AsmContext* context, RegContext* regc) {
	// Decrease ref count
	refCount --;
	if(processed) {
		genallocregasm(context,regc);
		if(value->type == TYPE_NUM) {
				context->mov(loc, value->value);
		} else {
			genloadregasm(context,regc);
		}
		return;
	}
	Register dest, src;
	switch(opr) {
		case QUAD_NONE:
			genallocregasm(context, regc);
			if(value->type == TYPE_NUM) {
				context->mov(loc, value->value);
			} else {
				genloadregasm(context,regc);
			}
			break;
		case QUAD_PARAM:
			right->genasm(context,regc);
			context->push(right->loc);
			break;
		case QUAD_LOAD:
			right->genasm(context,regc);
			genallocregasm(context, regc);
			context->mov(loc, right->loc, 1);
			break;
		case QUAD_SAVE:
			gentwinasm(context, regc);
			context->mov(left->loc, right->loc, 2);
			break;
		case QUAD_ADDR: {
			genallocregasm(context, regc);
			int level = 0;
			ActivationRecord* actrecord = context->getActRecord(right->value->var, &level);
			int offset = actrecord->offset(right->value->var);
			if (0 == level) {
				context->lea(loc, ebp, offset);
			} else {
				context->mov(loc, ebp);
				for (int i = 0; i < level; i++) {
					// point to the frame
					context->add(loc, 8);
					context->mov(loc, loc, 1);
				}
				context->add(loc, offset);
			}				
			break;
		}
		case QUAD_ADD:
			gentwinasm(context,regc);
			dest = left->loc;
			src = right->loc;
			// store left node as we will update the info to be the new node
			left->gencleanregasm(context,regc,true);
			context->add(dest,src);
			this->loc = dest;
			this->memory = false;
			regc->put(dest,this);
			break;
		case QUAD_SUB:
			gentwinasm(context,regc);
			dest = left->loc;
			src = right->loc;
			// store left node as we will update the info to be the new node
			left->gencleanregasm(context,regc,true);
			context->sub(dest,src);
			this->loc = dest;
			this->memory = false;
			regc->put(dest,this);
			break;
		case QUAD_MUL: 
			gentwinasm(context,regc);
			dest = left->loc;
			src = right->loc;
			// store left node as we will update the info to be the new node
			left->gencleanregasm(context,regc,true);
			
			if(dest != edx)
				context->push(edx);
			if(dest != eax)
				context->push(eax);
	
			if(src != eax) {
				context->mov(eax,dest);
				context->mul(src);
			} else { // src == eax
				if(dest != edx) {
					context->mov(edx,src);
					context->mov(eax,dest);
				} else { // src == eax, dest == edx
					context->push(dest);
					context->push(src);
					context->pop(edx);
					context->pop(eax);			
				}
				context->mul(edx);	
			}
			context->mov(dest,eax);
	
			if(dest != eax)
				context->pop(eax);
			if(dest != edx)
				context->pop(edx);
			this->loc = dest;
			this->memory = false;
			regc->put(dest,this);
			break;	
		case QUAD_DIV:
			gentwinasm(context,regc);
			dest = left->loc;
			src = right->loc;
			// store left node as we will update the info to be the new node
			left->gencleanregasm(context,regc,true);
			
			if(dest != edx)
				context->push(edx);
			if(dest != eax)
				context->push(eax);
			if(dest != ebx)
				context->push(ebx);
		
			if(dest != ebx){
				context->mov(ebx,src);
				context->mov(eax,dest);
			} else if (src != eax) {
				context->mov(eax,dest);
				context->mov(ebx,src);
			} else {
				context->push(src);
				context->push(dest);
				context->pop(eax);
				context->pop(ebx);
			}
			context->mov(edx,0);
	
			context->div(ebx);

			context->mov(dest,eax);

			if(dest != ebx)
				context->pop(ebx);
			if(dest != eax)
				context->pop(eax);
			if(dest != edx)
				context->pop(edx);
			this->loc = dest;
			this->memory = false;
			regc->put(dest,this);
			break;
		case QUAD_MOD:
			gentwinasm(context,regc);
			dest = left->loc;
			src = right->loc;
			// store left node as we will update the info to be the new node
			left->gencleanregasm(context,regc,true);
			
			if(dest != edx)
				context->push(edx);
			if(dest != eax)
				context->push(eax);
			if(dest != ebx)
				context->push(ebx);
		
			if(dest != ebx){
				context->mov(ebx,src);
				context->mov(eax,dest);
			} else if (src != eax) {
				context->mov(eax,dest);
				context->mov(ebx,src);
			} else {
				context->push(src);
				context->push(dest);
				context->pop(eax);
				context->pop(ebx);
			}
			context->mov(edx,0);
	
			context->div(ebx);

			context->mov(dest,edx);

			if(dest != ebx)
				context->pop(ebx);
			if(dest != eax)
				context->pop(eax);
			if(dest != edx)
				context->pop(edx);
			this->loc = dest;
			this->memory = false;
			regc->put(dest,this);
			break;
		default:
			break;
	}
	this->genstoreasm(context,regc,false);
	processed = true;
}
