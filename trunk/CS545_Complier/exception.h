/*
 * exception.h
 *
 *  Created on: Feb 10, 2013
 *      Author: harper
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#define UNDEFINED_ID 10

#define FILE_NOT_FOUND 100

#define ILLEGAL_FORMAT 200

#define ILLEGAL_TYPE 250

class Identifier;
class Declare;
class CallExpression;
class Expression;
class Type;

char* error_undefined_id(Identifier*);
char* error_dup_id(Declare*);
char* error_dup_id(Subprogram* sub);
char* error_no_sub(CallExpression*);
char* error_type_mismatch(Expression*);
char* error_type_mismatch(Expression*, Type*);
char* error_arg_mismatch(CallExpression*);
char* error_ret_in_proc(ReturnStatement*);
#endif /* EXCEPTION_H_ */
