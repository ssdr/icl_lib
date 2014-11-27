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
	fd_set rset, allset;
	FD_ZERO(&allset);
	FD_SET(servfd, &allset);
	int maxfdpl = servfd+1200;
	int i;
	for (;;) {
		/* 
		 * rset和allset必须区分开，一个做读操作(rset)，一个做写操作(allset) 
		 * 否则FD_SET会修改allset的信息，导致读写时间丢失
		 * */
		rset = allset;
		int nready = select(maxfdpl + 1, &rset, NULL, NULL, NULL);
		if (nready == -1) {
			/* 单个进程的文件描述符必须在1024以内，否则select返回-1， errno为9（bad file....) */
			printf("select error (%d)%s\n", errno, strerror(errno));
			return -1;
		}
		if (FD_ISSET(servfd, &rset)) {
			int sock_len = sizeof(struct sockaddr);
			printf("accept ok!\n");
			int clifd = accept(servfd, (struct sockaddr *)&cliaddr, (socklen_t *)&sock_len);
			if (clifd == -1) {
				handle_error("accept error\n");
			}
			for (i=0; i < FD_SETSIZE; i++) {
				if (client[i] < 0) {
					client[i] = clifd;
					break;
				}
			}
			if (i == FD_SETSIZE) {
				printf("too many clifd\n");
				return -1;
			}
			FD_SET(clifd, &allset);
			if (clifd > maxfdpl) {
				maxfdpl = clifd;
			}
			/* 提高效率，不做无用功 */
			if (--nready <= 0) {
				continue;
			}
		}

		for (i=0; i < FD_SETSIZE; i++) {
			if (client[i] < 0) {
				continue;
			}
			if (FD_ISSET(client[i], &rset)) {
				//int n = icl_net_read(client[i], rbuffer, MAXLINE);
				/* 
				 * 如果read配合select，那就是贪心算法，有多少取多少，不需要阻塞的问题
				 */
				int n = read(client[i], rbuffer, MAXLINE);
				//int n = recv(client[i], rbuffer, MAXLINE, 0);
				//int n = icl_net_peek_read(client[i], rbuffer, MAXLINE, NULL, 0);
				if (n <= 0) {
					close(client[i]);
					FD_CLR(client[i], &allset);
					client[i] = -1;
					printf("cli(%d) closed \n", client[i]);
				}
				else {
					rbuffer[n] = 0;
					//int n = icl_net_send(client[i], rbuffer, n);
					//icl_net_send(client[i], rbuffer, n);
					write(client[i], rbuffer, n);
					printf("send ok!\n");
				}
				if (--nready <= 0)
					break;
			}
		}
	}
	return 0;
}


