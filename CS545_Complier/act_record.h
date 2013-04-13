/*
 * act_record.h
 *
 *  Created on: Apr 11, 2013
 *      Author: harper
 */

#ifndef ACT_RECORD_H_
#define ACT_RECORD_H_

#include <map>
#include "common.h"

class ActivationRecord {
private:
	bool formain;
	std::map<char*,int,comp>* table;
	int localVarPointer;
	int paramPointer;
public:
	ActivationRecord(bool);

	// Managing local variables
	void add(Declare* variable);
	void addparam(Param* param);
	// Return the offset of given variable,
	// -1 if not exists
	int offset(char* variable);

	// Generate itself in memory
	void gencode(AsmContext*);
	void genclean(AsmContext*);
};
