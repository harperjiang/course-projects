/*
 * quadruple.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#include "quadruple.h"

static int QUAD_COUNTER = 0;

Quadruple::~Quadruple() {
	// Do nothing as it will cause double deleting in QuadNode
}

QuadNode::QuadNode(Value* value) {
	number = QUAD_COUNTER++;
	this->value = value;
	this->left = NULL;
	this->right = NULL;
	synonym = new std::vector<Value*>();
	origin = NULL;
	processed = false;

	ilabel = 0;
	loc = unknown;
	memory = false;
	refCount = 0;
}

QuadNode::QuadNode(OPR opr, QuadNode* left, QuadNode* right) {
	number = QUAD_COUNTER++;
	this->opr = opr;
	this->left = left;
	this->right = right;
	synonym = new std::vector<Value*>();
	this->value = NULL;
	origin = NULL;
	processed = false;

	ilabel = 0;
	loc= unknown;
	memory = false;
	refCount = 0;
}

QuadNode::~QuadNode() {
	if(left != NULL)
		delete left;
	if(right != NULL)
		delete right;
	synonym->clear();
	delete synonym;
	origin = NULL;
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
	if(synonym->size() == 0)
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
	
	if(this->value != NULL && this->value->type == TYPE_NUM) {
		value->var = new char[strlen(reserve->var)];
		strcpy(value->var,reserve->var);
		value->temp = reserve->temp;
	} else {
		value = reserve;
	}
}

void QuadNode::genstoreasm(AsmContext* context,bool allowtemp) {
	if(!memory && loc != unknown) {
		if(value->temp && !allowtemp)
			return;
		MemoryUnit* mu = NULL;
		mu = context->find(value->var,0);
		context->mov(mu->getPosition(),loc,0);
		memory = true;
	}
}

void QuadNode::genloadregasm(AsmContext* context) {
	if(memory && loc != unknown) {
		MemoryUnit* mu = context->find(value->var);
		if(mu != NULL) {
			context->mov(loc,mu->getPosition(),1);
			return;
		}
	}
}

void QuadNode::gencleanregasm(AsmContext* context, RegContext* regc,bool usenow) {
	// if use now, check the ref count, 
	// if ref count == 0, this item can be ignored safely
	if(!(usenow && refCount <= 0))
		genstoreasm(context,true);
	regc->clean(loc);
	loc = unknown;
}

void QuadNode::genasm(AsmContext* context, RegContext* regc) {
	// Decrease ref count
	refCount --;
	
	if((left == NULL && right == NULL) || processed) {
		if(this->loc != unknown)
			return;
		// leaf, move it to register		
		Register avail = regc->avail();
		if(avail == unknown) {
			// Clean an unlock register 	
			Register next = regc->next();
			regc->get(next)->gencleanregasm(context,regc,false);
			avail = next;
		}
		regc->put(avail, this);
		this->loc = avail;
		
		if(value->type == TYPE_NUM) {
			context->mov(avail, value->value);
		} else {
			this->memory = true;
			MemoryUnit* memloc = context->find(value->var);
			context->mov(avail,memloc->getPosition(),1); 
		}
	} else if(left == NULL) {
		// Uniary operations, call and param
		// These are all top level nodes
		switch(opr) {
		case OCALL:
			// Call operation will possibly modify all memory units.
			// Ignore parameter size now
			context->push(1);
			context->call("_print");
			break;
		case OPARAM:
			right->genasm(context,regc);
			context->push(right->loc);
			break;
		default:
			break;
		}
	} else {
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
			left->genloadregasm(context);
		}
		Register dest = left->loc;
		// store left node as we will update the info to be the new node
		left->gencleanregasm(context,regc,true);
		Register src = right->loc;
		switch(opr) {
		case OADD:
			context->add(dest,src);
			break;
		case OSUB:
			context->sub(dest,src);
			break;
		case OMUL:
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
			break;	
		case ODIV:
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
			break;
		case OMOD:
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
			break;
		default:
			break;
		}
		this->loc = dest;
		this->memory = false;
		regc->put(dest,this);
	}
	this->genstoreasm(context,false);
	processed = true;
}

void QuadNode::label(int flag) {
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

