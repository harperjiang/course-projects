/*
 * acc_hist.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: harper
 */

#include <typeinfo>
#include "node.h"
#include "acc_hist.h"

AccessHistory::AccessHistory() {
	history = new std::vector<Node*>();
}

AccessHistory::~AccessHistory() {
	history->clear();
	delete history;
}

void AccessHistory::push(Node* node) {
	history->push_back(node);
}

void AccessHistory::pop() {
	history->pop_back();
}

Node* AccessHistory::find(const char* type) {
	for (int i = history->size() - 1; i >= 0; i--) {
		if (strcmp(typeid(*(history->at(i))).name(), type) == 0)
			return history->at(i);
	}
	return NULL;
}

std::vector<Node*>* AccessHistory::gethistory() {
	return history;
}
