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
#include "icl_log.h"
#include "icl_string.h"

static void icl_sig_handler(int sig)
{
    icl_log_info("icl_sig_handler %d\n", sig);
}

void icl_sig_setup(void)
{
    int i;
    struct sigaction action;
    static int sig[] = {SIGINT, SIGQUIT, SIGTERM};
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = icl_sig_handler;
    for (i = 0; i < sizeof(sig)/sizeof(sig[0]); i++ ) {
        if (sigaction(sig[i], &action, (struct sigaction*)0) < 0)
        {
            icl_log_fital("sigaction: %s\n fital.", icl_sigitoa(sig[i]));
        }
    }
}

char *icl_sigitoa(int sig)
{
    char *siga;
    switch (sig) {
        case 1:
            siga = icl_strdump("SIGINT");
            break;
        case 2:
            siga = icl_strdump("SIGQUIT");
            break;
        case 3:
            siga = icl_strdump("SIGTERM");
        default:
            siga = icl_strdump("UNKNOW");
            break;
    }
    return siga;
}
