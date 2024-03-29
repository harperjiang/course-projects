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
	std::vector<QuadNode*> *roots;
	AsmContext* asmContext;
protected:
	QuadNode* get(OPR opr, QuadNode* left, QuadNode* right);
	QuadNode* get(Value* value);
	void removeRoot(QuadNode* node);
public:
	QuadContext(AsmContext* asmcontext);
	virtual ~QuadContext();

	void reset();

	void add(Quadruple* quad);
	Value* lastresult();	
	Value* newvar();

	void genasm();
	
	AsmContext* getAsmContext() {
		return asmContext;
	}
};

#endif /* QUAD_CONTEXT_H_ */
