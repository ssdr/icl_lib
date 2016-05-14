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

int icl_htable_set(Icl_Htable *iht, const char *key, const char *value);

int icl_htable_get(Icl_Htable *iht, const char *key, char *value, int value_size);

int icl_htable_del(Icl_Htable *iht, const char *key);

int icl_htable_destroy(Icl_Htable *iht);
#endif /*ICL_HTABLE_H_*/
