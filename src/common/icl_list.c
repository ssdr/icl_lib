/*
 * icl_list.c
 *
 *  Created on : 2014年3月1日
 *      Author : peterxmw
 */

#include <icl_list.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//整体的结构是一个闭环, 并且是一个双向链表
/*
 *  其中H这个节点并不存放任何任何数据
 *
 *   ------------------------
 *   |                      |
 *  \/                      |
 * ----    ----    ----    ----
 * | H|--->|  |--->|  |--->|  |
 * |  |<---|  |<---|  |<---|  |
 * ----    ----    ----    ----
 *  |                       /\
 *  |                       |
 *  -------------------------
 *
 */



static assert_null(Icl_List *h)
{
	assert(h != NULL);
}


Icl_List *icl_list_init()
{
	Icl_List *h = (Icl_List*) malloc ( sizeof(Icl_List) );
	if (h == NULL)
	{
		return NULL;
	}
	h->prev = h->next = h;
	h->data = NULL;
	return h;
}

int icl_list_empty(Icl_List *h)
{
	assert_null(h);

	if (h->prev == h)
		return 0;
	else
		return 1;
}

int icl_list_size(Icl_List *h)
{
	assert_null(h);
	Icl_List *p;
	int count = 0;
	for(p = h; p->next != h; p=p->next)
	{
		count++;
	}
	return count;
}

int icl_list_push_back(Icl_List *h, void *d)
{
	assert_null(h);

	Icl_List *q = (Icl_List*) malloc (sizeof(Icl_List));
	if (q == NULL)
	{
		printf("%s(%d) malloc Icl_List fail.", __FILE__, __LINE__);
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

int icl_list_push_front(Icl_List *h, void *d)
{
	assert_null(h);
	Icl_List *q = (Icl_List*) malloc (sizeof(Icl_List));
	if (q == NULL)
	{
		printf("%s(%d) malloc Icl_List fail.", __FILE__, __LINE__);
		return -1;
	}
	q->data = d;
	h->next->prev = q;
	q->next = h->next;
	h->next = q;
	q->prev = h;
	return 0;
}

Icl_List *icl_list_pop_back(Icl_List *h)
{
	assert_null(h);
	Icl_List *q;
	q = h->prev;
	q->prev->next = h;
	h->prev = q->prev;
	q->prev = NULL;
	q->next = NULL;
	return q;
}

Icl_List *icl_list_pop_front(Icl_List *h)
{
	assert_null(h);
	Icl_List *q;
	q = h->next;
	q->next->prev = h;
	h->next = q->next;
	q->prev = NULL;
	q->next = NULL;
	return q;
}


int icl_list_destroy(Icl_List *h)
{
	assert_null(h);
	Icl_List *q;
	while(icl_list_size(h) != 0)
	{
		q = icl_list_pop_front(h);
		icl_list_free(q);
	}
	icl_list_free(h);
    return 0;
}

int icl_list_free(Icl_List *p)
{
	if (p->data != NULL) {
		free(p->data);
	}
	if (p != NULL) {
		free(p);
	}
	return 0;
}
