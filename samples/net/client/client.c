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
#include "icl_net_tcp_base.h"



int main(int argc, char *argv[]) {
	char dst[16] = "127.0.0.1";
	struct sockaddr_in addr;
	struct hostent *ip;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	int clifd = socket(PF_INET, SOCK_STREAM, PROTOCOL);

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
		printf("connect error \n");
		return -1;
	}
	char buffer[4096];
	/* for test */
	int i;
	for (i = 0; i < 4096; i++) {
		buffer[i] = 'a';
	}
	buffer[4095] = '\0';
	ret = icl_net_send(clifd, buffer, strlen(buffer));
	if (ret < 0) {
		printf("icl_net_send error\n");
		return -1;
	}
	ret = icl_net_read(clifd, buffer, 4096);
	if (ret < 0) {
		printf("icl_net_read error\n");
		return -1;
	}
	

	close(clifd);
	return 0;
}

