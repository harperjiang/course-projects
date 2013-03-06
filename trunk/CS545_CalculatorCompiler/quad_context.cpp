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
	nodeMap = new std::map<char*, QuadNode*, comp>();
	valueMap = new std::map<int, QuadNode*>();
	varCount = 0;
	root = NULL;
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

void QuadContext::get(Value* value) {


}
void QuadContext::add(Quadruple* quad) {
	QuadNode* resultNode = NULL;
	switch(quad->opr) {
	case OASSIGN:
	// If an assignment 
		if(quad->right->type == TYPE_NUM) {
			if(NULL == valueMap->find(quad->right->value)) {
				resultNode = new QuadNode(quad->right);
				valueMap->insert(std::map<int,QuadNode*>(quad->right->value, resultNode));
			} else {
				resultNode = valueMap->find(quad->right->value);
			}
		} else {
			resultNode = nodeMap->find(quad->right->var);
		}
		resultNode->addSynonym(quad->result->var);
		nodeMap->insert(std::map<char*, QuadNode*>(quad->result->var, resultNode));
		break;
	case OADD:
	case OSUB:
	case OMUL:
	case ODIV:
	case OMOD:
	default:
		break;
	}	
	quads->push_back(quad);
}

Value* QuadContext::newvar() {
	char* name= new char[10];
	sprintf(name,"%s%d","var",varCount++);
	Value* val = new Value(name);
	val->temp = true;
	return val;
}

Value* QuadContext::lastresult() {
	Quadruple* last = quads->back();
	if(NULL == last) {
		return NULL;
	}
	return last->result;
}
