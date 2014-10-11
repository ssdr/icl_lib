/*
 * server.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <icl_net_tcp_base.h>

#define handle_error(msg) \
	           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{

	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr, cliaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = 7744;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	int ret = bind(servfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	if (ret < 0) {
		handle_error("bind error port 7744:");
		return -1;
	}
	ret = listen(servfd, 1024);
	if (ret < 0) {
		printf("listen error\n");
		return -1;
	}

	char buffer[4096];
	memset(buffer, 0,  4096);
	while (1) {
		int clifd = accept(servfd, (struct sockaddr *)&cliaddr, (socklen_t *)sizeof(struct sockaddr));
		if (clifd == -1) {
			printf("accept error\n");
			return -1;
		}
		int ret = icl_net_read(clifd, buffer, 4096);
		if (ret < 0) {
			printf("read error\n");
		}
		ret = icl_net_send(clifd, buffer, strlen(buffer));
		if (ret < 0) {
			printf("send error\n");
		}
		close(clifd);
	}

	return 0;
}


