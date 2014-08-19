//
//  icl_sig.c
//  icllib
//
//  Created by peterxm on 14-3-20.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <signal.h>
#include "icl_sig.h"
#include "icl_string.h"


#define SIGCOUNT 64

int sig[SIGCOUNT];
static int index;

void icl_sig_handler(int sig)
{
    printf("icl_sig_handler %d\n", sig);
}

int icl_sig_register(int index) 
{
	if (sig[index] == 0) {
		sig[index] = 1;
	}
	else {
		printf("sig %d already register!\n", index);
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
		if (sig[i] == 1 && sigaction(sig[i], &action, (struct sigaction*)0) < 0)
		{
			printf("sigaction: %s\n fital.", sig[i]);
		}
	}
}
