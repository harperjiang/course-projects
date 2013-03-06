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
	roots = new std::vector<QuadNode*>();
}

QuadContext::~QuadContext() {
	delete quads;
	delete roots;
	delete nodeMap;
	delete valueMap;
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

QuadNode* QuadContext::get(Value* value) {
	if(value->type == TYPE_NUM) {
		if(NULL == valueMap->find(value->value)) {
			resultNode = new QuadNode(value);
			valueMap->insert(std::pair<int,QuadNode*>(value->value, resultNode));
		} else {
			resultNode = valueMap->find(value->value);
		}
	} else {
		resultNode = nodeMap->find(value->var);
	}
	return resultNode;
}

QuadNode* QuadContext::get(OPR opr, QuadNode* left, QuadNode* right) {
	char* key = new char[30];
	QuadNode* result = NULL;
	sprintf(key, "%d %d %d",left->number,opr,right->number);
	if((result = nodeMap->find(key))!= NULL) {
		delete key;
	} else {
		result = new QuadNode(opr,left,right);
		nodeMap->insert(std::pair<char*, QuadNode*>(key,result));
	}
	return result;
}

void QuadContext::add(Quadruple* quad) {
	QuadNode* resultNode = NULL;
	switch(quad->opr) {
	case OASSIGN:
		// If an assignment 
		resultNode = get(quad->right->value);
		break;
	case OPARAM:
	case OCALL:
		// Do nothing for these now
		break;
	case OADD:
	case OSUB:
	case OMUL:
	case ODIV:
	case OMOD:
		// If a binary operation
		QuadNode* left = get(quad->left);
		QuadNode* right = get(quad->right);
		// Try to find an existing operator, create one if fails
		resultNode = get(quad->opr,left,right);
		break;
	default:
		break;
	}	
	if(NULL != resultNode) {
		QuadNode* someExist = nodeMap->find(quad->result->var);
		if(someExist != NULL && someExist != resultNode) {
			// An name comes with some new value, remove it from the original value
			someExist->removeSynonym(quad->result->var);
		}
		nodeMap->insert(std::map<char*,QuadNode*>(quad->result->var,resultNode);
		resultNode->addSynonym(quad->result->var);
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
