/*
 * icl_log.c
 *
 *  Created on : 2014年4月14日
 *      Author : peterxmw
 */

#include "icl_log.h"
#include "icl_string.h"
#include "icl_time.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

//这里是一个全局变量
static int fd;

int icl_open_file(const char *filename) {
	fd = open(filename, O_WRONLY|O_APPEND|O_CREAT, 0644);
	if (fd == -1)
	{
		icl_log_stdout("%s(%d) open fail.", __FILE__, __LINE__);
		return -1;
	}
	return 0;
}

void icl_close_file() {
	close(fd);
}

void icl_set_level(int lvl)
{
    glevel = lvl;
}


void icl_log_wn(int lvl, char *fmt, ...)
{
    int len;
    char buf[4096];
    char *str_lvl;
    switch (lvl) {
        case 1:
            str_lvl = "INFO";
            break;
        case 2:
            str_lvl = "WARN";
            break;
        case 3:
            str_lvl = "ERROR";
            break;
        case 4:
            str_lvl = "FITAL";
            break;
        case 5:
            str_lvl = "DEBUG";
            break;
        case 6:
            str_lvl = "TRACK";
            break;
        default:
            str_lvl = NULL;
            break;
    }
    len = sprintf(buf, "%s\t[%s]\t[%d]\t", icl_asctime(), str_lvl, getpid());
    va_list args;
    va_start(args, fmt);
    //icl_log_wn(&buf[len], fmt, args);
    vsprintf(&buf[len], fmt, args);
    if (fd)
        (void) write(fd, buf, (int) strlen(buf));
    va_end(args);
    

    /* 这里如果是fatal错误，直接强迫程序退出 */
    if (icl_strcmp(str_lvl, "FATAL")) {
    	assert("0");
    }
}

//这个一个原始函数， 需要在外层加入fmt等缺省函数
//日志输出的格式为： time    level   pid     tid    content

//void icl_log_wn(char *buf, char *fmt, va_list ap) {
//	int len;
//	/* 这里限定了buf的大小为2048，超过的数据会被丢弃 */
//     
//	len = vsprintf(buf, fmt, ap);
//	if (!fd) {
//		(void) write (fd, buf, len);
//	}
//}

void icl_log_stdout(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}
