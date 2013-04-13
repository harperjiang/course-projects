/*
 * acc_history.h
 *
 *  Created on: Apr 11, 2013
 *      Author: harper
 */

#ifndef ACC_HISTORY_H_
#define ACC_HISTORY_H_

#include <vector>

class Node;

class AccessHistory {
private:
	std::vector<Node*>* history;
public:
	AccessHistory();
	virtual ~AccessHistory();

	void push(Node*);
	void pop();
	Node* find(const char* type);
	std::vector<Node*>* gethistory();
};

#endif
