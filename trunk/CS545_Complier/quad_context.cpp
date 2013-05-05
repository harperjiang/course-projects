/*
 * quad_context.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#include <stdio.h>
#include <algorithm>
#include "quad_context.h"
#include "node.h"
#include "reg_context.h"


template<class V> 
void clearVector(V* avec) {
    for (typename V::iterator it = avec->begin(); it != avec->end(); ++it ) {
        delete (*it);
    }
    avec->clear();
}

template<class M> 
void clearMap(M* amap) {
    for (typename M::iterator it = amap->begin(); it != amap->end(); ++it ) {
        delete it->second;
    }
    amap->clear();
}


QuadContext::QuadContext(AsmContext* conc) {
	nodeMap = new std::map<char*, QuadNode*, comp>();
	valueMap = new std::map<int, QuadNode*>();
	varCount = 0;
	roots = new std::vector<QuadNode*>();
	asmContext = conc;
	last = NULL;

	quitflag = false;
}

QuadContext::~QuadContext() {
	nodeMap->clear();
	delete nodeMap;
	valueMap->clear();
	delete valueMap;
	roots->clear();
	delete roots;
}

void QuadContext::reset() {
	nodeMap->clear();
	valueMap->clear();
	roots->clear();
	varCount = 0;
	quitflag = false;
	asmContext->resetHeap();
}

void QuadContext::removeRoot(QuadNode* node) {
	std::vector<QuadNode*>::iterator it = std::find(roots->begin(),
			roots->end(), node);
	if (it != roots->end()) {
		roots->erase(it);
	}
}

void QuadContext::genasm() {
	RegContext* regc = new RegContext();
	for (std::vector<QuadNode*>::iterator it = roots->begin();
			it != roots->end(); it++) {
		(*it)->cleanSynonym();
		// All registers are available
		(*it)->genasm(asmContext,regc);
	}
	delete regc;
}

QuadNode* QuadContext::get(Value* value) {
	QuadNode* resultNode = NULL;
	if (value->type == TYPE_NUM) {
		std::map<int, QuadNode*>::iterator loc = valueMap->find(value->value);
		if (valueMap->end() == loc) {
			resultNode = new QuadNode(value);
			valueMap->insert(
					std::pair<int, QuadNode*>(value->value, resultNode));
		} else {
			resultNode = loc->second;
			removeRoot(resultNode);
		}
	} else {
		std::map<char*, QuadNode*>::iterator loc = nodeMap->find(value->var);
		if (loc == nodeMap->end()) {
			// This is a variable defined somewhere else, just register it
			resultNode = new QuadNode(value);
			nodeMap->insert(
					std::pair<char*, QuadNode*>(value->var, resultNode));
			resultNode->addSynonym(value);
		} else {
			resultNode = loc->second;
			removeRoot(resultNode);
		}
	}

	return resultNode;
}

QuadNode* QuadContext::get(QuadOpr opr, QuadNode* left, QuadNode* right) {
	char* key = new char[30];
	QuadNode* result = NULL;
	sprintf(key, "%d %d %d", left == NULL?-1:left->number, opr, right->number);
	std::map<char*, QuadNode*>::iterator ite = nodeMap->find(key);
	if (ite != nodeMap->end()) {
		result = ite->second;
		removeRoot(result);
		delete key;
	} else {
		result = new QuadNode(opr, left, right);
		nodeMap->insert(std::pair<char*, QuadNode*>(key, result));
	}
	return result;
}

void QuadContext::add(Value* result, QuadOpr opr, Value* left, Value *right) {
	QuadNode* resultNode = NULL;
	switch (opr) {
	case QUAD_ASSIGN:
		// If an assignment 
		resultNode = get(right);
		break;
	case QUAD_PARAM:
	case QUAD_LOAD:
	case QUAD_ADDR:
		// If a uniary operation
		resultNode = get(right);
		resultNode = get(opr, NULL, resultNode);
		break;
	case QUAD_SAVE:
	case QUAD_ADD:
	case QUAD_SUB:
	case QUAD_MUL:
	case QUAD_DIV:
	case QUAD_MOD: {
		// If a binary operation
		QuadNode* qleft = get(left);
		QuadNode* qright = get(right);
		// Try to find an existing operator, create one if fails
		resultNode = get(opr, qleft, qright);
	}
		break;
	default:
		break;
	}
	if (NULL != resultNode) {
		roots->push_back(resultNode);
		if (NULL != result) {
			// For the normal ones with a result
			QuadNode* someExist = NULL;
			if(nodeMap->find(result->var) != nodeMap->end()) {
				someExist = nodeMap->find(result->var)->second;
			}
			if (someExist != NULL && someExist != resultNode) {
				// An name comes with some new value, remove it from the original value
				someExist->removeSynonym(result);
			}
			nodeMap->insert(
					std::pair<char*, QuadNode*>(result->var, resultNode));
			resultNode->addSynonym(result);
		} else {
			// For those without result, PARAM or CALL
		}
	}
	last = result;
}

Value* QuadContext::newvar() {
	char* name = new char[10];
	sprintf(name, "%s%d", "var", varCount++);
	Value* val = new Value(name);
	val->temp = true;
	return val;
}

Value* QuadContext::lastresult() {
	return last;
}

QuadNode* QuadContext::lastnode() {
	return roots->back();
}

void QuadContext::quit() {
	this->quitflag = true;
}

bool QuadContext::shouldQuit() {
	return this->quitflag;
}
