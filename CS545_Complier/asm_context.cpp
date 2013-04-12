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

Register reg(int index) {
	return (Register) index;
}

AsmContext::AsmContext(FILE* output) {
	this->output = output;
	symbolTable = new SymbolTable();

	labelCount = 0;

	history = new AccessHistory();
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

void AsmContext::access(Node* node) {
	history->push(node);
}

void AsmContext::done() {
	// Don't do boundary check
	history->pop();
}

Node* AsmContext::findhistory(std::type_info type) {
	return history->find(type);
}

std::vector<Node*>* AsmContext::gethistory() {
	return history->gethistory();
}

ActivationRecord* AsmContext::getActRecord(char* id, int* level) {
	*level = 0;
	for (int i = history->gethistory()->size() - 1; i >= 0; i--) {
		Node* node = history->gethistory()->at(i);
		ActivationRecord* actrecord = NULL;
		if (typeid(node) == typeid(Program)) {
			actrecord = ((Program*) node)->actrecord;
		}
		if (typeid(node) == typeid(Function)) {
			actrecord = ((Function*) node)->actrecord;
		}
		if (typeid(node) == typeid(Procedure)) {
			actrecord = ((Procedure*) node)->actrecord;
		}
		if (-1 != actrecord->offset(id))
			return actrecord;
		(*level)++;
	}
	return NULL;
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

void AsmContext::declare(const char* type, const char* name) {

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
	Register buffer = edx;
	if (source == buffer)
		buffer = ecx;
	push(buffer);
	mov(buffer, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmov [%s+%d],%s\n", regtoa(buffer), address,
				regtoa(source));
		break;
	case 1: //01
		fprintf(getOutput(), "\tmov [%s+%d],[%s]\n", regtoa(buffer), address,
				regtoa(source));
		break;
	default:
		break;
	}
	pop(buffer);
}

void AsmContext::mov(Register target, int valoraddr, int mode) {
	Register buffer = edx;
	if (target == buffer)
		buffer = ecx;
	push(buffer);
	mov(buffer, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmov %s,%d\n", regtoa(target), valoraddr);
		break;
	case 1: //01
		fprintf(getOutput(), "\tmov %s,[%s+%d]\n", regtoa(target),
				regtoa(buffer), valoraddr);
		break;
	case 2: //10
		fprintf(getOutput(), "\tmov [%s],%d\n", regtoa(target), valoraddr);
		break;
	case 3: // 11
		fprintf(getOutput(), "\tmov [%s],[%s+%d]\n", regtoa(target),
				regtoa(buffer), valoraddr);
		break;
	default:
		break;
	}
	pop(buffer);
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

void AsmContext::mov(Register target, int offset, Register source) {
	fprintf(getOutput(), "mov %s,[%s+%d]\n", regtoa(target), regtoa(source),
			offset);
}

void AsmContext::lea(Register target, Register source, int offset) {
	fprintf(getOutput(), "\t%s %s,%s+%d\n", "lea", regtoa(target),
			regtoa(source), offset);
}

void AsmContext::add(Register target, int val) {
	fprintf(getOutput(), "\t%s %s,%d\n", "add", regtoa(target), val);
}

void AsmContext::add(Register target, Register source) {
	fprintf(getOutput(), "\t%s %s,%s\n", "add", regtoa(target), regtoa(source));
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
	fprintf(getOutput(), "\tnot %s,%s\n", regtoa(target), regtoa(target));
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

void AsmContext::push(char* val) {
	fprintf(getOutput(), "\t%s %s\n", "push", val);
}

void AsmContext::push(Register target, int offset) {
	fprintf(getOutput(), "\t%s [%s+%d]\n", "push", regtoa(target), offset);
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

void ATTAsmContext::declare(const char* type, const char* name) {
	fprintf(getOutput(), "\t.%s %s\n", type, name);
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
	if (target == source)
		return;
	fprintf(getOutput(), "\tmovl %%%s,%%%s\n", regtoa(source), regtoa(target));
}

void ATTAsmContext::mov(int address, Register source, int mode) {
	Register buffer = edx;
	if (source == buffer) {
		buffer = ecx;
	}
	push(buffer);
	mov(buffer, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmovl %%%s,%d(%%%s)\n", regtoa(source), address,
				regtoa(buffer));
		break;
	case 1: //01
		fprintf(getOutput(), "\tmovl (%%%s),%d(%%%s),\n", regtoa(source),
				address, regtoa(buffer));
		break;
	default:
		break;
	}
	pop(buffer);
}

void ATTAsmContext::mov(Register target, int valoraddr, int mode) {
	Register buffer = edx;
	if (target == buffer) {
		buffer = ecx;
	}
	push(buffer);
	mov(buffer, "heap");
	switch (mode) {
	case 0: //00
		fprintf(getOutput(), "\tmovl $%d,%%%s\n", valoraddr, regtoa(target));
		break;
	case 1: //01
		fprintf(getOutput(), "\tmovl %d(%%%s),%%%s\n", valoraddr,
				regtoa(buffer), regtoa(target));
		break;
	case 2: //10
		fprintf(getOutput(), "\tmovl $%d,(%%%s)\n", valoraddr, regtoa(target));
		break;
	case 3: // 11
		fprintf(getOutput(), "\tmovl %d(%%%s),(%%%s)\n", valoraddr,
				regtoa(buffer), regtoa(target));
		break;
	default:
		break;
	}
	pop(buffer);
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

void ATTAsmContext::mov(Register target, int offset, Register source) {
	fprintf(getOutput(), "movl %d(%s),%s\n", offset, regtoa(source),
			regtoa(target));
}

void ATTAsmContext::lea(Register target, Register source, int offset) {
	fprintf(getOutput(), "\t%s %d(%s),%s\n", "leal", offset, regtoa(source),
			regtoa(target));
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

void ATTAsmContext::push(char* val) {
	fprintf(getOutput(), "\t%s $%s\n", "pushl", val);
}

void AsmContext::push(Register target, int offset) {
	fprintf(getOutput(), "\t%s %d(%%%s)\n", "pushl", regtoa(target), offset);
}

void ATTAsmContext::pop(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "popl", regtoa(target));
}

void ATTAsmContext::reserve(const char* name, int size, int type) {
	int realsize = size * type;
	fprintf(getOutput(), "\t.lcomm %s,%d\n", name, realsize);
}

