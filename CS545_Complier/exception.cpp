/*
 * exception.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: harper
 */
#include "exception.h"
#include "node.h"

char* error_undefined_id(Identifier* id) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: undefined id: %s", id->name);
	return buffer;
}

char* error_dup_id(Declare* declare) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: id is declared twice: %s",
			declare->name->name);
	return buffer;
}

char* error_dup_id(Subprogram* sub) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: subroutine is declared twice: %s",
			sub->id->name);
	return buffer;
}

char* error_no_sub(CallExpression* call) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: call not defined: %s",
			call->callname->name);
	return buffer;
}

char* error_ret_in_proc(ReturnStatement* ret) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: return statement in procedure:");
	return buffer;
}

char* error_type_mismatch(Expression* source) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: type mismatch: expression should have same type on both side");
	return buffer;
}

char* error_type_mismatch(Expression* source, Type* shouldbe) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: type mismatch: expression is not the type of %s",
			shouldbe == NULL ? "<void>" : shouldbe->description());
	return buffer;
}

char* error_arg_mismatch(CallExpression* call) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: argument count mismatch: %s",
			call->callname->name);
	return buffer;
}
