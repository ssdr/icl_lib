//
//  icl_time.h
//  icllib
//
//  Created by peterxm on 14-3-1.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//

#ifndef ICLLIB_ICL_TIME_H
#define ICLLIB_ICL_TIME_H

/*
 * struct timespec {
 * time_t tv_sec;
 * long   tv_nsec;
 * } */
typedef struct timespec TimeSpec;

char *icl_asctime(void);
void min2tmspec(TimeSpec *tsp, long minutes);
void sec2tmspec(TimeSpec *tsp, long seconds);
void icl_prtnow();

#endif
