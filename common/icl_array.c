/*
 * icl_array.c
 *
 *  Created on: 2014年3月1日
 *      Author: peterxmw
 */

#include "icl_array.h"
#include <stdlib.h>

//整体的结构是一个闭环

ICL_ARRAY *icl_array_init()
{
	ICL_ARRAY *h = (ICL_ARRAY*) malloc ( sizeof(ICL_ARRAY) );
	if (h == NULL)
	{
		return NULL;
	}
	h->prev = h->next = h;
	h->data = NULL;
	return h;
}

int icl_array_empty(ICL_ARRAY *h)
{
	if (h->prev == h)
		return 0;
	else
		return 1;
}

int icl_array_size(ICL_ARRAY *h)
{
	ICL_ARRAY *p;
	int count = 0;
	for(p = h; p->next != h; p=p->next)
	{
		count++;
	}
	return count;
}

int icl_array_push_back(ICL_ARRAY *h, void *d)
{
	ICL_ARRAY *q = (ICL_ARRAY*) malloc (sizeof(ICL_ARRAY));
	if (q == NULL)
	{
		printf("%s(%d) malloc ICL_ARRAY fail.", __FILE__, __LINE__);
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

int icl_array_push_front(ICL_ARRAY *h, void *d)
{
	ICL_ARRAY *q = (ICL_ARRAY*) malloc (sizeof(ICL_ARRAY));
	if (q == NULL)
	{
		printf("%s(%d) malloc ICL_ARRAY fail.", __FILE__, __LINE__);
		return -1;
	}
	q->data = d;
	h->next->prev = q;
	q->next = h->next;
	h->next = q;
	q->prev = h;
	return 0;
}

ICL_ARRAY *icl_array_pop_back(ICL_ARRAY *h)
{
	ICL_ARRAY *q;
	q = h->prev;
	q->prev->next = h;
	h->prev = q->prev;
	q->prev = NULL;
	q->next = NULL;
	return q;
}

ICL_ARRAY *icl_array_pop_front(ICL_ARRAY *h)
{
	ICL_ARRAY *q;
	q = h->next;
	q->next->prev = h;
	h->next = q->next;
	q->prev = NULL;
	q->next = NULL;
	return q;
}


int icl_array_clear(ICL_ARRAY *h)
{
	ICL_ARRAY *q;
	while(icl_array_size(h) == 0)
	{
		q = icl_array_pop_front(h);
		free(q);
	}
    return 0;
}
