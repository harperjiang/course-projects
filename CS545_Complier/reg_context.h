/*
 * reg_context.h
 *
 *  Created on: May 5, 2013
 *      Author: harper
 */

#ifndef REG_CONTEXT_H_
#define REG_CONTEXT_H_

#define NO_AVAIL_REG 10
#define REG_LOCKED 20

#include <stdio.h>
#include <map>
#include "quadruple.h"

class RegContext {
private:
	std::map<Register,QuadNode*>* nodes;
	std::map<Register,bool>* locks;
	int nextpointer;
public:
	RegContext() {
		nodes = new std::map<Register,QuadNode*>();
		locks = new std::map<Register,bool>();
		nextpointer = 0;
	}

	virtual ~RegContext() {
		delete nodes;
		delete locks;
	}

	Register next() {
		Register retval = unknown;
		int start = nextpointer;
		while(nextpointer - start < 6) {
			retval = reg((nextpointer++)%6);
			if(!islock(retval))
				return retval;
		}
		return unknown;
	}

	Register avail() {
		for(int i = 0 ; i < 6 ; i++) {
			if(get(reg(i)) == NULL)
				return reg(i);
		}
		return unknown;
	}

	QuadNode* get(Register reg) {
		if(nodes->find(reg) == nodes->end())
			return NULL;
		return nodes->find(reg)->second;
	}

	void clean(Register reg) {
		if(islock(reg))
			throw REG_LOCKED;
		nodes->erase(reg);
	}

	void put(Register reg, QuadNode* node) {
		if(islock(reg) && get(reg) != node)
			throw REG_LOCKED;
		nodes->insert(std::pair<Register,QuadNode*>(reg,node));
	}

	void lock(Register reg) {
		locks->insert(std::pair<Register,bool>(reg,true));
	}

	void unlock(Register reg) {
		locks->erase(reg);
	}

	bool islock(Register reg) {
		return locks->find(reg) != locks->end() && locks->find(reg)->second;
	}
};


#endif /* REG_CONTEXT_H_ */
