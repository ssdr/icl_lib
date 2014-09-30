/*
 * icl_array.c
 *
 *  Created on: 2014年9月3日
 *      Author: peterxmw
 */


#include "icl_fork.h"


char *icl_getenv(const char *name)
{
	char *reptr = getenv(name);
	if (reptr == NULL) {
		printf("getenv failed\n");
	}
	return reptr;
}


int icl_putenv(const char *str)
{
	/* overwrite old value */
	int ret = putenv(str);
	if (ret != 0) {
		printf("putenv failed\n");
		return -1;
	}
	return 0;
}

int icl_setenv(const char *name, const char *value, int rewrite)
{
	/* if rewrite is zero, overwrite value 
	 *  otherwise do noting
	 */
	int ret = setenv(name, value, rewrite);
	if (ret != 0) {
		printf("setenv failed\n");
		return -1;
	}
	return 0;
}

int icl_getopt(int argc, char * const argv[], const char *optstring)
{
	char ch;
	switch(ch = getopt(argc, argv, "hr:t:f:X:")) {
		case 'h':
			break;
		case 'r':
			break;
		case 't':
			break;
		case 'f':
			break;
		case 'X':
			break;
		default:
			break;
	}
}

pid_t fork(void)
{
	return fork();
}
	