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

#include "common.h"
#include "acc_hist.h"
#include "act_record.h"

#define INDIRECT  1
#define DIRECT  0

class Node;
class Subprogram;

typedef enum _Register {
	eax, ebx, ecx, edx, esi, edi, esp, ebp, unknown
} Register;

class AsmContext {
private:
	FILE* output;
	int labelCount;
	AccessHistory* history;
	std::stack<Subprogram*>* subhistory;
	std::map<char*,int,comp>* heapTracker;
	int heapPointer;
public:
	AsmContext(FILE* output);
	virtual ~AsmContext();
	FILE* getOutput();

	Subprogram* currentsub();

	void init();

	void access(Node*);
	void done();
	Node* findhistory(char* type);
	std::vector<Node*>* gethistory();

	ActivationRecord* getActRecord(char* var, int* level);
	int inHeap(char* var);
	void resetHeap();

	char* genlabel();

	// Utilities methods for generating ASM code
	virtual void header();

	virtual void tail();

	virtual void declare(const char* type, const char* name);
	virtual void section(const char* name);
	virtual void reserve(const char* name, int size, int type);

	virtual void label(const char* label);

	virtual void call(const char* label);
	virtual void ret();
	virtual void ret(int val);
	virtual void leave();

	virtual void cmp(Register source, Register target);
	virtual void cmp(Register source, int val);

	virtual void mov(Register target, const char* var);
	virtual void mov(Register target, int val);
	virtual void mov(Register target, unsigned int fval);
	virtual void mov(Register target, Register source, int mode = 0,
			int offset = 0);

	virtual void lea(Register target, Register source, int offset);

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
	virtual void push(const char*);
	virtual void push(Register target, int offset);
	virtual void pop(Register target);

	virtual void pushf();
	virtual void popf();

	virtual void shr(Register target, int val);
	virtual void shl(Register target, int val);

	virtual void jmp(char* label);
	virtual void je(char* label);
	virtual void jne(char* label);
	virtual void ja(char* label);
	virtual void jae(char* label);
	virtual void jg(char* label);
	virtual void jge(char* label);
	virtual void jb(char* label);
	virtual void jbe(char* label);
	virtual void jl(char* label);
	virtual void jle(char* label);

	virtual void nop();

	// Float operations
	virtual void fld(Register, int offset = 0, bool lv = false);
	virtual void fstp(Register, int offset = 0, bool lv = false);
	virtual void fldz();
	virtual void fld1();
	virtual void ffree(int i);
	virtual void faddp();
	virtual void fsubp();
	virtual void fmulp();
	virtual void fdivp();
	virtual void fcompp();
	virtual void fcomip(int i);
	virtual void fstsw();
};

class ATTAsmContext: public AsmContext {
public:
	ATTAsmContext(FILE* output) :
			AsmContext(output) {
	}

	virtual void header();

	virtual void section(const char* name);
	virtual void declare(const char* type, const char* name);
	virtual void reserve(const char* name, int size, int type);

	virtual void cmp(Register source, Register target);
	virtual void cmp(Register source, int val);

	virtual void mov(Register target, const char* var);
	virtual void mov(Register target, int val);
	virtual void mov(Register target, unsigned int fval);
	virtual void mov(Register target, Register source, int mode = 0,
			int offset = 0);

	virtual void lea(Register target, Register source, int offset);

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
	virtual void push(const char*);
	virtual void push(Register target, int offset);
	virtual void pop(Register target);

	virtual void pushf();
	virtual void popf();

	virtual void shr(Register target, int val);
	virtual void shl(Register target, int val);

	// Float operations
	virtual void fld(Register, int offset = 0, bool lv = false);
	virtual void fstp(Register, int offset = 0, bool lv = false);
	virtual void fstsw();
	virtual void ffree(int i);
	virtual void fcomip(int i);
};

#endif /* ASM_CONTEXT_H_ */
