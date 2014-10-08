/*
 *
 * author: xiemin
 * filename: icl_net_select.c
 * company: ifeng
 * date: 2014-09-30
 *
 *
 */

#include <icl_select.h>

/*
 * timeout 三种状态
 * NULL为永久等待, 0为从不等待, 设定时间：等待固定时间后返回
 */

int icl_select(int maxfdpl, fd_set *readset, fd_set *writeset,
				fd_set *exceptset, const struct timeval *timeout)
		{
			return select(maxfdpl, readset, writeset, exceptset, timeout);
		}
