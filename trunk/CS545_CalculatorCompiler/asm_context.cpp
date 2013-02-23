/*
 * asm_context.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: harper
 */

#include "asm_context.h"
#include <stdio.h>

const char* regtoa(Register reg) {
	switch (reg) {
	case eax:
		return "eax";
	case ebx:
		return "ebx";
	case ecx:
		return "ecx";
	case edx:
		return "edx";
	default:
		return NULL;
	}
}

AsmContext::AsmContext(FILE* output) {
	this->output = output;
	symbolTable = new SymbolTable();

	labelCount = 0;
}

AsmContext::~AsmContext() {
	if (NULL != this->output) {
		fclose(this->output);
	}

	delete symbolTable;
}

FILE* AsmContext::getOutput() {
	return this->output;
}

void AsmContext::init() {

}

MemoryUnit* AsmContext::alloc(int size) {
	return this->symbolTable->allocOnHeap(size);
}

void AsmContext::dealloc(MemoryUnit* alloc) {
	symbolTable->releaseHeap(alloc);
}

// Return the allocated address for the given id, -1 if not allocated
MemoryUnit* AsmContext::find(const char* id) {
	if (NULL == symbolTable->find(id)) {
		MemoryUnit* alloc = this->alloc(4); // 32 bit
		symbolTable->add(id, alloc);
	}
	return symbolTable->find(id);
}

MemoryUnit* AsmContext::find(const char* id, int level) {
	if (NULL == symbolTable->find(id, level)) {
		MemoryUnit* alloc = this->alloc(4); // 32 bit
		symbolTable->add(id, alloc);
	}
	return symbolTable->find(id, level);
}

void AsmContext::pushFrame() {
	this->symbolTable->pushFrame();
}

void AsmContext::popFrame() {
	this->symbolTable->popFrame();
}

char* AsmContext::genlabel() {
	char* label = new char[10];
	sprintf(label, "%s%du", "label", labelCount++);
	return label;
}

void AsmContext::section(const char* name) {
	fprintf(getOutput(), "section .%s\n", name);
}

// Utilities methods for generating ASM code
void AsmContext::header() {
	section("text");
	fprintf(getOutput(), "global _start\n");
}

void AsmContext::reserve(const char* name, int size, int type) {
	switch (type) {
	case 1: // byte
		fprintf(getOutput(), "%s resb %d\n", name, size);
		break;
	case 2: // word
		fprintf(getOutput(), "%s resw %d\n", name, size);
		break;
	}
}

void AsmContext::ret() {
	fprintf(getOutput(), "\t%s\n", "ret");
}

void AsmContext::ret(int val) {
	fprintf(getOutput(), "\t%s %d\n", "ret", val);
}

void AsmContext::tail() {
	section("bss");
	reserve("heap", 8192, 1);
}

void AsmContext::label(const char* label) {
	fprintf(getOutput(), "%s:\n", label);
}

void AsmContext::call(const char* label) {
	fprintf(getOutput(), "\t%s %s\n", "call", label);
}

void AsmContext::cmp(Register source, Register target) {
	fprintf(getOutput(), "\tcmp %s,%s\n", regtoa(source), regtoa(target));
}

void AsmContext::cmp(Register source, int val) {
	fprintf(getOutput(), "\tcmp %s,%d\n", regtoa(source), val);
}

void AsmContext::mov(Register target, const char* var) {
	fprintf(getOutput(), "\tmov %s,%s\n", regtoa(target), var);
}

void AsmContext::mov(Register target, int val) {
	fprintf(getOutput(), "\tmov %s,%d\n", regtoa(target), val);

}
void AsmContext::mov(Register target, Register source) {
	fprintf(getOutput(), "\tmov %s,%s\n", regtoa(target), regtoa(source));
}

void AsmContext::mov(int address, Register source, int mode) {
	push(edx);
	mov(edx, "heap");
	add(edx, address);
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmov [edx],%s\n", regtoa(source));
		break;
	case 1: //01
		fprintf(getOutput(), "\tmov [edx],[%s]\n", regtoa(source));
		break;
	default:
		break;
	}
	pop(edx);
}

