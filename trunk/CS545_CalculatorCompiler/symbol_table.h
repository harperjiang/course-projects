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
#include <string.h>

class MemoryUnit {
private:
	int position;
	int size;
public:
	MemoryUnit(int pos, int siz) {
		this->position = pos;
		this->size = siz;
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

struct comp {
	bool operator()(const char* a, const char* b) {
		return strcmp(a, b) < 0;
	}
};

class SymbolTable {
private:
	std::vector<std::map<char*, MemoryUnit*, comp> *> *idTable;
public:
	SymbolTable();
	virtual ~SymbolTable();

	void add(char* id, MemoryUnit* loc);
	MemoryUnit* find(char* id);
	MemoryUnit* find(char* id, int level);

	void pushFrame();
	void popFrame();
};

#endif /* SYMBOL_TABLE_H_ */
