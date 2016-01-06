/*
 * icl_string.h
 *
 *  Created on: 2014年1月24日
 *      Author: peterxmw
 */

#ifndef ICL_STRING_H_
#define ICL_STRING_H_

/*
 * 说明sprintf(char ret, char *format, char *src);
 * 如果src中存在0, NULL, '\0'那么此复制操作就会自动结束
 * 如果第一个字符就是0， NULL, '\0', 那么复制操作根本不
 * 会执行
 */

char *icl_strdump(char *src);

int icl_strcpy(char *dst, char *src);

char *icl_strcat(char *dst, char *src);

int icl_strlen(char *ops);

int icl_strcmp(char *dst, char *src);

int icl_strncmp(char *dst, char *src, int len);

char *icl_strerror(void);

int icl_errno(void);

#endif /* ICL_STRING_H_ */
