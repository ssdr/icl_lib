/*
 * icl_string.c
 *
 *  Created on: 2014年4月11日
 *      Author: peterxmw
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "icl_string.h"
#include <errno.h>

char *icl_strdump(char *src)
{
	size_t len = icl_strlen(src);
	char *dst = (char *) malloc(len+1);
	if (dst == NULL) {
		printf("error malloc!");
		return NULL;
	}
	dst[len] = 0;
	while (len--) {
		dst[len] = src[len];
	}
	return dst;
}

int icl_strcpy(char *dst, char *src)
{
	int len, i;
	if (dst == NULL || src == NULL) {
		printf("dst ptr NULL or src ptr NULL!");
		return -1;
	}
	size_t len_dst = icl_strlen(dst);
	size_t len_src = icl_strlen(src);
	len = len_dst > len_src ? len_dst : len_src;

	for (i = 0; i < len; i++) {
		dst[i] = src[i];
	}
	dst[len] = 0;
	return 0;
}

char *icl_strcat(char *dst, char *src)
{
	return strcat(dst, src);
}

int icl_strlen(char *ops)
{
	return (int) strlen(ops);
}

void icl_strdump_free(char *ptr)
{
	free(ptr);
}

int icl_strcmp(char *dst, char *src)
{
	return strcmp(dst, src);
}

int icl_strncmp(char *dst, char *src, int len)
{
	return strncmp(dst, src, len);
}

char *icl_strerror(void)
{
	return strerror(errno);
}

int icl_errno(void)
{
	return (errno);
}
