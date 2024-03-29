/*
 * act_record.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: harper
 */

#include "act_record.h"
#include "node.h"
#include "asm_context.h"

ActivationRecord::ActivationRecord(bool fm) {
	formain = fm;
	table = new std::map<char*, int, comp>();
	// ebp - 4 -> local vars
	// ebp     -> old ebp
	// ebp + 4 -> ret val
	// ebp + 8 -> frame ref
	// ebp + 12 and more -> param
	localVarPointer = 0;
	paramPointer = 12;
}

void ActivationRecord::add(Declare* var) {
	if (typeid(*(var->getType())) == typeid(ArrayType)) {
		ArrayType* at = (ArrayType*) var->getType();
		int size = at->end - at->begin + 1;
		localVarPointer -= 4 * size;
	} else {
		localVarPointer -= 4;
	}
	table->insert(std::pair<char*, int>(var->name->name, localVarPointer));
}

void ActivationRecord::addparam(Param* param) {
	// TODO Param can't be an array type, add this check
	table->insert(std::pair<char*, int>(param->name->name, paramPointer));
	paramPointer += 4;
}

int ActivationRecord::offset(char* var) {
	if (table->find(var) == table->end()) {
		return -1;
	}
	return table->find(var)->second;
}

void ActivationRecord::gencode(AsmContext* context) {
	// begin
	context->push(ebp);
	context->mov(ebp, esp);

	// allocate local variables
	if (localVarPointer != 0)
		context->sub(esp, -localVarPointer);
}

void ActivationRecord::genclean(AsmContext* context) {
	context->leave();
	if (!formain) {
		// need to clean param from stack
		// things to clean: return + frame + param
		// maintain return address

		// no saved ebp now
		// esp should be esp - (paramPointer - 4) + 4
		// esp = esp - paramPointer + 4
		context->mov(ebx, esp, 1);
		context->lea(esp, esp, paramPointer - 8);
		context->mov(esp, ebx, 2);
	}
}
