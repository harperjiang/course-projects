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
	sprintf(buffer, "undefined id: %s", id->name);
	return buffer;
}

char* error_dup_id(Declare* declare) {
	char* buffer = new char[300];
	sprintf(buffer, "id is declared twice: %s", declare->name->name);
	return buffer;
}

char* error_no_sub(CallExpression* call) {
	char* buffer = new char[300];
	sprintf(buffer, "call not defined: %s", call->callname->name);
	return buffer;
}

char* error_type_mismatch(Expression* source) {
	char* buffer = new char[300];
	sprintf(buffer,
			"type mismatch: expression should have same type on both side");
	return buffer;
}

char* error_type_mismatch(Expression* source, Type* shouldbe) {
	char* buffer = new char[300];
	sprintf(buffer, "type mismatch: expression is not the type of %s",
			shouldbe->description());
	return buffer;
}

