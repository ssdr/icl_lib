/*
 * icl_unix.h
 *
 *  Created on: 2014年10月29日
 *      Author: peterxm
 */



#ifndef ICL_FORK_H_
#define ICL_FORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /*fork*/
#include <assert.h>
#include <stdarg.h>

char *icl_getenv(const char *name);

int icl_putenv(char *str);

int icl_setenv(const char *name, const char *value, int rewrite);

int icl_getopt(int argc, char * const argv[], const char *optstring);

pid_t icl_fork(void);

int icl_dup(int oldfd);

int icl_execve(const char *pathname, char * const argv[], char * const envp[]);

int icl_dup(int oldfd);

int icl_pipe(int pipefd[2]);

void icl_assert(int torf);

void icl_prtf_wtpid(char *fmt, ...);
#endif /*ICL_FORK_H_*/
