/*
 * icl_htable.h
 *
 *  Created on: 2014-10-25
 *      Author: peterxiemin
 */



#ifndef ICL_HTABLE_H_
#define ICL_HTABLE_H_

#include <icl_hash.h>
#include <stdio.h>

typedef struct icl_htable_node icl_htable_node;

#define KEY_SIZE 64
#define VAL_SIZE 128

struct icl_htable_node
{
	char key[KEY_SIZE];
	char value[VAL_SIZE];
	icl_htable_node *next;
};

typedef struct icl_htable_t icl_htable_t;
struct icl_htable_t
{
	icl_htable_node **p;
	int size;
};

icl_htable_t *icl_htable_create(int size);

#endif ICL_HTABLE_H_
