/*
 * quad_context.h
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#ifndef QUAD_CONTEXT_H_
#define QUAD_CONTEXT_H_

#include <vector>
#include <map>
#include "asm_context.h"
#include "quadruple.h"

class QuadContext {
private:
	std::map<char*, QuadNode*, comp>* nodeMap;	
	std::map<int, QuadNode*>* valueMap;
	int varCount;
	std::vector<QuadNode*> *roots;
	AsmContext* asmContext;
	Value* last;
	bool quitflag;
protected:
	QuadNode* get(QuadOpr opr, QuadNode* left, QuadNode* right);
	QuadNode* get(Value* value);
	void removeRoot(QuadNode* node);
public:
	QuadContext(AsmContext* asmcontext);
	virtual ~QuadContext();

	void reset();

	void add(Value* result, QuadOpr opr, Value* left, Value *right);
	Value* lastresult();
	QuadNode* lastnode();
	Value* newvar();

	void genasm();

	void quit();
	bool shouldQuit();
	
	AsmContext* getAsmContext() {
		return asmContext;
	}
};

#endif /* QUAD_CONTEXT_H_ */
