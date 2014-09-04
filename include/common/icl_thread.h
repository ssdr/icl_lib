#include <stdio.h>
#include <stdlib.h>

/*
 * icl_thread.h
 *
 *  Created on: 2014年9月2日
 *      Author: peterxm
 */


#ifndef _ICL_THREAD_H_
#define _ICL_THREAD_H_

#include <stdio.h>
#include <pthread.h>
/* static or stack pthread_cond_t */
#define ICL_PTHREAD_COND_INITIALIZER PTHREAD_COND_INITIALIZER
/* static or stack pthread_mutex_t */
#define ICL_PTHREAD_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

int icl_pthread_equal(pthread_t td1, pthread_t td2);
pthread_t icl_pthread_self(void);
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		                          void *(*start_routine) (void *), void *arg);

#endif


