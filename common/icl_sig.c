/*
 * icl_sig.c
 * icllib
 *
 * Created by peterxm on 14-3-20.
 * Copyright (c) 2014年 peterxm. All rights reserved.
 *
 *
 */
  
#include <stdio.h>
#include <signal.h>
#include <signal.h>
#include "icl_sig.h"
#include "icl_string.h"


#define SIGCOUNT 64

int sig[SIGCOUNT];

void icl_sig_handler(int sig)
{
	/* 注意，事件处理函数不能使用可重用函数 printf malloc 等
	 * 最好设置flag， 由函数外判断  */
	;;
}

int icl_sig_register(int index) 
{
	if (index > 0 && index <= 64) {
		if (sig[index] == 0) {
			sig[index] = index;
		}
		else {
			printf("sig %d already register!\n", index);
		}
	}

	return 0;
}

void icl_sig_setup(void)
{
	int i;
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = icl_sig_handler;
	for (i = 0; i < SIGCOUNT; i++ ) {
		if (sig[i] != 0 && sigaction(sig[i], &action, (struct sigaction*)0) < 0)
		{
			printf("sigaction: %s\n fital.", sig[i]);
		}
	}
}
