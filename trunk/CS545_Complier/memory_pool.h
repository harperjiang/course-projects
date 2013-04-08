/*
 * memory_pool.h
 *
 *  Created on: Apr 8, 2013
 *      Author: harper
 */

#ifndef MEMORY_POOL_H_
#define MEMORY_POOL_H_

#include <vector>

class MemoryPool {
private:
	static std::vector<MemoryPool*>* pools;

	std::vector<void*>* pool;
public:
	MemoryPool();
	virtual ~MemoryPool();

	void add(void*);

	static void clear();
};

#endif /* MEMORY_POOL_H_ */
