/*
 * exception.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: harper
 */
#include "exception.h"
#include "node.h"
#include "parser.h"

char* error_undefined_id(Identifier* id) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: undeclared id: '%s' @line %d, col %d",
			id->name, id->loc->first_line, id->loc->first_column);
	return buffer;
}

char* error_dup_id(Declare* declare) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: id is declared twice: '%s' @line %d, col %d",
			declare->name->name, declare->name->loc->first_line,
			declare->name->loc->first_column);
	return buffer;
}

char* error_dup_id(Subprogram* sub) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: subroutine is declared twice: '%s' @line %d, col %d",
			sub->id->name, sub->id->loc->first_line,
			sub->id->loc->first_column);
	return buffer;
}

char* error_no_sub(CallExpression* call) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: call not defined: '%s' @line %d, col %d",
			call->callname->name, call->callname->loc->first_line,
			call->callname->loc->first_column);
	return buffer;
}

char* error_ret_in_proc(ReturnStatement* ret) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: return statement in procedure: @line %d, col %d",
			ret->loc->first_line, ret->loc->first_column);
	return buffer;
}

char* error_type_mismatch(Expression* source) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: type mismatch: expression should have same type on both side: @line %d, col %d",
			source->loc->first_line, source->loc->first_column);
	return buffer;
}

char* error_type_mismatch(Function* function) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: function should return int or real: '%s' @line %d, col %d",
			function->id->name, function->id->loc->first_line,
			function->id->loc->first_column);
	return buffer;
}

char* error_type_mismatch(Expression* source, const char* desc) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: type mismatch: expression should have type %s while get %s: @line %d, col %d",
			desc, source->getType()->description(), source->loc->first_line,
			source->loc->first_column);
	return buffer;
}

char* error_type_mismatch(Expression* source, Type* shouldbe) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: type mismatch: expression is not the type of %s: @line %d, col %d",
			shouldbe == NULL ? "<void>" : shouldbe->description(),
			source->loc->first_line, source->loc->first_column);
	return buffer;
}

char* error_arg_mismatch(CallExpression* call) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: argument count mismatch: '%s' @line %d, col %d",
			call->callname->name, call->callname->loc->first_line,
			call->callname->loc->first_column);
	return buffer;
}

char* error_arg_mismatch(Identifier* call) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: argument count mismatch: '%s' @line %d, col %d",
			call->name, call->loc->first_line, call->loc->first_column);
	return buffer;
}

char* error_break_not_in_loop(BreakStatement* stmt) {
	char* buffer = new char[300];
	sprintf(buffer, "Semantic error: break not in a loop: @line %d, col %d",
			stmt->loc->first_line, stmt->loc->first_column);
	return buffer;
}

char* error_no_return(Function* func) {
	char* buffer = new char[300];
	sprintf(buffer,
			"Semantic error: function has no return statement: '%s' @line %d, col %d",
			func->id->name, func->id->loc->first_line,
			func->id->loc->first_column);
	return buffer;
}

char* error_update_non_local(AssignStatement* assign) {
	char* buffer = new char[300];
	Identifier* id = NULL;
	if (typeid(*(assign->leftval)) == typeid(Identifier)) {
		id = (Identifier*) (assign->leftval);
	} else {
		id = ((ArrayElement*) assign->leftval)->name;
	}
	sprintf(buffer,
			"Semantic error: non-local variable cannot be updated:'%s' @line %d, col %d",
			id->name, id->loc->first_line, id->loc->first_column);
	return buffer;
}
