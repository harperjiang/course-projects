/*
 * quad_context.h
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#ifndef QUAD_CONTEXT_H_
#define QUAD_CONTEXT_H_

#include "asm_context.h"
#include "quadruple.h"
#include <vector>
#include <map>
#include "symbol_table.h"

class QuadContext {

private:
	std::vector<Quadruple*>* quads;
	std::map<char*, QuadNode*, comp>* nodeMap;	
	std::map<int, QuadNode*>* valueMap;
	int varCount;
	QuadNode* root;
protected:
	QuadNode* get(Value* value);
public:
	QuadContext();
	virtual ~QuadContext();

	void add(Quadruple* quad);
	Value* lastresult();	

	Value* newvar();

	void genasm(AsmContext* context);
};

#endif /* QUAD_CONTEXT_H_ */
