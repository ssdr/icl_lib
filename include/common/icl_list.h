/*
 * icl_list.h
 *
 *  Created on: 2014-09-27
 *      Author: peterxmw
 */

#ifndef Icl_List_H_
#define Icl_List_H_

typedef struct icl_list Icl_List;

struct icl_list {
	void *data;
	Icl_List *prev;
	Icl_List *next;
};

Icl_List* icl_list_init();

int icl_list_empty(Icl_List *h);

int icl_list_size(Icl_List *h);

int icl_list_push_back(Icl_List *h, void *d);

int icl_list_push_front(Icl_List *h, void *d);

Icl_List *icl_list_pop_back(Icl_List *h);

Icl_List *icl_list_pop_front(Icl_List *h);

int icl_list_clear(Icl_List *h);

int icl_list_destroy(Icl_List *p);

#endif /* Icl_List_H_ */
