/*
 * wyf_array.c
 *
 *  Created on: 2014年1月23日
 *      Author: peterxiemin
 */


//#include "wyf_array.h"
//
//WYF_ARRAY* wyf_array_init(int n, int typsz)
//{
//	/*
//	 * 这里对内存管理还没有做， 暂时先用malloc吧
//	 */
//	WYF_ARRAY *p;
//	p = (WYF_ARRAY*) malloc (sizeof(WYF_ARRAY));
//	if (p == NULL)
//	{
//		return NULL;
//	}
//	p->typsz = typsz;
//	p->size = typsz * n;
//	p->begin = malloc (p->size);
//	if (p->begin == NULL)
//	{
//		return NULL;
//	}
//	p->nelts = 0;
//	return p;
//}
//
//void* wyf_array_push(WYF_ARRAY *a)
//{
//	if ( a == NULL )
//		return NULL;
//	/*
//	 * 已经满了， 需要扩容
//	 */
//	if ( a->nelts*a->typsz >= a->size )
//	{
//		void *new = realloc(a->begin ,a->size * 2);
//		if (new == NULL)
//		{
//			return NULL;
//		}
//		a->begin = new;
//		a->size *= 2;
//	}
//	void *elts = a->begin + a->nelts * a->typsz;
//	a->nelts ++;
//	return elts;
//}
//
//void wyf_array_destroy(WYF_ARRAY *a)
//{
//	if (a == NULL)
//	{
//		return;
//	}
//	/* 这里也应该加入内存管理机制 */
//	free(a->begin);
//	free(a);
//}