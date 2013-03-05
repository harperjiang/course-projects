/*
 * eval_ontext.cpp
 *
 *  Created on: Feb 10, 2013
 *      Author: harper
 */

#include "eval_context.h"
#include "exception.h"

EvalContext::EvalContext() {
	error = 0;
	idTable = new std::vector<std::map<char*, char*, comparator>*>();
	errors = new std::map<int, std::vector<char*>*>();

	idTable->push_back(new std::map<char*, char*, comparator>());
}

EvalContext::~EvalContext() {
	idTable->clear();
	delete idTable;

	errors->clear();
	delete errors;
}

void EvalContext::addId(char* id) {
	this->idTable->back()->insert(std::pair<char*, char*>(id, id));
}

void EvalContext::check(char* id) {
	char* buffer = new char[100];
	std::vector<std::map<char*, char*, comparator>*>::iterator ite =
			idTable->begin();
	for (; ite != idTable->end(); ite++) {
		if ((*ite)->find(id) != (*ite)->end()) {
			return;
		}
	}
	sprintf(buffer, "Variable %s was used before it was declared", id);
	record(UNDEFINED_ID, buffer);
}

void EvalContext::record(int type, char* context) {
	this->error = 1;
	if (errors->end() == errors->find(type)) {
		std::vector<char*> * newvec = new std::vector<char*>();
		newvec->push_back(context);
		errors->insert(std::pair<int, std::vector<char*>*>(type, newvec));
	} else {
		errors->find(type)->second->push_back(context);
	}
}

int EvalContext::geterror() {
	return error;
}

void EvalContext::showerror(FILE* output) {
	if (error) {
		for (std::map<int, std::vector<char*>*>::iterator it = errors->begin();
				it != errors->end(); it++) {
			for (std::vector<char*>::iterator listit = it->second->begin();
					listit != it->second->end(); listit++) {
				fprintf(output, "%s\n", *listit.base());
			}
		}
	}
}

void EvalContext::pushFrame() {
	idTable->push_back(new std::map<char*, char*, comparator>());
}

void EvalContext::popFrame() {
	idTable->pop_back();
}