void AsmContext::mov(Register target, int valoraddr, int mode) {
	push(edx);
	mov(edx, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmov %s,%d\n", regtoa(target), valoraddr);
		break;
	case 1: //01
		add(edx, valoraddr);
		fprintf(getOutput(), "\tmov %s,[edx]\n", regtoa(target));
		break;
	case 2: //10
		fprintf(getOutput(), "\tmov [%s],%d\n", regtoa(target), valoraddr);
		break;
	case 3: // 11
		add(edx, valoraddr);
		fprintf(getOutput(), "\tmov [%s],[edx]\n", regtoa(target));
		break;
	default:
		break;
	}
	pop(edx);
}
void AsmContext::mov(Register target, Register source, int mode) {
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "mov %s,%s\n", regtoa(target), regtoa(source));
		break;
	case 1: //01
		fprintf(getOutput(), "mov %s,[%s]\n", regtoa(target), regtoa(source));
		break;
	case 2: //10
		fprintf(getOutput(), "mov [%s],%s\n", regtoa(target), regtoa(source));
		break;
	case 3: // 11
		fprintf(getOutput(), "mov [%s],[%s]\n", regtoa(target), regtoa(source));
		break;
	default:
		break;
	}
}

void AsmContext::arith(Register target, int val, OPR opr) {
	switch (opr) {
	case OADD:
		fprintf(getOutput(), "\t%s %s,%d\n", "add", regtoa(target), val);
		break;
	case OSUB:
		fprintf(getOutput(), "\t%s %s,%d\n", "sub", regtoa(target), val);
		break;
	case OMUL:
		fprintf(getOutput(), "\t%s %s,%d\n", "mul", regtoa(target), val);
		break;
	case ODIV:
		fprintf(getOutput(), "\t%s %s,%d\n", "div", regtoa(target), val);
		break;
	case OMOD:
		fprintf(getOutput(), "\t%s %s,%d\n", "mod", regtoa(target), val);
		break;
	default:
		break;
	}
}

void AsmContext::arith(Register target, Register source, OPR opr) {
	switch (opr) {
	case OADD:
		fprintf(getOutput(), "\t%s %s,%s\n", "add", regtoa(target),
				regtoa(source));
		break;
	case OSUB:
		fprintf(getOutput(), "\t%s %s,%s\n", "sub", regtoa(target),
				regtoa(source));
		break;
	case OMUL:
		fprintf(getOutput(), "\t%s %s,%s\n", "mul", regtoa(target),
				regtoa(source));
		break;
	case ODIV:
		fprintf(getOutput(), "\t%s %s,%s\n", "div", regtoa(target),
				regtoa(source));
		break;
	case OMOD:
		fprintf(getOutput(), "\t%s %s,%s\n", "mod", regtoa(target),
				regtoa(source));
		break;
	default:
		break;
	}
}

void AsmContext::add(Register target, int val) {
	fprintf(getOutput(), "\t%s %s,%d", "add", regtoa(target), val);
}

void AsmContext::add(Register target, Register source) {
	fprintf(getOutput(), "\t%s %s,%s", "add", regtoa(target), regtoa(source));
}

void AsmContext::sub(Register target, int val) {
	fprintf(getOutput(), "\t%s %s,%d\n", "sub", regtoa(target), val);
}

void AsmContext::sub(Register target, Register source) {
	fprintf(getOutput(), "\t%s %s,%s\n", "sub", regtoa(target), regtoa(source));
}

void AsmContext::mul(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "mul", regtoa(target));
}

void AsmContext::div(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "div", regtoa(target));
}

void AsmContext::neg(Register target) {
	lnot(target);
	add(target, 1);
}

void AsmContext::land(Register target, int val) {
	fprintf(getOutput(), "\tand %s,%d\n", regtoa(target), val);
}

void AsmContext::lor(Register target, int val) {
	fprintf(getOutput(), "\tor %s,%d\n", regtoa(target), val);
}

void AsmContext::lnot(Register target) {
	fprintf(getOutput(), "\tnot %s,%d\n", regtoa(target));
}

void AsmContext::lxor(Register target, int val) {
	fprintf(getOutput(), "\txor %s,%d\n", regtoa(target), val);
}

