/*
 * icl_mem.c
 *
 *  Created on: 2014-11-14
 *      Author: peterxm
 */

#include <stdio.h>
#include <stdlib.h>
#include "icl_mem.h"

static int ptr_count = 0;

void *icl_malloc(int len)
{
	void *ptr = malloc(len);
	if (ptr == NULL) {
		perror("malloc error");
	}
	ptr_count++;
	return ptr;
}

void *icl_calloc(int count, int len)
{
	void *ptr = calloc(count, len);
	if (ptr == NULL) {
		perror("calloc error");
	}
	ptr_count++;
	return ptr;
}

void *icl_realloc(void *ptr, int len)
{
	/* 如果len == 0, 那么realloc将返回 NULL , 或者一个曾经被释放的ptr指针 */
	if (len == 0) {
		return NULL;
	}
	/* 如果len != 0， realloc分配失败后,将返回 NULL,不改变原ptr指针的任何内容
	 * 一旦realloc分配成功后，
	 * 如果因为原堆空间充足，将直接在原ptr指针所致的空间后追加新的空间
	 * 如果原堆空间不足，将原堆栈空间拷贝至新的推空间（并且是新增len长度的空间)
	 * 然后将原ptr空间释放掉, realloc的第一个参数和return都将返回新空间的地址
	 * */
	void *p = realloc(ptr, len);
	if (p == NULL) {
		perror("realloc error");
		return NULL;
	}
	return p;
}

void *icl_free(void *ptr)
{
	ptr_count--;
	free(ptr);
}

int icl_check_leak()
{
	if (ptr_count == 0) {
		printf("not memory leak");
		return 0;
	}

	printf("There are %d block not free\n", ptr_count);
	return -1;
}

