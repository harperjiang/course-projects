/*
 ============================================================================
 Name        : main.cpp
 Author      : Hao Jiang
 Version     :
 Description   : CS545 Compiler
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "node.h"
#include "eval_context.h"
#include "exception.h"

#define ESC 27

extern Program* parse_result;
extern void passet_in(FILE* f);
extern void pasparse();

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
		const int outputFormat, const int asmstyle);

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
				"Error: No input file specified. Use -h to see available options",
				ESC);
		exit(1);
	}

	try {
		parse_input(argv[optind], outputFile, outputFormat, asmstyle);
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
	fprintf(stdout, "%c[1mUsage%c[0m: pasc [OPTION] <input file>\n", ESC, ESC);
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
	passet_in(inputFile);
	pasparse();
	if (parse_result == NULL)
		return;
	// Evaulate the parse result
	EvalContext* evalcontext = new EvalContext();

	parse_result->evaluate(evalcontext);

	bool haserror = 0;
	if ((haserror = evalcontext->haserror())) {
		evalcontext->showerror();
	}
	delete evalcontext;
	if (haserror)
		return;

	// Generate output
	switch (format) {
	case ASM:
		break;
	case TREE:
		parse_result->print(outputFile, 0);
		break;
	default:
		throw ILLEGAL_FORMAT;
	}
	delete parse_result;
}

void error(const char* info) {
	fprintf(stderr, "%c[31;1m%s%c[0m\n", ESC, info, ESC);
}
