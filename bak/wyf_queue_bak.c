/*
 * wyf_queue.c
 *
 *  Created on: 2014Äê1ÔÂ27ÈÕ
 *      Author: peterxmw
 */

 #include "wyf_queue.h"


WYF_QUEUE* wyf_queue_init()
{
	WYF_QUEUE *h = (WYF_QUEUE*) malloc ( sizeof(WYF_QUEUE) );
	if (h == NULL)
	{
		return NULL;
	}
	h->prev = h->next = h;
	h->data = NULL;
	return h;
}

int wyf_queue_empty(WYF_QUEUE *h)
{
	if (h->prev == h)
		return 1;
	else
		return 0;
}

int wyf_queue_size(WYF_QUEUE *h)
{
	WYF_QUEUE *p;
	int count = 0;
	for(p = h; p->next != h; p=p->next)
	{
		count++;
	}
	return count;
}

int wyf_queue_push_back(WYF_QUEUE* h, void* d)
{
	WYF_QUEUE *q = (WYF_QUEUE*) malloc (sizeof(WYF_QUEUE));
	if (q == NULL)
	{
		wyf_log_stdout("%s(%d) malloc WYF_QUEUE fail.", __FILE__, __LINE__);
		return -1;
	}
	q->data = d;
	h->prev->next = q;
	q->prev = h->prev;
	h->prev = q;
	q->next = h;
	return 0;
}

int wyf_queue_push_front(WYF_QUEUE* h, void* d)
{
	WYF_QUEUE *q = (WYF_QUEUE*) malloc (sizeof(WYF_QUEUE));
	if (q == NULL)
	{
		wyf_log_stdout("%s(%d) malloc WYF_QUEUE fail.", __FILE__, __LINE__);
		return -1;
	}
	q->data = d;
	h->next->prev = q;
	q->next = h->next;0
	h->next = q;
	q->prev = h;
	return 0;
}

WYF_QUEUE* wyf_queue_pop_back(WYF_QUEUE *h)
{
	WYF_QUEUE *q;
	q = h->prev;
	q->prev->next = h;
	h->prev = q->prev;
	q->prev = NULL;
	q->next = NULL;
	return q;
}

WYF_QUEUE* wyf_queue_pop_front(WYF_QUEUE *h)
{
	WYF_QUEUE *q;
	q = h->next;
	q->next->prev = h;
	h->next = q->next;
	q->prev = NULL;
	q->next = NULL;
	return q;
}


int wyf_queue_clear(WYF_QUEUE *h)
{
	WYF_QUEUE *q;
	while(wyf_queue_size(h) == 0)
	{
		q = wyf_queue_pop_front(h);
		free(q);
	}
}
