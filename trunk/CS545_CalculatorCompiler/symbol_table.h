/*
 * symbol_table.h
 *
 *  Created on: Feb 19, 2013
 *      Author: harper
 */

#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <vector>
#include <map>
#include <list>
#include <string.h>
#include "common.h"

class MemoryUnit {
private:
	int position;
	int size;
	bool onHeap;
public:
	MemoryUnit(int pos, int siz,bool oh) {
		this->position = pos;
		this->size = siz;
		this->onHeap = oh;
	}

	bool isOnHeap() {
		return this->onHeap;
	}

	int getPosition() {
		return position;
	}

	int getSize() {
		return size;
	}

	long getEnd() {
		return position + size;
	}
};

class SymbolTable {
private:
	std::vector<std::map<const char*, MemoryUnit*, comp> *> *idTable;
	std::vector<std::list<MemoryUnit*>*> *stackArea;

	std::list<MemoryUnit*> *heap;
public:
	SymbolTable();
	virtual ~SymbolTable();

	void add(const char* id, MemoryUnit* loc);

	MemoryUnit* allocOnStack(int size);
	void releaseStack(MemoryUnit* unit);
	int stackSize();

	MemoryUnit* allocOnHeap(int size);
	void releaseHeap(MemoryUnit* unit);

	MemoryUnit* find(const char* id);
	MemoryUnit* find(const char* id, int level);

	void pushFrame();
	void popFrame();
};

#endif /* SYMBOL_TABLE_H_ */
