/*
 * icl_list.c
 *
 *  Created on: 2014年3月1日
 *      Author: peterxmw
 */

#include "icl_list.h"
#include <stdlib.h>
#include <stdio.h>

//整体的结构是一个闭环

ICL_LIST *icl_list_init()
{
	ICL_LIST *h = (ICL_LIST*) malloc ( sizeof(ICL_LIST) );
	if (h == NULL)
	{
		return NULL;
	}
	h->prev = h->next = h;
	h->data = NULL;
	return h;
}

int icl_list_empty(ICL_LIST *h)
{
	if (h->prev == h)
		return 0;
	else
		return 1;
}

int icl_list_size(ICL_LIST *h)
{
	ICL_LIST *p;
	int count = 0;
	for(p = h; p->next != h; p=p->next)
	{
		count++;
	}
	return count;
}

int icl_list_push_back(ICL_LIST *h, void *d)
{
	ICL_LIST *q = (ICL_LIST*) malloc (sizeof(ICL_LIST));
	if (q == NULL)
	{
		printf("%s(%d) malloc ICL_LIST fail.", __FILE__, __LINE__);
		return -1;
	}
    //如果只有h一个节点， 第二点如何加入？
    
	q->data = d;
	h->prev->next = q;
	q->prev = h->prev;
	h->prev = q;
	q->next = h;
	return 0;
}

int icl_list_push_front(ICL_LIST *h, void *d)
{
	ICL_LIST *q = (ICL_LIST*) malloc (sizeof(ICL_LIST));
	if (q == NULL)
	{
		printf("%s(%d) malloc ICL_LIST fail.", __FILE__, __LINE__);
		return -1;
	}
	q->data = d;
	h->next->prev = q;
	q->next = h->next;
	h->next = q;
	q->prev = h;
	return 0;
}

ICL_LIST *icl_list_pop_back(ICL_LIST *h)
{
	ICL_LIST *q;
	q = h->prev;
	q->prev->next = h;
	h->prev = q->prev;
	q->prev = NULL;
	q->next = NULL;
	return q;
}

ICL_LIST *icl_list_pop_front(ICL_LIST *h)
{
	ICL_LIST *q;
	q = h->next;
	q->next->prev = h;
	h->next = q->next;
	q->prev = NULL;
	q->next = NULL;
	return q;
}


int icl_list_clear(ICL_LIST *h)
{
	ICL_LIST *q;
	while(icl_list_size(h) == 0)
	{
		q = icl_list_pop_front(h);
		free(q);
	}
    return 0;
}
