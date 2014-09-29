/*
 * icl_list.h
 *
 *  Created on: 2014Äê1ÔÂ27ÈÕ
 *      Author: peterxmw
 */

#ifndef ICL_LIST_H_
#define ICL_LIST_H_

typedef struct icl_list ICL_LIST;

struct icl_list {
	void *data;
	ICL_LIST *prev;
	ICL_LIST *next;
};

ICL_LIST* icl_list_init();

int icl_list_empty(ICL_LIST *h);

int icl_list_size(ICL_LIST *h);

int icl_list_push_back(ICL_LIST *h, void *d);

int icl_list_push_front(ICL_LIST *h, void *d);

ICL_LIST *icl_list_pop_back(ICL_LIST *h);

ICL_LIST *icl_list_pop_front(ICL_LIST *h);

int icl_list_clear(ICL_LIST *h);

#endif /* ICL_LIST_H_ */
