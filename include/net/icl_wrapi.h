/*
 * icl_net_wrapi.h
 *
 *  Created on: 2014年4月11日
 *      Author: peterxiemin
 */

#ifndef ICL_NET_WRAPI_H_
#define ICL_NET_WRAPI_H_

#include <stdio.h>

int icl_net_connect(char *dst, int port);

int icl_net_read(int sockfd, char *buf, int len);

int icl_net_send(int sockfd, char *buf, int len);


#endif /* ICL_NET_WRAPI_H_ */
