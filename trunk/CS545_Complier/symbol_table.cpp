/*
 * symbol_table.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: harper
 */

#include "symbol_table.h"

SymbolTable::SymbolTable() {
	idTable = new std::vector<std::map<const char*, MemoryUnit*, comp>*>();
	stackArea = new std::vector<std::list<MemoryUnit*>*>();

	heap = new std::list<MemoryUnit*>();

	idTable->push_back(new std::map<const char*, MemoryUnit*, comp>());
	stackArea->push_back(new std::list<MemoryUnit*>());
}

SymbolTable::~SymbolTable() {
	idTable->clear();
	delete idTable;

	stackArea->clear();
	delete stackArea;

	delete heap;
}

void SymbolTable::add(const char* id, MemoryUnit* loc) {
	idTable->back()->insert(std::pair<const char*, MemoryUnit*>(id, loc));
}

MemoryUnit* SymbolTable::allocOnStack(int size) {
	std::list<MemoryUnit*>::iterator it = stackArea->back()->begin();
	MemoryUnit* prev = NULL;
	for (; it != stackArea->back()->end(); it++) {
		if (prev != NULL && (*it)->getPosition() - prev->getEnd() >= size) {
			MemoryUnit *m = new MemoryUnit((*it)->getEnd(), size, false);
			stackArea->back()->insert(it, m);
			return m;
		}
		prev = *it;
	}
	MemoryUnit* m = new MemoryUnit(((NULL == prev) ? 0 : prev->getEnd()), size,
			false);
	heap->push_back(m);
	return m;
}

void SymbolTable::releaseStack(MemoryUnit* alloc) {
	for (std::list<MemoryUnit*>::iterator it = stackArea->back()->begin();
			it != stackArea->back()->end(); it++) {
		if (*it == alloc) {
			stackArea->back()->erase(it);
			return;
		}
	}
}

int SymbolTable::stackSize() {
	return stackArea->back()->size();
}

MemoryUnit* SymbolTable::allocOnHeap(int size) {
	// TODO Check total available memory
	std::list<MemoryUnit*>::iterator it = heap->begin();
	MemoryUnit* prev = NULL;
	for (; it != heap->end(); it++) {
		if (prev != NULL && (*it)->getPosition() - prev->getEnd() >= size) {
			MemoryUnit *m = new MemoryUnit((*it)->getEnd(), size, true);
			heap->insert(it, m);
			return m;
		}
		prev = *it;
	}
	MemoryUnit* m = new MemoryUnit(((NULL == prev) ? 0 : prev->getEnd()), size,
			true);
	heap->push_back(m);
	return m;
}

void SymbolTable::releaseHeap(MemoryUnit* alloc) {
	for (std::list<MemoryUnit*>::iterator it = heap->begin(); it != heap->end();
			it++) {
		if (*it == alloc) {
			heap->erase(it);
			return;
		}
	}
}

MemoryUnit* SymbolTable::find(const char* id) {
	for (int i = idTable->size() - 1; i >= 0; i--) {
		std::map<const char*, MemoryUnit*, comp>* map = idTable->at(i);
		if (map->find(id) != map->end()) {
			return map->find(id)->second;
		}
	}
	return NULL;
}

MemoryUnit* SymbolTable::find(const char* id, int level) {
	std::map<const char*, MemoryUnit*, comp>* map = idTable->at(
			idTable->size() - 1 - level);
	if (map->find(id) != map->end()) {
		return map->find(id)->second;
	}
	return NULL;
}

void SymbolTable::pushFrame() {
	idTable->push_back(new std::map<const char*, MemoryUnit*, comp>());
}

void SymbolTable::popFrame() {
	idTable->pop_back();
}
