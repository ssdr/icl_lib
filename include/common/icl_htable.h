/*
 * icl_htable.h
 *
 *  Created on: 2014Äê10ÔÂ5ÈÕ
 *      Author: peterxiemin
 */



#ifndef ICL_HTABLE_H_
#define ICL_HTABLE_H_

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
