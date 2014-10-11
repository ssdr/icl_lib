/*
 * icl_fork.h
 *
 *  Created on: 2014年9月22日
 *      Author: peterxmw
 */



#ifndef ICL_FORK_H_
#define ICL_FORK_H_

#include <stdio.h>
#include <stdlib.h>
char *icl_getenv(const char *name);
int icl_putenv(char *str);
int icl_setenv(const char *name, const char *value, int rewrite);

#endif /*ICL_FORK_H_*/
