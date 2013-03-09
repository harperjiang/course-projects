/*
 ============================================================================
 Name        : Calculator.c
 Author      : Hao Jiang
 Version     :
 Description   : CS545 Compiler
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "exception.h"
#include "node.h"

#define ESC 27

extern Program* parse_result;
extern void calset_in(FILE* f);
extern void calparse();

static const char* opts = "o:hti";

typedef enum _OUTPUT_FLAG {
	TREE = 1, ASM
} OUTPUT_FLAG;

typedef enum _ASM_STYLE {
	ATT = 1, INTEL
} ASM_STYLE;

void error(const char* info);

void print_help_info();
void parse_input(const char* inputfile, const char* outputFile,
		const int outputFormat,const int asmstyle);

int main(int argc, char** argv) {
	char* outputFile = NULL;
	int opt = -1;
	int outputFormat = ASM;
	int asmstyle = ATT;
	while ((opt = getopt(argc, argv, opts)) != -1) {
		switch (opt) {
		case 'o':
			outputFile = optarg;
			break;
		case 'h':
			print_help_info();
			exit(0);
		case 'i':
			asmstyle = INTEL;
			break;
		case 't':
			// print tree structure
			outputFormat = TREE;
			break;
		default:
			exit(1);
		}
	}

	if (optind == argc) {
		fprintf(stderr, "%c[31;1m%s%c[0m\n", ESC,
				"Error: No input file specified", ESC);
		exit(1);
	}

	try {
		parse_input(argv[optind], outputFile, outputFormat,asmstyle);
	} catch (int e) {
		switch (e) {
		case FILE_NOT_FOUND:
			error("Error: failed to open input file");
			break;
		case ILLEGAL_FORMAT:
			error("Error: unrecognized output format");
			break;
		default:
			break;
		}
	}
}

void print_help_info() {
	fprintf(stdout, "%c[1mUsage%c[0m: compiler [OPTION] <input file>\n", ESC,
			ESC);
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "\t%c[1m%s%c[0m%s\t%s\n", ESC, "-o", ESC, " <output file>",
			"Indicate output files");
	fprintf(stdout, "\t%c[1m%s%c[0m\t\t\t%s\n", ESC, "-t", ESC,
			"Output Tree Structure");
	fprintf(stdout, "\t%c[1m%s%c[0m\t\t\t%s\n", ESC, "-i", ESC,
			"Generate Intel Style Assembly (default AT&T)");
	fprintf(stdout, "\t%c[1m%s%c[0m\t\t\t%s\n", ESC, "-h", ESC,
			"Display help options");
}

void parse_input(const char* inputName, const char* outputName,
		const int format, const int asmstyle) {
	// Dealing with I/O
	FILE* inputFile = fopen(inputName, "r");
	if (NULL == inputFile)
		throw FILE_NOT_FOUND;
	FILE* outputFile = NULL;
	if (NULL == outputName)
		outputFile = stdout;
	else {
		outputFile = fopen(outputName, "w");
		if (NULL == outputFile)
			throw FILE_NOT_FOUND;
	}
	// Parse input
	calset_in(inputFile);
	calparse();

	// Check the parse result
	EvalContext* context = new EvalContext();
	parse_result->evaluate(context);

	if (context->geterror()) {
		context->showerror(outputFile);
		return;
	}
	delete context;

	// Generate output
	AsmContext* asmcontext = (asmstyle == ATT)?new ATTAsmContext(outputFile): new AsmContext(outputFile);
	switch (format) {
	case ASM:
		parse_result->genasm(asmcontext);
		break;
	case TREE:
		parse_result->print(outputFile, 0);
		break;
	default:
		throw ILLEGAL_FORMAT;
	}
	delete asmcontext;
}

void error(const char* info) {
	fprintf(stderr, "%c[31;1m%s%c[0m\n", ESC, info, ESC);
}
