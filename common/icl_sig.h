//
//  icl_sig.h
//  icllib
//
//  Created by peterxm on 14-3-20.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//

#ifndef icllib_icl_sig_h
#define icllib_icl_sig_h

void icl_sig_setup(void);

char *icl_sigitoa(int sig);

static void icl_sig_handler(int sig);

#endif
