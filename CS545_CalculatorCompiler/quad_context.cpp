/*
 * quad_context.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#include <stdio.h>
#include <algorithm>
#include "quad_context.h"


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
	quads = new std::vector<Quadruple*>();
	nodeMap = new std::map<char*, QuadNode*, comp>();
	valueMap = new std::map<int, QuadNode*>();
	varCount = 0;
	roots = new std::vector<QuadNode*>();
	asmContext = conc;
}

QuadContext::~QuadContext() {
	quads->clear();
	delete quads;
	nodeMap->clear();
	delete nodeMap;
	valueMap->clear();
	delete valueMap;
	roots->clear();
	delete roots;
}

void QuadContext::reset() {
	quads->clear();
	nodeMap->clear();
	valueMap->clear();
	roots->clear();
	varCount = 0;
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
		(*it)->label(0);
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

QuadNode* QuadContext::get(OPR opr, QuadNode* left, QuadNode* right) {
	char* key = new char[30];
	QuadNode* result = NULL;
	sprintf(key, "%d %d %d", left->number, opr, right->number);
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

void QuadContext::add(Quadruple* quad) {
	QuadNode* resultNode = NULL;
	switch (quad->opr) {
	case OASSIGN:
		// If an assignment 
		resultNode = get(quad->right);
		break;
	case OPARAM:
		resultNode = get(quad->right);
		resultNode = new QuadNode(OPARAM, NULL, resultNode);
		break;
	case OCALL:
		// Save the origin call
		resultNode = new QuadNode(OCALL, NULL, new QuadNode(quad->right));
		resultNode->origin = quad;
		break;
	case OADD:
	case OSUB:
	case OMUL:
	case ODIV:
	case OMOD: {
		// If a binary operation
		QuadNode* left = get(quad->left);
		QuadNode* right = get(quad->right);
		// Try to find an existing operator, create one if fails
		resultNode = get(quad->opr, left, right);
	}
		break;
	default:
		break;
	}
	if (NULL != resultNode) {
		roots->push_back(resultNode);
		if (NULL != quad->result) {
			// For the normal ones with a result
			QuadNode* someExist = nodeMap->find(quad->result->var)->second;
			if (someExist != NULL && someExist != resultNode) {
				// An name comes with some new value, remove it from the original value
				someExist->removeSynonym(quad->result);
			}
			nodeMap->insert(
					std::pair<char*, QuadNode*>(quad->result->var, resultNode));
			resultNode->addSynonym(quad->result);
		} else {
			// For those without result, PARAM or CALL
		}
	}
	quads->push_back(quad);
}

Value* QuadContext::newvar() {
	char* name = new char[10];
	sprintf(name, "%s%d", "var", varCount++);
	Value* val = new Value(name);
	val->temp = true;
	return val;
}

Value* QuadContext::lastresult() {
	Quadruple* last = quads->back();
	if (NULL == last) {
		return NULL;
	}
	return last->result;
}
