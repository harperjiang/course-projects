/*
 * acc_hist.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: harper
 */
 
 #include "acc_history.h"
 
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

Node* AccessHistory::find(std::typeinfo type) {
	for(int i = history->size()-1;i>=0;i--) {
		if(typeid(history->at(i)) == type)
			return history->at(i);
	}
	return NULL;
}

std::vector<Node*>* gethistory() {
	return history;
}
