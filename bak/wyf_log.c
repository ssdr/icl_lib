/*
 * wyf_log.c
 *
 *  Created on: 2014Äê1ÔÂ23ÈÕ
 *      Author: peterxmw
 */

#include "wyf_log.h"
#include "wyf_array.h"
#include "wyf_string"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <assert.h>

//static WYF_ARRAY *loggers;

/*
 * void wyf_log_error(int fd, char *fmt, ...) {
 */

//int wyf_log_register(WYF_LOG_FN log_fn) {
//	ITER *iter;
//	WYF_FOREACH(iter, loggers)
//	{
//		iter->data->
//	}
//}

int wyf_open_file(const char *log_nm, WYF_LOG_FN log_fn) {
	int fd;
	LOGGER *log;

	log = (LOGGER*) malloc (sizeof(LOGGER));
	if (log == NULL)
	{
		wyf_log_stdout("%s(%d) malloc LOGGER fail.", __FILE__, __LINE__);
		return -1;
	}
	
	fd = open(filename, O_WRONLY|O_APPEND|O_CREAT, 0644);
	if (fd == -1)
	{
		wyf_log_stdout("%s(%d) open fail.", __FILE__, __LINE__);
		return -1;
	}
	log->fd = fd;
	log->name = wyf_strdup(log_nm);
	log->log_fn = log_fn;

	if (loggers == NULL) 
		loggers = wyf_array_init();

	(void) wyf_array_push_back(loggers, (void*) log);
	return 0;
}

void wyf_close_file(int fd) {
	close(fd);
}

/*
 * 这里需要注用户自己定义
 * 这里的设计主要是考虑开发人员的这个需求：
 * 想要在不同的文件中写日志
void wyf_log_cus1(char *fmt, ...)
{
	char log_fm[] = "./log";
	va_list args;
	va_start(args, fmt);
	wyf_log_def(log_fm, fmt, args);
	va_end(args);
}
*/

void wyf_log_def(char *name, char *fmt, va_list ap) {
	int len;
	ITER iter;
	int fd = -1;
	char buf[2048];
	len = vsprintf(buf, fmt, ap);
	WYF_FOREACH(iter, loggers) {
		if (iter->data->name == name) {
			fd = iter->data->fd;
			break;
		}
	}
	if (fd != -1)
		(void) write (fd, buf, len);
}

void wyf_log_stdout(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}
