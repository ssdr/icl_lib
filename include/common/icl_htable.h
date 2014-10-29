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

typedef struct Icl_Htable_Node Icl_Htable_Node;

#define KEY_SIZE 64
#define VAL_SIZE 128

struct Icl_Htable_Node
{
	char key[KEY_SIZE];
	char value[VAL_SIZE];
	Icl_Htable_Node *next;
};

typedef struct Icl_Htable Icl_Htable;

struct Icl_Htable
{
	Icl_Htable_Node **p;
	int size;
};

Icl_Htable *icl_htable_create(int size);

#endif /*ICL_HTABLE_H_*/
