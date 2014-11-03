/*
 * icl_unix.c
 *
 *  Created on: 2014年10月29日
 *      Author: peterxm
 */


#include <icl_unix.h>


char *icl_getenv(const char *name)
{
	char *reptr = getenv(name);
	if (reptr == NULL) {
		printf("getenv failed\n");
	}
	return reptr;
}


int icl_putenv(char *str)
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
	int num = 0;
	char ch;
	/*
	 * hr::t:f:X: 中 ":" 表示-t 后必须跟参数 "::"表示-r 后面可以跟参数也可以不跟参数
	 * "" 表示h后面不跟参数。也可以后面一个参数都不跟
	 */
	while((ch = getopt(argc, argv, "hr::t:f:X:")) != -1) {
		switch(ch) {
			case 'h':
				/* ./a.out -t 3 */
				num = atoi(optarg);		
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
}

pid_t icl_fork(void)
{
	return fork();
}

int icl_execve(const char *pathname, char * const argv[], 
		char * const envp[])
{
	return execve(pathname, argv, envp);
}

int icl_dup(int oldfd)
{
	return dup(oldfd);
}

int icl_pipe(int pipefd[2])
{
	int ret = pipe(pipefd);
	/* fail */
	if (ret == -1) {
		return -1;
	}
	return 0;
}

void icl_assert(int torf)
{
	/*
	 * torf == 0 , assert break prog
	 */
	assert(torf);
}

void icl_prtf_wtpid(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char buf[128];
	int len = snprintf(buf, 128, "[%d]\t", getpid());
	vsprintf(&buf[len], fmt, args);
	printf("%s", buf);
	va_end(args);
}
	

