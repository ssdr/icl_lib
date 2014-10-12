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
#include <string.h>
#include <unistd.h> /*fork*/

char *icl_getenv(const char *name);
int icl_putenv(char *str);
int icl_setenv(const char *name, const char *value, int rewrite);
int icl_getopt(int argc, char * const argv[], const char *optstring);
pid_t icl_fork(void);
int icl_execve(const char *pathname, const char *argv[], const char *envp[]);

#endif /*ICL_FORK_H_*/
