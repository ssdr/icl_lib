/*
 * icl_string.h
 *
 *  Created on: 2014年1月24日
 *      Author: peterxmw
 */

#ifndef ICL_STRING_H_
#define ICL_STRING_H_


char *icl_strdump(char *src);

int icl_strcpy(char *dst, char *src);

char *icl_strcat(char *dst, char *src);

int icl_strlen(char *ops);

int icl_strcmp(char *dst, char *src);

int icl_strncmp(char *dst, char *src, int len);

char *icl_strerror(void);

int icl_errno(void);

#endif /* ICL_STRING_H_ */
