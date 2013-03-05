/*
 * quad_context.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#include <stdio.h>
#include "quad_context.h"

QuadContext::QuadContext() {
	quads = new std::vector<Quadruple*>();
	varCount = 0;
}

QuadContext::~QuadContext() {
	delete quads;
}


void QuadContext::genasm(AsmContext* context) {
	for(std::vector<Quadruple*>::iterator it = quads->begin();it != quads->end(); it++) {
		Quadruple* quad = *it;
		char* leftc = NULL;
		if(quad->left!=NULL)
			leftc=quad->left->content();
		char* rightc = quad->right->content();
		if(leftc != NULL)
			printf("%s = %s %d %s\n", quad->result->var,leftc,quad->opr,rightc);
		else 
			printf("%s = %d %s\n", quad->result->var, quad->opr,rightc);
		if(NULL != leftc)
			delete leftc;
		delete rightc;
	}
}

void QuadContext::add(Quadruple* quad) {
	quads->push_back(quad);
}

Value* QuadContext::newvar() {
	char* name= new char[10];
	sprintf(name,"%s%d","var",varCount++);
	return new Value(name);	
}

Value* QuadContext::lastresult() {
	Quadruple* last = quads->back();
	if(NULL == last) {
		return NULL;
	}
	return last->result;
}
