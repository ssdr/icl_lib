/*
 * wyf_queue.h
 *
 *  Created on: 2014Äê1ÔÂ27ÈÕ
 *      Author: peterxmw
 */

#ifndef WYF_QUEUE_H_
#define WYF_QUEUE_H_

typedef struct wyf_queue WYF_QUEUE;

struct wyf_queue {
	void *data;
	WYF_QUEUE *prev;
	WYF_QUEUE *next;
};

WYF_QUEUE* wyf_queue_init();

int wyf_queue_empty(WYF_QUEUE*);

int wyf_queue_size(WYF_QUEUE*);

WYF_QUEUE* wyf_queue_push_back(WYF_QUEUE*);

WYF_QUEUE* wyf_queue_push_front(WYF_QUEUE*);

WYF_QUEUE* wyf_queue_pop_back(WYF_QUEUE*);

WYF_QUEUE* wyf_queue_pop_front(WYF_QUEUE*);

void* wyf_queue_clear(WYF_QUEUE*);

#endif /* WYF_QUEUE_H_ */
