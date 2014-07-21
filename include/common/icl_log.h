/*
 * icl_log.h
 *
 *  Created on: 2014年3月2日
 *      Author: peterxiemin
 */

#ifndef ICL_LOG_H_
#define ICL_LOG_H_


#include <stdarg.h>


/* 在这里加入日志等级 */

#define ICL_INFO  1
#define ICL_WARN  2
#define ICL_ERROR 3
#define ICL_FITAL 4
#define ICL_DEBUG 5
#define ICL_TRACK 6

//默认的级别是info
static int glevel = 1;


//#define icl_log_info(fmt, ...)  \
//if (glevel >= ICL_INFO) icl_log_wn(ICL_INFO, fmt, ...)
//#define icl_log_warn(fmt, ...)  \
//if (glevel >= ICL_WARN) icl_log_wn(ICL_WARN, fmt, ...)
//#define icl_log_error(fmt, ...) \
//if (glevel >= ICL_ERROR) icl_log_wn(ICL_ERROR, fmt, ...)
//#define icl_log_fital(fmt, ...) \
//if (glevel >= ICL_FITAL) icl_log_wn(ICL_FITAL, fmt, ...)
//#define icl_log_debug( fmt, ...) \
//if (glevel >= ICL_DEBUG) icl_log_wn(ICL_DEBUG, fmt, ...)
//#define icl_log_track(fmt, ...) \
//if (glevel >= ICL_TRACK) icl_log_wn(ICL_TRACK, fmt, ...)


#define icl_log_info(fmt, ...)  \
if (glevel >= ICL_INFO) icl_log_wn(ICL_INFO, fmt, __VA_ARGS__)
#define icl_log_warn(fmt, ...)  \
if (glevel >= ICL_WARN) icl_log_wn(ICL_WARN, fmt, __VA_ARGS__)
#define icl_log_error(fmt, ...) \
if (glevel >= ICL_ERROR) icl_log_wn(ICL_ERROR, fmt, ##__VA_ARGS__)
#define icl_log_fital(fmt, ...) \
if (glevel >= ICL_FITAL) icl_log_wn(ICL_FITAL, fmt, __VA_ARGS__)
#define icl_log_debug( fmt, ...) \
if (glevel >= ICL_DEBUG) icl_log_wn(ICL_DEBUG, fmt, __VA_ARGS__)
#define icl_log_track(fmt, ...) \
if (glevel >= ICL_TRACK) icl_log_wn(ICL_TRACK, fmt, __VA_ARGS__)


//这里主要是想通过函数让开发者自定义打日志函数

//typedef void (*ICL_LOG_FN) (int , char *fmt, ...);
//
//typedef struct g_log{
//    ICL_LOG_FN log_fn;
//    int fd;
//} G_LOG;
//
//ICL_ARRAY * g_logs;




int icl_open_file(const char *filename);

void icl_close_file();

void icl_set_level(int lvl);

void icl_log_wn(int lvl, char *fmt, ...);

void icl_log_stdout(char *fmt, ...);

//void icl_log_info(char *fmt, ...);

#endif /* ICL_LOG_H_ */
