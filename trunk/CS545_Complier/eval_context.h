/*
 * eval_context.h
 *
 *  Created on: Feb 10, 2013
 *      Author: harper
 */

#ifndef EVAL_CONTEXT_H_
#define EVAL_CONTEXT_H_

#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <typeinfo>
#include "acc_history.h"

struct comparator {
	bool operator()(const char* a, const char* b) {
		return strcmp(a, b) < 0;
	}
};
class Declare;
class Subprogram;
class EvalContext {
private:
	std::vector<std::map<char*, Declare*, comparator> *> *idTable;
	Subprogram* current;
	std::map<char*, Subprogram*, comparator> *subTable;
	std::vector<char*> *errors;
	AccessHistory* history;
	int error;
protected:

public:
	EvalContext();
	virtual ~EvalContext();

	void access(Node*);
	void done();	
	Node* findhistory(std::type_info type);

	void addDeclare(char* id, Declare* type);
	Declare* getDeclare(char* id);

	void addSub(char* id, Subprogram* def);
	Subprogram* getSub(char* id);
	Subprogram* getCurrent();

	void record(char* error);

	bool haserror();
	void showerror();

	void pushFrame(Subprogram*);
	void popFrame();
};

#endif /* EVAL_CONTEXT_H_ */
