/*
 * author:	xiemin
 * filename: icl_array.h
 * company: ifeng
 * date: 2014-09-29
 *
 */


#ifndef ICL_ARRAY_H_
#define ICL_ARRAY_H_

#include <stdio.h>
#include <stdlib.h>

struct icl_array_t {
	int nelt;
	int pos; //current position
	int elt_size;
	void *p; //start point
};
typedef struct icl_array_t icl_array_t;
icl_array_t *icl_array_create(int n, int size);
void *icl_array_push_back(icl_array_t *iat);
int icl_array_append(icl_array_t *iat);
int icl_array_destroy(icl_array_t *iat);
#endif /*ICL_ARRAY_H_*/

