/*
 * quadruple.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: harper
 */

#include "quadruple.h"

Quadruple::~Quadruple() {
	delete result;
	delete left;
	delete right;
}

