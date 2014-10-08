/*
 *
 * author: xiemin
 * filename: icl_net_select.h
 * company: ifeng
 * date: 2014-09-30
 *
 *
 */


#ifndef ICL_NET_SELECT_H
#define ICL_NET_SELECT_H


#include <sys/select.h>
#include <sys/time.h>

void ICL_FD_ZERO(fd_set *fdset);
void ICL_FD_SET(int fd, fd_set *fdset);
void ICL_FD_CLR(int fd, fd_set *fdset);
int ICL_FD_ISSET(int fd, fd_set *fdset);


/*
 * struct timeval {
 * 		long tv_sec;
 * 		long tv_usec;
 * 	}
 */

int icl_select(int maxfdpl, fd_set *readset, fd_set *writeset, fd_set *exceptset,
					const struct timeval *timeout);

#endif /*ICL_NET_SELECT_H*/