void AsmContext::inc(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "inc", regtoa(target));
}

void AsmContext::dec(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "dec", regtoa(target));
}

void AsmContext::interrupt(int number) {
	fprintf(getOutput(), "\t%s %xh\n", "int", number);
}

void AsmContext::push(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "push", regtoa(target));
}

void AsmContext::push(int val) {
	fprintf(getOutput(), "\t%s %d\n", "push", val);
}

void AsmContext::pop(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "pop", regtoa(target));
}

void AsmContext::jmp(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jmp", label);
}

void AsmContext::je(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "je", label);
}

void AsmContext::jne(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jne", label);
}

void AsmContext::jg(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jg", label);
}

void AsmContext::jge(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jge", label);
}

void AsmContext::jl(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jl", label);
}

void AsmContext::jle(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jle", label);
}

void AsmContext::nop() {
	fprintf(getOutput(), "\t%s\n", "nop");
}

// ATT Part

void ATTAsmContext::section(const char* name) {
	fprintf(getOutput(), ".%s\n", name);
}

// Utilities methods for generating ASM code
void ATTAsmContext::header() {
	section("text");
	fprintf(getOutput(), ".globl main\n");
	fprintf(getOutput(), "main:\n");
}

void ATTAsmContext::cmp(Register source, Register target) {
	fprintf(getOutput(), "\tcmpl %%%s,%%%s\n", regtoa(target), regtoa(source));
}

void ATTAsmContext::cmp(Register source, int val) {
	fprintf(getOutput(), "\tcmpl $%d,%%%s\n", val, regtoa(source));
}

void ATTAsmContext::mov(Register target, const char* var) {
	fprintf(getOutput(), "\tmov $%s,%%%s\n", var, regtoa(target));
}

void ATTAsmContext::mov(Register target, int val) {
	fprintf(getOutput(), "\tmovl $%d,%%%s\n", val, regtoa(target));

}
void ATTAsmContext::mov(Register target, Register source) {
	fprintf(getOutput(), "\tmovl %%%s,%%%s\n", regtoa(source), regtoa(target));
}

void ATTAsmContext::mov(int address, Register source, int mode) {
	push(edx);
	mov(edx, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmovl %%%s,%d(%%edx)\n", regtoa(source),
				address);
		break;
	case 1: //01
		fprintf(getOutput(), "\tmovl (%%%s),%d(%%edx),\n", regtoa(source),
				address);
		break;
	default:
		break;
	}
	pop(edx);
}

void ATTAsmContext::mov(Register target, int valoraddr, int mode) {
	push(edx);
	mov(edx, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmovl $%d,%%%s\n", valoraddr, regtoa(target));
		break;
	case 1: //01
		fprintf(getOutput(), "\tmovl %d(%%edx),%%%s\n", valoraddr,
				regtoa(target));
		break;
	case 2: //10
		fprintf(getOutput(), "\tmovl $%d,(%%%s)\n", valoraddr, regtoa(target));
		break;
	case 3: // 11
		fprintf(getOutput(), "\tmovl %d(%%edx),(%%%s)\n", valoraddr,
				regtoa(target));
		break;
	default:
		break;
	}
	pop(edx);
}
void ATTAsmContext::mov(Register target, Register source, int mode) {
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmovl %%%s,%%%s\n", regtoa(source),
				regtoa(target));
		break;
	case 1: //01
		fprintf(getOutput(), "\tmovl (%%%s),%%%s\n", regtoa(source),
				regtoa(target));
		break;
	case 2: //10
		fprintf(getOutput(), "\tmovl %%%s,(%%%s)\n", regtoa(source),
				regtoa(target));
		break;
	case 3: // 11
		fprintf(getOutput(), "\tmovl (%%%s),(%%%s)\n", regtoa(source),
				regtoa(target));
		break;
	default:
		break;
	}
}

