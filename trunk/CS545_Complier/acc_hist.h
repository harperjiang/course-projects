/*
 * acc_history.h
 *
 *  Created on: Apr 11, 2013
 *      Author: harper
 */

#ifndef ACC_HISTORY_H_
#define ACC_HISTORY_H_
#include "node.h"
#include <vector>
#include <typeinfo>

class AccessHistory {
private:
	std::vector<Node*>* history;
public:
	AccessHistory();
	virtual ~AccessHistory();
	
	void push(Node*);
	void pop();
	Node* find(std::type_info type);
	std::vector<Node*>* gethistory();
};
