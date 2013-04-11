/*
 * asm_context.h
 *
 *  Created on: Feb 11, 2013
 *      Author: harper
 */

#ifndef ASM_CONTEXT_H_
#define ASM_CONTEXT_H_

#include <list>
#include <map>
#include <vector>
#include <stack>

#include "symbol_table.h"

#define INDIRECT  1
#define DIRECT  0

typedef enum _Register {
	eax, ebx, ecx, edx, esp, unknown
} Register;

class AsmContext {
private:
	FILE* output;
	SymbolTable *symbolTable;

	int labelCount;
public:
	AsmContext(FILE* output);
	virtual ~AsmContext();
	FILE* getOutput();

	void init();

	MemoryUnit* alloc(int size);

	void dealloc(MemoryUnit*);

	void pushFrame();

	void popFrame();

	// Return the allocated address for the given id, allocate if not allocated
	MemoryUnit* find(const char* id);
	MemoryUnit* find(const char* id, int level);

	char* genlabel();

	// Utilities methods for generating ASM code
	virtual void header();
	virtual void declare(const char* type, const char* value);
	virtual void tail();

	virtual void declare(const char* type, const char* value);

	virtual void section(const char* name);
	virtual void reserve(const char* name, int size, int type);


	virtual void label(const char* label);

	virtual void call(const char* label);
	virtual void ret();
	virtual void ret(int val);

	virtual void cmp(Register source, Register target);
	virtual void cmp(Register source, int val);

	virtual void mov(Register target, const char* var);
	virtual void mov(Register target, int val);
	virtual void mov(Register target, Register source);
	virtual void mov(int address, Register source, int mode);
	virtual void mov(Register target, int valoraddr, int mode);
	virtual void mov(Register target, Register source, int mode);

	virtual void add(Register target, int val);
	virtual void add(Register target, Register source);
	virtual void sub(Register target, int val);
	virtual void sub(Register target, Register source);
	virtual void mul(Register target);
	virtual void div(Register target);

	virtual void land(Register, int);
	virtual void lor(Register, int);
	virtual void lnot(Register);
	virtual void lxor(Register, int);

	virtual void neg(Register target);

	virtual void inc(Register target);
	virtual void dec(Register target);

	virtual void interrupt(int number);

	virtual void push(Register target);
	virtual void push(int val);
	virtual void pop(Register target);

	virtual void jmp(char* label);
	virtual void je(char* label);
	virtual void jne(char* label);
	virtual void jg(char* label);
	virtual void jge(char* label);
	virtual void jl(char* label);
	virtual void jle(char* label);

	virtual void nop();
};

class ATTAsmContext: public AsmContext {
public:
	ATTAsmContext(FILE* output) :
			AsmContext(output) {
	}

	virtual void header();

	virtual void section(const char* name);
	virtual void reserve(const char* name, int size, int type);

	virtual void cmp(Register source, Register target);
	virtual void cmp(Register source, int val);

	virtual void mov(Register target, const char* var);
	virtual void mov(Register target, int val);
	virtual void mov(Register target, Register source);
	virtual void mov(int address, Register source, int mode);
	virtual void mov(Register target, int valoraddr, int mode);
	virtual void mov(Register target, Register source, int mode);

	virtual void add(Register target, int val);
	virtual void add(Register target, Register source);
	virtual void sub(Register target, int val);
	virtual void sub(Register target, Register source);
	virtual void mul(Register target);
	virtual void div(Register target);

	virtual void land(Register, int);
	virtual void lor(Register, int);
	virtual void lnot(Register);
	virtual void lxor(Register, int);

	virtual void inc(Register target);
	virtual void dec(Register target);

	virtual void interrupt(int number);

	virtual void push(Register target);
	virtual void push(int val);
	virtual void pop(Register target);
};

#endif /* ASM_CONTEXT_H_ */
