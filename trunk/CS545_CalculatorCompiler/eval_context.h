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

class EvalContext {
private:
	std::map<char*, char*, comparator> *idTable;
	std::map<int, std::vector<char*>*> *errors;
	int error;
protected:
	void record(int type, char* context);
public:
	EvalContext();
	virtual ~EvalContext();
	void addId(char* id);
	void check(char* id);
	int geterror();
	void showerror(FILE* output);
};

#endif /* EVAL_CONTEXT_H_ */
