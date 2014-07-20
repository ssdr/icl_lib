/*
 * wyf_log.h
 *
 *  Created on: 2014Äê2ÔÂ8ÈÕ
 *      Author: peterxmw
 */

#ifndef WYF_LOG_H_
#define WYF_LOG_H_

typedef void (*wyf_log_fn)(int, char*, ....) WYF_LOG_FN;

struct logger {
	int fd;
	char *name;
	WYF_LOG_FN log_fn; 
};

typedef struct logger LOGGER;

int wyf_open_file(const char *filename);

void wyf_close_file(int fd);

void wyf_log_def(int fd, char *fmt, ...);

#endif /* WYF_LOG_H_ */
