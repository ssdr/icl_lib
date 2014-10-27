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
	char buffer[MAXLINE/2];
	memset(buffer, 'a', MAXLINE/2-3);
	buffer[MAXLINE/2-1] = 0;
	buffer[MAXLINE/2-2] = 10;
	buffer[MAXLINE/2-3] = 13;
	buffer[MAXLINE/2-3] = 13;
	//ret = write(clifd, buffer, strlen(buffer));
	char *p = malloc(1024*1024*10);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (int*)&send_buf, 
	ret = send(clifd, p, 1, 0);
	if (ret < 0) {
		printf("icl_net_send error\n");
		return -1;
	}
	printf("icl_net_send ok! ret: %d\n", ret);
	memset(buffer, 0, MAXLINE/2);
	ret = icl_net_read(clifd, buffer, MAXLINE/2-1);
	if (ret < 0) {
		printf("icl_net_read error\n");
		return -1;
	}
	printf("icl_net_read ok, buffer: %s\n", buffer);
	close(clifd);
	return 0;
}

