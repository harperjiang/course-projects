/*
 * symbol_table.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: harper
 */

#include "symbol_table.h"

SymbolTable::SymbolTable() {
	idTable = new std::vector<std::map<char*, MemoryUnit*, comp>*>();

	idTable->push_back(new std::map<char*, MemoryUnit*, comp>());
}

SymbolTable::~SymbolTable() {
	idTable->clear();
	delete idTable;
}

void SymbolTable::add(char* id, MemoryUnit* loc) {
	idTable->back()->insert(std::pair<char*, MemoryUnit*>(id, loc));
}

MemoryUnit* SymbolTable::find(char* id) {
	for (int i = idTable->size() - 1; i >= 0; i--) {
		std::map<char*, MemoryUnit*, comp>* map = idTable->at(i);
		if (map->find(id) != map->end()) {
			return map->find(id)->second;
		}
	}
	return 0;
}

MemoryUnit* SymbolTable::find(char* id, int level) {
	std::map<char*, MemoryUnit*, comp>* map = idTable->at(
			idTable->size() - 1 - level);
	if (map->find(id) != map->end()) {
		return map->find(id)->second;
	}
	return NULL;
}

void SymbolTable::pushFrame() {
	idTable->push_back(new std::map<char*, MemoryUnit*, comp>());
}

void SymbolTable::popFrame() {
	idTable->pop_back();
}
