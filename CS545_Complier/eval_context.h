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
	std::map<char*, Subprogram*, comparator> *subTable;
	std::vector<char*> *errors;
	int error;
protected:

public:
	EvalContext();
	virtual ~EvalContext();

	void addDeclare(char* id, Declare* type);
	Declare* getDeclare(char* id);

	void addSub(char* id, Subprogram* def);
	Subprogram* getSub(char* id);

	void record(char* error);

	bool haserror();
	void showerror(FILE* output);

	void pushFrame();
	void popFrame();
};

#endif /* EVAL_CONTEXT_H_ */
