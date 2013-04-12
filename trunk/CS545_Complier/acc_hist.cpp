/*
 * acc_hist.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: harper
 */

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

Node* AccessHistory::find(std::type_info type) {
	for (int i = history->size() - 1; i >= 0; i--) {
		if (typeid(history->at(i)) == type)
			return history->at(i);
	}
	return NULL;
}

std::vector<Node*>* AccessHistory::gethistory() {
	return history;
}
