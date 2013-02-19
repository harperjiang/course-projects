#include "node.h"

const char* oprtoa(OPR input) {
	switch (input) {
	case OADD:
		return "+";
	case OSUB:
		return "-";
	case OMUL:
		return "*";
	case ODIV:
		return "/";
	default:
		return "Unrecognized";
	}
}

Expression::~Expression() {

}

Identifier::~Identifier() {
	delete name;
}

void Identifier::evaluate(EvalContext* context) {
	context->check(this->name);
}

void Identifier::genasm(AsmContext* context) {
	MemoryUnit* mu = context->find(this->name);
	context->mov(eax, mu->getPosition(), 1);
}

void Identifier::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "%s%s\n", "[Identifier]", this->name);
}

NumConstant::~NumConstant() {

}

void NumConstant::evaluate(EvalContext* context) {

}

void NumConstant::genasm(AsmContext* context) {
	context->mov(eax, this->value);
}

void NumConstant::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "%s%d\n", "[NumConstant]", this->value);
}

void ArithExpression::evaluate(EvalContext* context) {
	if (this->left != NULL)
		this->left->evaluate(context);
	this->right->evaluate(context);
}

void ArithExpression::genasm(AsmContext* context) {
	if (this->left == NULL)
		context->mov(eax, 0);
	else
		this->left->genasm(context);
	context->push(eax);
	this->right->genasm(context);
	context->pop(ebx);
	context->arith(ebx, eax, this->opr);
	context->mov(eax, ebx);
}

void ArithExpression::print(FILE*output, int level) {
	Node::print(output, level);
	fprintf(output, "%s%s\n", "[ArithExpression]", oprtoa(this->opr));
	if (NULL != this->left)
		this->left->print(output, level + 1);
	this->right->print(output, level + 1);
}

void AssignStatement::evaluate(EvalContext* context) {
	this->value->evaluate(context);
	context->addId(this->id->name);
}

void AssignStatement::genasm(AsmContext* context) {
	MemoryUnit* idalloc = context->find(this->id->name, 0);
	this->value->genasm(context);
	context->mov(idalloc->getPosition(), eax, 0);
}

void AssignStatement::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "[AssignStatement]\n");
	this->id->print(output, level + 1);
	this->value->print(output, level + 1);
}

void PrintStatement::evaluate(EvalContext* context) {
	this->expression->evaluate(context);
}

void PrintStatement::genasm(AsmContext* context) {
	this->expression->genasm(context);
	MemoryUnit* buffer = context->alloc(20);
	char* label0 = context->genlabel();
	char* label1 = context->genlabel();
	char* label2 = context->genlabel();
	char* label3 = context->genlabel();
	char* label4 = context->genlabel();
	char* label5 = context->genlabel();

	context->mov(ecx, "heap");
	context->add(ecx, buffer->getPosition());
	context->mov(ebx, 1);

	// if (eax == 0)
	// directly goto output
	context->cmp(eax, 0);
	context->jne(label0);
	context->mov(ecx, 48, 2);
	context->add(ecx, 4);
	context->jmp(label5);

	// if(eax < 0)
	// output a minus sign and change the number to positive
	context->label(label0);
	context->cmp(eax, 0);
	context->jge(label1);
	context->mov(ecx, '-', 2);
	context->add(ecx, 4);
	context->neg(eax);

	context->label(label1);
	context->cmp(eax, ebx);
	context->jle(label2);
	context->push(eax);
	context->mov(eax, ebx);
	context->mov(ebx, 10);
	context->mul(ebx);
	context->mov(ebx, eax);
	context->pop(eax);
	context->jmp(label1);

	context->label(label2);
	context->cmp(eax, ebx);
	context->jge(label3);
	context->push(eax);
	context->mov(eax, ebx);
	context->mov(ebx, 10);
	context->mov(edx, 0);
	context->div(ebx);
	context->mov(ebx, eax);
	context->pop(eax);

	context->label(label3);
	context->cmp(eax, 0);
	context->je(label4);
	context->push(edx);
	context->mov(edx, 0);
	context->div(ebx);
	context->add(eax, 48);
	context->mov(ecx, eax, 2);
	context->mov(eax, edx);
	context->add(ecx, 4);
	context->pop(edx);
	context->jmp(label2);

	context->label(label4);
	context->cmp(ebx, 0);
	context->je(label5);
	// output an zero
	context->mov(ecx, 48, 2);
	context->add(ecx, 4);

	// Output
	context->label(label5);
	context->mov(eax, 4);
	context->mov(ebx, 1);
	// ecx now has the end of buffer
	// Append \n\r
	context->mov(ecx, 0x0D, 2);
	context->add(ecx, 4);
	context->mov(ecx, 0x0A, 2);
	context->add(ecx, 4);

	context->push(ecx);
	context->mov(ecx, "heap");
	context->add(ecx, buffer->getPosition());
	// ecx has the beginning of buffer now
	context->pop(edx);
	context->sub(edx, ecx);
	// edx has the length now
	context->interrupt(0x80);
	context->dealloc(buffer);
}

void PrintStatement::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "%s\n", "[PrintStatement]");
	this->expression->print(output, level + 1);
}

Statements::~Statements() {
	this->statements->clear();
	delete this->statements;
}

void Statements::evaluate(EvalContext* context) {
	for (std::vector<Statement*>::iterator iterator = this->statements->begin();
			iterator != this->statements->end(); iterator++) {
		(*iterator)->evaluate(context);
	}
}

void Statements::genasm(AsmContext* context) {
	for (std::vector<Statement*>::iterator it = this->statements->begin();
			it != this->statements->end(); it++) {
		(*it)->genasm(context);
		// For Debugging purpose
		context->nop();
	}
}

void Statements::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "%s\n", "[Statements]");
	for (std::vector<Statement*>::iterator iterator = this->statements->begin();
			iterator != this->statements->end(); iterator++) {
		(*iterator)->print(output, level + 1);
	}
}

StatementBlock::~StatementBlock() {
	if (NULL != content)
		delete content;
}

void StatementBlock::evaluate(EvalContext* context) {
	context->pushFrame();
	content->evaluate(context);
	context->popFrame();
}

void StatementBlock::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "%s\n", "[StatementBlock]");
	this->content->print(output, level + 1);
}

void StatementBlock::genasm(AsmContext* context) {
	context->pushFrame();
	content->genasm(context);
	context->popFrame();
}

Program::~Program() {
	if (NULL != block)
		delete block;
}

void Program::evaluate(EvalContext* context) {
	block->evaluate(context);
}

void Program::print(FILE* output, int level) {
	Node::print(output, level);
	fprintf(output, "%s\n", "[Program]");
	this->block->print(output, level + 1);
}

void Program::genasm(AsmContext* context) {
	context->header();
	block->genasm(context);
	context->tail();
}
