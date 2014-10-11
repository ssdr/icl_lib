/*
 * client.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "icl_net_tcp_base.h"

#define handle_error(msg)	\
		do { perror(msg);exit(-1);} while(0)

int main(int argc, char *argv[]) {
	char dst[16] = "127.0.0.1";
	struct sockaddr_in addr;
	struct hostent *ip;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7744);
	int clifd = socket(AF_INET, SOCK_STREAM, PROTOCOL);

	/* 只是一个不可重入函数，详见icl_dns.c */
	ip = gethostbyname(dst);
	if (ip != NULL) {
		memcpy(&(addr.sin_addr), ip->h_addr, ip->h_length);
	} else {
		/*
		 * inet_addr可以将char *的地址转化为 int_addr_t （sockaddr可以接受的地址
		 */
		in_addr_t addr_t = inet_addr(dst);
		if (addr_t != INADDR_NONE) {
			addr.sin_addr.s_addr = addr_t;
		} else {
			printf("%s", strerror(errno));
		}
	}

	int ret = icl_connect(clifd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
	if (ret < 0) {
		handle_error("connect error");
		return -1;
	}
	printf("icl_connect ok!\n");
	char buffer[MAXLINE];
	memset(buffer, 'a', MAXLINE-1);
	buffer[MAXLINE-1] = '\0';
	ret = icl_net_send(clifd, buffer, strlen(buffer)+1);
	if (ret < 0) {
		printf("icl_net_send error\n");
		return -1;
	}
	printf("icl_net_send ok!\n");
	ret = icl_net_read(clifd, buffer, MAXLINE);
	if (ret < 0) {
		printf("icl_net_read error\n");
		return -1;
	}
	printf("icl_net_read ok!\n");
	char *p = buffer;
	int i = 0;
	while(*p != '\0') {
		//printf("i:%d, %c\n",i, *p);
		i++;p++;
	}
		
	close(clifd);
	return 0;
}

