//
//  icl_time.c
//  icllib
//
//  Created by peterxm on 14-3-1.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//

#include <stdio.h>
#include <time.h>

char *icl_asctime()
{
typedef struct tm STRC_TM;
    char *time_str;
    int pos;
    time_t t_clock;
    STRC_TM *stm;
    (void) time(&t_clock);
    stm = localtime(&t_clock);
    time_str = asctime(stm);
    pos = strlen(time_str);
    //删除最后最后一个换行符
    time_str[pos-1] = '\0';
    return time_str;
}
