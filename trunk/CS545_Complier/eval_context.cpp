/*
 * eval_ontext.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: harper
 */

#include "eval_context.h"
#include "node.h"
#include "exception.h"

extern void error(const char* info);

EvalContext::EvalContext() {
	error = 0;
	idTable = new std::vector<std::map<char*, Declare*, comparator>*>();
	subTable = new std::map<char*, Subprogram*, comparator>();
	errors = new std::vector<char*>();

	idTable->push_back(new std::map<char*, Declare*, comparator>());
}

EvalContext::~EvalContext() {
	idTable->clear();
	delete idTable;

	subTable->clear();
	delete subTable;

	for (std::vector<char*>::iterator ite = errors->begin();
			ite != errors->end(); ite++) {
		delete *ite;
	}
	errors->clear();
	delete errors;
}

void EvalContext::addDeclare(char* id, Declare* type) {
	// Record a duplication if there is
	std::map<char*, Declare*, comparator>* current = this->idTable->back();
	if (current->find(id) != current->end()) { // Already exists, record duplication
		record(error_dup_id(type));
	}
	this->idTable->back()->insert(std::pair<char*, Declare*>(id, type));
}

Declare* EvalContext::getDeclare(char* id) {
	std::vector<std::map<char*, Declare*, comparator>*>::iterator ite =
			idTable->begin();
	for (; ite != idTable->end(); ite++) {
		if ((*ite)->find(id) != (*ite)->end()) {
			return (*ite)->find(id)->second;
		}
	}
	return NULL;
}

void EvalContext::addSub(char*id, Subprogram* def) {
	if (subTable->find(id) != subTable->end()) { // Already exists, record duplication
		record(error_dup_id(def));
	}
	subTable->insert(std::pair<char*, Subprogram*>(id, def));
}

Subprogram* EvalContext::getSub(char* id) {
	if (subTable->find(id) != subTable->end())
		return subTable->find(id)->second;
	return NULL;
}

Subprogram* EvalContext::getCurrent() {
	return current;
}

void EvalContext::record(char* context) {
	this->error = 1;
	errors->push_back(context);
}

bool EvalContext::haserror() {
	return error;
}

void EvalContext::showerror() {
	if (error) {
		for (std::vector<char*>::iterator listit = errors->begin();
				listit != errors->end(); listit++) {
			::error(*listit);
		}
	}
}

void EvalContext::pushFrame(Subprogram* sub) {
	current = sub;
	idTable->push_back(new std::map<char*, Declare*, comparator>());
}

void EvalContext::popFrame() {
	current = NULL;
	idTable->pop_back();
}
