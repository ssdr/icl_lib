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

#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>

/*
void ICL_FD_ZERO(fd_set *fdset);
void ICL_FD_SET(int fd, fd_set *fdset);
void ICL_FD_CLR(int fd, fd_set *fdset);
int ICL_FD_ISSET(int fd, fd_set *fdset);
*/

#define ICL_FD_ZERO 	FD_ZERO
#define ICL_FD_SET 		FD_SET
#define ICL_FD_CLR 		FD_CLR
#define ICL_FD_ISSET 	FD_ISSET

/*
 * struct timeval {
 * 		long tv_sec;
 * 		long tv_usec;
 * 	}
 */

int icl_select(int maxfdpl, fd_set *readset, fd_set *writeset, fd_set *exceptset,
					struct timeval *timeout);

#endif /*ICL_NET_SELECT_H*/



