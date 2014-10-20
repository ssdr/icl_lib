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
	do { perror(msg);exit(-1);} while (0)

int main(int argc, char *argv[])
{

	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr, cliaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7744);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(servaddr.sin_zero),8);


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

	char rbuffer[MAXLINE];
	memset(rbuffer, 0,  MAXLINE);
	/* select */
	int client[FD_SETSIZE];
	memset(client, -1, FD_SETSIZE);
	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(servfd, &rset);
	int maxfdpl = servfd;
	int i;
	for (;;) {
		int nready = select(maxfdpl + 1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(servfd, &rset)) {
			int sock_len = sizeof(struct sockaddr);
			printf("accept ok!\n");
			int clifd = accept(servfd, (struct sockaddr *)&cliaddr, (socklen_t *)&sock_len);
			if (clifd == -1) {
				handle_error("accept error");
			}
			for (i; i < FD_SETSIZE; i++) {
				if (client[i] < 0) {
					client[i] = clifd;
					break;
				}
			}
			if (i == FD_SETSIZE) {
				printf("too many clifd");
				return -1;
			}
			FD_SET(clifd, &rset);
			if (clifd > maxfdpl) {
				maxfdpl = clifd;
			}
			/* 优先处理 accept */
			if (--nready <= 0) {
				continue;
			}
		}

		for (i=0; i < FD_SETSIZE; i++) {
			if (client[i] < 0) {
				continue;
			}
			if (FD_ISSET(client[i], &rset)) {
				int n = icl_net_read(client[i], rbuffer, MAXLINE);
				if (n == 0) {
					close(client[i]);
					FD_CLR(client[i], &rset);
					client[i] = -1;
				}
				printf("read ok!\n");
				else {
					int n = icl_net_send(client[i], rbuffer, n);
					printf("send ok!\n");
				}
				if (--nready <= 0)
					break;
			}
		}
	}
	return 0;
}


