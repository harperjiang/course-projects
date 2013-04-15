/*
 * asm_context.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: harper
 */

#include "asm_context.h"
#include "node.h"
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
	case esp:
		return "esp";
	case ebp:
		return "ebp";
	default:
		return NULL;
	}
}

AsmContext::AsmContext(FILE* output) {
	this->output = output;

	labelCount = 0;

	history = new AccessHistory();
}

AsmContext::~AsmContext() {
	if (NULL != this->output) {
		fclose(this->output);
	}
	delete history;
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

Node* AsmContext::findhistory(char* type) {
	return history->find(type);
}

std::vector<Node*>* AsmContext::gethistory() {
	return history->gethistory();
}

ActivationRecord* AsmContext::getActRecord(char* id, int* level) {
	*level = 0;
	ActivationRecord* actrecord = NULL;
	for (int i = history->gethistory()->size() - 1; i >= 0; i--) {
		Node* node = history->gethistory()->at(i);
		if (typeid(*node) == typeid(Program)) {
			actrecord = ((Program*) node)->actrecord;
		}
		if (typeid(*node) == typeid(Function)) {
			actrecord = ((Function*) node)->actrecord;
		}
		if (typeid(*node) == typeid(Procedure)) {
			actrecord = ((Procedure*) node)->actrecord;
		}
		if (actrecord != NULL) {
			if (-1 != actrecord->offset(id)) {
				return actrecord;
			} else {
				(*level)++;
			}
		}
	}
	return NULL;
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
	fprintf(getOutput(), "global main\n");
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

void AsmContext::leave() {
	fprintf(getOutput(), "\t%s\n", "leave");
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

void AsmContext::mov(Register target, unsigned int fval) {
	fprintf(getOutput(), "\tmov %s, %X\n", regtoa(target), fval);
}

void AsmContext::mov(Register target, Register source, int mode, int offset) {
	if (0 == offset) {
		switch (mode) {
		case 0: //00
			fprintf(getOutput(), "mov %s,%s\n", regtoa(target), regtoa(source));
			break;
		case 1: //01
			fprintf(getOutput(), "mov %s,[%s]\n", regtoa(target),
					regtoa(source));
			break;
		case 2: //10
			fprintf(getOutput(), "mov [%s],%s\n", regtoa(target),
					regtoa(source));
			break;
		case 3: // 11
			fprintf(getOutput(), "mov [%s],[%s]\n", regtoa(target),
					regtoa(source));
			break;
		default:
			break;
		}
	} else {
		switch (mode) {
		case 0: //00
			fprintf(getOutput(), "mov %s,%s\n", regtoa(target), regtoa(source));
			break;
		case 1: //01
			fprintf(getOutput(), "mov %s,[%s+%d]\n", regtoa(target),
					regtoa(source), offset);
			break;
		case 2: //10
			fprintf(getOutput(), "mov [%s+%d],%s\n", regtoa(target), offset,
					regtoa(source));
			break;
		case 3: // 11
			fprintf(getOutput(), "mov [%s],[%s]\n", regtoa(target),
					regtoa(source));
			break;
		default:
			break;
		}
	}
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

void AsmContext::push(const char* val) {
	fprintf(getOutput(), "\t%s %s\n", "push", val);
}

void AsmContext::push(Register target, int offset) {
	fprintf(getOutput(), "\t%s [%s+%d]\n", "push", regtoa(target), offset);
}

void AsmContext::pop(Register target) {
	fprintf(getOutput(), "\t%s %s\n", "pop", regtoa(target));
}

void AsmContext::pushf() {
	fprintf(getOutput(), "\t%s\n", "pushfd");
}

void AsmContext::popf() {
	fprintf(getOutput(), "\t%s\n", "popfd");
}

void AsmContext::shr(Register target, int val) {
	fprintf(getOutput(), "\t%s %s,%d\n", "shr", regtoa(target), val);
}

void AsmContext::shl(Register target, int val) {
	fprintf(getOutput(), "\t%s %s,%d\n", "shl", regtoa(target), val);
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

void AsmContext::ja(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "ja", label);
}

void AsmContext::jae(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jae", label);
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

void AsmContext::jb(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jb", label);
}

void AsmContext::jbe(char* label) {
	fprintf(getOutput(), "\t%s %s\n", "jbe", label);
}

void AsmContext::nop() {
	fprintf(getOutput(), "\t%s\n", "nop");
}

void AsmContext::fld(Register reg, int offset, bool lv) {
	fprintf(getOutput(), "\t%s [%s+%d]\n", "fld", regtoa(reg), offset);
}

void AsmContext::fstp(Register reg, int offset, bool lv) {
	fprintf(getOutput(), "\t%s [%s+%d]\n", "fstp", regtoa(reg), offset);
}

void AsmContext::fldz() {
	fprintf(getOutput(), "\t%s\n", "fldz");
}

void AsmContext::fld1() {
	fprintf(getOutput(), "\t%s\n", "fld1");
}

void AsmContext::faddp() {
	fprintf(getOutput(), "\t%s\n", "faddp");
}

void AsmContext::fsubp() {
	fprintf(getOutput(), "\t%s\n", "fsubrp");
}

void AsmContext::fmulp() {
	fprintf(getOutput(), "\t%s\n", "fmulp");
}

void AsmContext::fdivp() {
	fprintf(getOutput(), "\t%s\n", "fdivrp");
}

void AsmContext::fcompp() {
	fprintf(getOutput(), "\t%s\n", "fcompp");
}

void AsmContext::fcomip(int i) {
	fprintf(getOutput(), "\t%s st, st(%d)\n", "fcomip", i);
}

void AsmContext::fstsw() {
	fprintf(getOutput(), "\t%s\n", "fstsw ax");
}

void AsmContext::ffree(int a) {
	fprintf(getOutput(), "\t%s st%d\n", "ffree", a);
}
// ATT Part

void ATTAsmContext::section(const char* name) {
	fprintf(getOutput(), ".%s\n", name);
}

// Utilities methods for generating ASM code
void ATTAsmContext::header() {
	section("text");
	fprintf(getOutput(), ".globl main\n");
}

void ATTAsmContext::declare(const char* type, const char* name) {
	fprintf(getOutput(), "\t.%s \"%s\"\n", type, name);
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

void ATTAsmContext::mov(Register target, unsigned int fval) {
	fprintf(getOutput(), "\tmovl $0x%x, %%%s\n", fval, regtoa(target));
}

void ATTAsmContext::mov(Register target, Register source, int mode,
		int offset) {
	if (offset == 0) {
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
	} else {
		switch (mode) {
		case 0: //00
			fprintf(getOutput(), "\tmovl %%%s,%%%s\n", regtoa(source),
					regtoa(target));
			break;
		case 1: //01
			fprintf(getOutput(), "\tmovl %d(%%%s),%%%s\n", offset,
					regtoa(source), regtoa(target));
			break;
		case 2: //10
			fprintf(getOutput(), "\tmovl %%%s,%d(%%%s)\n", regtoa(source),
					offset, regtoa(target));
			break;
		case 3: // 11
			fprintf(getOutput(), "\tmovl (%%%s),(%%%s)\n", regtoa(source),
					regtoa(target));
			break;
		default:
			break;
		}
	}
}

void ATTAsmContext::lea(Register target, Register source, int offset) {
	fprintf(getOutput(), "\t%s %d(%%%s),%%%s\n", "leal", offset, regtoa(source),
			regtoa(target));
}

void ATTAsmContext::add(Register target, int val) {
	if (val < 0)
		sub(target, -val);
	else
		fprintf(getOutput(), "\t%s $%d,%%%s\n", "addl", val, regtoa(target));
}

void ATTAsmContext::add(Register target, Register source) {
	fprintf(getOutput(), "\t%s %%%s,%%%s\n", "addl", regtoa(source),
			regtoa(target));
}

void ATTAsmContext::sub(Register target, int val) {
	if (val < 0)
		add(target, -val);
	else
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

void ATTAsmContext::push(const char* val) {
	fprintf(getOutput(), "\t%s $%s\n", "pushl", val);
}

void ATTAsmContext::push(Register target, int offset) {
	fprintf(getOutput(), "\t%s %d(%%%s)\n", "pushl", offset, regtoa(target));
}

void ATTAsmContext::pop(Register target) {
	fprintf(getOutput(), "\t%s %%%s\n", "popl", regtoa(target));
}

void ATTAsmContext::pushf() {
	fprintf(getOutput(), "\t%s\n", "pushf");
}

void ATTAsmContext::popf() {
	fprintf(getOutput(), "\t%s\n", "popf");
}

void ATTAsmContext::shr(Register target, int val) {
	fprintf(getOutput(), "\t%s $%d,%%%s\n", "shrl", val, regtoa(target));
}

void ATTAsmContext::shl(Register target, int val) {
	fprintf(getOutput(), "\t%s $%d,%%%s\n", "shll", val, regtoa(target));
}

void ATTAsmContext::reserve(const char* name, int size, int type) {
	int realsize = size * type;
	fprintf(getOutput(), "\t.lcomm %s,%d\n", name, realsize);
}

void ATTAsmContext::fld(Register reg, int offset, bool longversion) {
	if (0 == offset) {
		fprintf(getOutput(), "\t%s (%%%s)\n", longversion ? "fldl" : "flds",
				regtoa(reg));
	} else {
		fprintf(getOutput(), "\t%s %d(%%%s)\n", longversion ? "fldl" : "flds",
				offset, regtoa(reg));
	}
}

void ATTAsmContext::fstp(Register reg, int offset, bool longversion) {
	if (0 == offset) {
		fprintf(getOutput(), "\t%s (%%%s)\n", longversion ? "fstpl" : "fstps",
				regtoa(reg));
	} else {
		fprintf(getOutput(), "\t%s %d(%%%s)\n", longversion ? "fstpl" : "fstps",
				offset, regtoa(reg));
	}
}

void ATTAsmContext::fstsw() {
	fprintf(getOutput(), "\t%s\n", "fstsw %%ax");
}

void ATTAsmContext::ffree(int a) {
	fprintf(getOutput(), "\t%s st(%d)\n", "ffree", a);
}

void ATTAsmContext::fcomip(int i) {
	fprintf(getOutput(), "\t%s %%st(%d),%%st\n", "fcomip", i);
}
