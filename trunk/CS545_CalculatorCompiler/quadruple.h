/*
 * quadruple.h
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#ifndef QUADRUPLE_H_
#define QUADRUPLE_H_

#include "common.h"

typedef enum _ValueType {
	NUM, VAR
} ValueType;

typedef struct _Value {
	ValueType type;
	union {
		int value;
		const char* varName;
	};
} Value;

class Quadruple {
public:
	OPR opr;
	Value left;
	Value right;

	Quadruple(OPR opr, Value left, Value right) {
		this->opr = opr;
		this->left = left;
		this->right = right;
	}
	virtual ~Quadruple();
};

#endif /* QUADRUPLE_H_ */
