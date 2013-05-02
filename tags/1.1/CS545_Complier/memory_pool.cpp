/*
 * memory_pool.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: harper
 */

#include "memory_pool.h"

std::vector<MemoryPool*>* MemoryPool::pools = new std::vector<MemoryPool*>();

MemoryPool::MemoryPool() {
	pool = new std::vector<void*>();
	MemoryPool::pools->push_back(this);
}

MemoryPool::~MemoryPool() {
	for (std::vector<void*>::iterator ite = pool->begin(); ite != pool->end();
			ite++) {
		delete *ite;
	}
	pool->clear();
	delete pool;
}

void MemoryPool::add(void* member) {
	pool->push_back(member);
}

static void MemoryPool::clear() {
	for (std::vector<void*>::iterator ite = pools->begin(); ite != pools->end();
			ite++) {
		delete *ite;
	}
	pools->clear();
	delete pools;
}