void ATTAsmContext::arith(Register target, int val, OPR opr) {
	switch (opr) {
	case OADD:
		fprintf(getOutput(), "\t%s $%d,%%%s\n", "addl", val, regtoa(target));
		break;
	case OSUB:
		fprintf(getOutput(), "\t%s $%d,%%%s\n", "subl", val, regtoa(target));
		break;
	case OMUL:
		mov(eax, target);
		mov(edx, val);
		fprintf(getOutput(), "\t%s %%%s\n", "mull", regtoa(edx));
		mov(target, eax);
		break;
	case ODIV:
		mov(edx, 0);
		mov(eax, target);
		mov(ebx, val);
		fprintf(getOutput(), "\t%s %%%s\n", "divl", regtoa(ebx));
		mov(target, eax);
		break;
	case OMOD:
		mov(edx, 0);
		mov(eax, target);
		mov(ebx, val);
		fprintf(getOutput(), "\t%s %%%s\n", "divl", regtoa(ebx));
		mov(target, edx);
		break;
	default:
		break;
	}
}

void ATTAsmContext::arith(Register target, Register source, OPR opr) {
	switch (opr) {
	case OADD:
		fprintf(getOutput(), "\t%s %%%s,%%%s\n", "addl", regtoa(source),
				regtoa(target));
		break;
	case OSUB:
		fprintf(getOutput(), "\t%s %%%s,%%%s\n", "subl", regtoa(source),
				regtoa(target));
		break;
	case OMUL:
		push(ebx);
		push(target);
		push(source);
		pop(ebx);
		pop(eax);
		fprintf(getOutput(), "\t%s %%%s\n", "mull", regtoa(ebx));
		pop(ebx);
		mov(target, eax);
		break;
	case ODIV:
		push(ebx);
		push(target);
		push(source);
		pop(ebx);
		pop(eax);
		mov(edx, 0);
		fprintf(getOutput(), "\t%s %%%s\n", "divl", regtoa(ebx));
		pop(ebx);
		mov(target, eax);
		break;
	case OMOD:
		push(ebx);
		push(target);
		push(source);
		pop(ebx);
		pop(eax);
		mov(edx, 0);
		fprintf(getOutput(), "\t%s %%%s\n", "divl", regtoa(ebx));
		pop(ebx);
		mov(target, edx);
		break;
	default:
		break;
	}
}

void ATTAsmContext::add(Register target, int val) {
	fprintf(getOutput(), "\t%s $%d,%%%s\n", "addl", val, regtoa(target));
}

void ATTAsmContext::add(Register target, Register source) {
	fprintf(getOutput(), "\t%s %%%s,%%%s\n", "addl", regtoa(source),
			regtoa(target));
}

void ATTAsmContext::sub(Register target, int val) {
	fprintf(getOutput(), "\t%s $%d,%%%s\n", "subl", val, regtoa(target));
}

void ATTAsmContext::sub(Register target, Register source) {
	fprintf(getOutput(), "\t%s %%%s,%%%s\n", "subl", regtoa(source),
			regtoa(target));
}

void ATTAsmContext::mul(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "mull", regtoa(target));
}

void ATTAsmContext::div(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "divl", regtoa(target));
}

void ATTAsmContext::land(Register target, int val) {
	fprintf(getOutput(), "\tand $%d,%%%s\n", val, regtoa(target));
}

void ATTAsmContext::lor(Register target, int val) {
	fprintf(getOutput(), "\tor $%d,%%%s\n", val, regtoa(target));
}

void ATTAsmContext::lnot(Register target) {
	fprintf(getOutput(), "\tnot %%%s\n", regtoa(target));
}

void ATTAsmContext::lxor(Register target, int val) {
	fprintf(getOutput(), "\txor $%d,%%%s\n", val, regtoa(target));
}

void ATTAsmContext::inc(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "incl", regtoa(target));
}

void ATTAsmContext::dec(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "decl", regtoa(target));
}

void ATTAsmContext::interrupt(int number) {
	fprintf(getOutput(), "\t%s $0x%x\n", "int", number);
}

void ATTAsmContext::push(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "pushl", regtoa(target));
}
void ATTAsmContext::push(int val) {
	fprintf(getOutput(), "\t%s $%d\n", "pushl", val);
}
void ATTAsmContext::pop(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "popl", regtoa(target));
}

void ATTAsmContext::reserve(const char* name, int size, int type) {
	int realsize = size * type;
	fprintf(getOutput(), "\t.lcomm %s,%d\n", name, realsize);
}

