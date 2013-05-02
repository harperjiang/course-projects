/*
 * memory_pool.h
 *
 *  Created on: Apr 8, 2013
 *      Author: harper
 */

#ifndef MEMORY_POOL_H_
#define MEMORY_POOL_H_

#include <vector>

template <class T>
class MemoryPool {
private:
	std::vector<T*>* pool;
public:
	MemoryPool() {
		pool = new std::vector<T*>();
	}

	virtual ~MemoryPool() {
		for (typename std::vector<T*>::iterator ite = pool->begin(); ite != pool->end();
			ite++) {
			delete *ite;
		}
		pool->clear();
		delete pool;
	}

	void add(T* member) {
		pool->push_back(member);
	}
};

#endif /* MEMORY_POOL_H_ */
