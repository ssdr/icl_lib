/*
 * author:    xiemin
 * filename:  icl_array.h
 * company:   ifeng
 * date:      2014-09-29
 *
 */


#ifndef ICL_ARRAY_H_
#define ICL_ARRAY_H_

#include <stdio.h>
#include <stdlib.h>

struct Icl_Array {
	int nelt;
	int pos; //current position
	int elt_size;
	void *p; //start point
};
typedef struct Icl_Array Icl_Array;

Icl_Array *icl_array_create(int n, int size);

void *icl_array_index(Icl_Array *iay, int idx);

void *icl_array_push_back(Icl_Array *iay);

int icl_array_append(Icl_Array *iay);

int icl_array_destroy(Icl_Array *iay);

#endif /*ICL_ARRAY_H_*/

