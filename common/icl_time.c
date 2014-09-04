//
//  icl_time.c
//  icllib
//
//  Created by peterxm on 14-3-1.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

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

/* 
 * struct timespec {
 * 	time_t tv_sec;
 * 	long   tv_nsec;
 * } */
typedef struct timespec TimeSpec;

void min2tmspec(TimeSpec *tsp, long minutes)
{
	struct timeval now;
	/* get the current time */
	gettimeofday(&now);
	tsp->tv_sec = now.tv_sec;
	tsp->tv_nsec = now.tv_usec * 1000; /* usec to nsec */
	tsp->tv_sec += minutes * 60;
}

void sec2tmspec(TimeSpec *tsp, long seconds)
{
	struct timeval now;
	/* get the current time */
	gettimeofday(&now);
	tsp->tv_sec = now.tv_sec;
	tsp->tv_nsec = now.tv_usec * 1000; /* usec to nsec */
	tsp->tv_sec += seconds;
}

void icl_prtnow()
{
	char pTime[50];
	int		temI, t_Loop, t_Len;
	char	t_Room[128] = { 0x00  } ;
	time_t	t_When;
	struct timeval  t_Pri_Time;
	struct timezone tz;
	gettimeofday(&t_Pri_Time , &tz);
	time( &t_When  );
	sprintf( pTime, "%s", ctime( &t_When  )  );
	t_Loop = strlen( pTime  );
	for( temI=0; temI<t_Loop; temI++  )
	{
		if ( *( pTime + temI  ) == 0x0D ||
				*( pTime + temI  ) == 0x0A
		   )
		{
			*( pTime + temI  ) = 0x00;
			t_Len = strlen( pTime  );
			sprintf( t_Room, " ( %ld.%.3ld  )", t_Pri_Time.tv_sec, t_Pri_Time.tv_usec / 1000  );
		}
	}
	printf("%s, %s\n", pTime, t_Room);
}
