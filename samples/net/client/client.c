/*
 * client.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include "icl_net_client.h"

#define PROTOCOL 0

int icl_net_connect(int clifd, struct sockaddr_in *addr) {
	int ret = connect(clifd, (struct sockaddr *) &addr, sizeof(struct sockaddr));
	if (ret == 0) {
		printf("%s", strerror(errno));
	} else {
		return (-1);
	}
}

int icl_net_read(int clifd, char *buf, int len) {
	int left = len;
	int used = 0;
	char *p = buf;
	// sanity check
	if (clifd < 0) {
		printf("icl_cli_confd init error.");

		return (-1);
	}
	while (left > 0) {
		used = read(clifd, p, left);
		if (used > 0) {
			left -= used;
			p += used;
		} else if (used == 0) {
			printf("break out from server.");
			break;
		} else {
			printf("return value < 0 from read . error: %d", strerror(errno));
		}
	}
	return (0);
}

int icl_net_send(int clifd, char *buf, int len) {
	int left = len;
	int used;
	char *p = buf;
	// sanity check
	if (clifd < 0) {
		printf("icl_cli_confd init error.");
		return (-1);
	}
	while (left > 0) {
		used = send(clifd, p, left, 0);
		if (used > 0) {
			left -= used;
			p += used;
		} else {
			printf("send error , error: %d", strerror(errno));
		}
	}
	return (0);
}

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

	int ret = icl_net_connect(clifd, &addr);
	if (ret < 0) {
		printf("connect error \n");
		return -1;
	}
	char buffer[4096];
	memset(buffer, 0, 4096);
	ret = icl_net_read(clifd, buffer, 4096);
	if (ret < 0) {
		printf("icl_net_read error\n");
		return -1;
	}
	ret = icl_net_send(clifd, buffer, strlen(buffer));
	if (ret < 0) {
		printf("icl_net_send error\n");
		return -1;
	}

	close(clifd);
	return 0;
}

