/*
 * common.h
 *
 *  Created on: Feb 11, 2013
 *      Author: harper
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <string.h>
#include <stdio.h>

struct comp {
	bool operator()(const char* a, const char* b) {
		return strcmp(a, b) < 0;
	}
};

#endif /* COMMON_H_ */
