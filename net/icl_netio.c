/*
 * icl_net_wrapi.c
 *
 *  Created on: 2014骞�3鏈�2鏃�
 *      Author: peterxiemin
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include "icl_wrapi.h"




//杩欓噷杩欎釜鍙傛暟鐩墠杩樻病鏈夊紕鏄庣櫧锛屾殏鏃惰缃负0锛屽悗闈㈡煡娓呮浜嗗啀琛ヤ笂
#define PROTOCOL 0

int icl_cli_confd = -1;

enum icl_socket_type 
{
	ICL_STREAM    = SOCK_STREAM,
	ICL_DGRAM     = SOCK_DGRAM,
	ICL_RAW       = SOCK_RAW,
	//ICL_SEQPACKET = SOCK_DEQPACKET,
	ICL_RDM       = SOCK_RDM
};

enum icl_socket_domain
{
	ICL_LOCAL    = PF_LOCAL,
	ICL_UNIX     = PF_INET,
	ICL_INET     = PF_INET,
	ICL_ROUTE    = PF_ROUTE,
	ICL_KEY      = PF_KEY,
	ICL_INET6    = PF_INET6,
	//ICL_SYSTEM   = PF_SYSTEM,
	//ICL_NDRV     = PF_NDRV
};


int icl_net_connect(char *dst, int port)
{
	int ret;
	struct sockaddr_in addr;
	struct hostent *ip;
	addr.sin_family = ICL_INET;
	addr.sin_port = htons(port);
	icl_cli_confd = socket(ICL_INET, ICL_STREAM, PROTOCOL);
	if (icl_cli_confd < 0) {
		printf("%s", strerror(errno));
		return (-1);
	}
	ip =  gethostbyname(dst);
	if (ip != NULL) {
		memcpy(&(addr.sin_addr), ip->h_addr, ip->h_length);	
	}
	else {
		//鍩熷悕瑙ｆ瀽澶辫触锛� 杩欓噷鐩存帴瀵筰p杩涜杞寲
		in_addr_t addr_t = inet_addr(dst);
		if (addr_t != INADDR_NONE) {
			addr.sin_addr.s_addr = addr_t;
		}
		else {
			printf("%s", strerror(errno));
		}
	}
	ret = connect (icl_cli_confd, (struct sockaddr *)&addr,  sizeof(addr));
	if (ret == 0) {
		printf("%s", strerror(errno));
	}
	else {
		return (-1);	
	}
}

int icl_net_read(char *buf, int len)
{
	int left = len;
	int used = 0;
	char *p = buf;
	// sanity check
	if (icl_cli_confd < 0) {
		printf("icl_cli_confd init error.");

		return (-1);
	}
	while (left > 0) {
		used = read(icl_cli_confd, p, left);
		if (used > 0) {
			left -= used;
			p += used;
		}
		else if (used == 0) {
			printf("break out from server.");
			break;
		}
		else {
			//杩欓儴鍒嗗鏋滄槸鍦ㄤ簨浠跺惊鐜郴缁熶腑锛岄渶瑕佺壒鍒鐞�,single 妯″潡閲岀洿鎺ラ��鍑哄氨鍙互浜�
			printf("return value < 0 from read . error: %d", strerror(errno));
		}
	}
	return (0);
}

int icl_net_send(char *buf, int len)
{
	int left = len;
	int used;
	char *p = buf;
	// sanity check
	if (icl_cli_confd < 0) {
		printf("icl_cli_confd init error.");
		return (-1);
	}
	while (left > 0)
	{
		used = send(icl_cli_confd, p, left, 0);
		if (used > 0) {
			left -= used;
			p += used;
		}
		else {
			printf("send error , error: %d", strerror(errno));
		}
	}
	return (0);
}
