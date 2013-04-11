/*
 * act_record.h
 *
 *  Created on: Apr 11, 2013
 *      Author: harper
 */

#ifndef ACT_RECORD_H_
#define ACT_RECORD_H_

class ActRecord {
private:

public:
	
	// Managing local variables
	void add(Declare* variable);
	void addparam(Param* param);
	int offset(char* variable);
	
	// Generate itself in memory
	void gencode(AsmContext*);
};
