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
	subTable = new std::vector<std::map<char*, Subprogram*, comparator>*>();
	errors = new std::vector<char*>();

	history = new AccessHistory();

	idTable->push_back(new std::map<char*, Declare*, comparator>());
	subTable->push_back(new std::map<char*, Subprogram*, comparator>());
	current = new std::stack<Subprogram*>();
}

EvalContext::~EvalContext() {
	for (std::vector<std::map<char*, Declare*, comparator>*>::iterator ite =
			idTable->begin(); ite != idTable->end(); ite++) {
		(*ite)->clear();
		delete (*ite);
	}
	idTable->clear();
	delete idTable;

	for (std::vector<std::map<char*, Subprogram*, comparator>*>::iterator ite =
			subTable->begin(); ite != subTable->end(); ite++) {
		(*ite)->clear();
		delete (*ite);
	}
	subTable->clear();
	delete subTable;

	for (std::vector<char*>::iterator ite = errors->begin();
			ite != errors->end(); ite++) {
		delete *ite;
	}
	errors->clear();
	delete errors;

	while (!current->empty())
		current->pop();
	delete current;
}

void EvalContext::access(Node* node) {
	history->push(node);
}

void EvalContext::done() {
	// Don't do boundary check
	history->pop();
}

Node* EvalContext::findhistory(const char* type) {
	return history->find(type);
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
	// from back to front
	for (int i = idTable->size() - 1; i >= 0; i--) {
		std::map<char*, Declare*, comparator>* level = idTable->at(i);
		if (level->find(id) != level->end()) {
			return level->find(id)->second;
		}
	}
	return NULL;
}

void EvalContext::addSub(char*id, Subprogram* def) {
	std::map<char*, Subprogram*, comparator>* currentTable = subTable->back();
	if (currentTable->find(id) != currentTable->end()) { // Already exists, record duplication
		record(error_dup_id(def));
	}
	currentTable->insert(std::pair<char*, Subprogram*>(id, def));
}

Subprogram* EvalContext::getSub(char* id) {
	for (int i = subTable->size() - 1; i >= 0; i--) {
		std::map<char*, Subprogram*, comparator>* ct = subTable->at(i);
		if (ct->find(id) != ct->end())
			return ct->find(id)->second;
	}
	return NULL;
}

Subprogram* EvalContext::getCurrent() {
	if(current->empty())
		return NULL;
	return current->top();
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
	current->push(sub);
	idTable->push_back(new std::map<char*, Declare*, comparator>());
	subTable->push_back(new std::map<char*, Subprogram*, comparator>());
	access(sub);
}

void EvalContext::popFrame() {
	done();
	current->pop();
	idTable->pop_back();
	subTable->pop_back();
}
