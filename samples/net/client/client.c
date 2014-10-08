/*
 * client.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */



#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <icl_net_tcpdef.h>
#include "icl_net_client.h"




#define PROTOCOL 0

int icl_cli_confd = -1;


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
	/* 只是一个不可重入函数，详见icl_dns.c */
	ip =  gethostbyname(dst);
	if (ip != NULL) {
		memcpy(&(addr.sin_addr), ip->h_addr, ip->h_length);
	}
	else {
		/*
		 * inet_addr可以将char *的地址转化为 int_addr_t （sockaddr可以接受的地址
		 */
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


int main(int argc, char *argv[])
{
	return 0;
}



