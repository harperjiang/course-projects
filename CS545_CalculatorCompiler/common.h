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

typedef enum _OPR {
	OINVALID = 0, OADD = 1, OSUB, OMUL, ODIV, OMOD, OCALL, OPARAM
} OPR;

typedef enum _ValueType {
	TYPE_NUM, TYPE_VAR

} ValueType;

#endif /* COMMON_H_ */
