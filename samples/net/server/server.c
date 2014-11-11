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
#include <icl_http_parser.h>

#define handle_error(msg) \
	           do { perror(msg);exit(-1);} while (0)


void prt_def_sbuf(int fd)
{
	int sock_def_buf;
	int size = sizeof(int);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (int*)&sock_def_buf, (socklen_t*)&size);
	printf("send core buffer :%d\n", sock_def_buf);
}

void prt_def_rbuf(int fd)
{
	int sock_def_buf;
	int size = sizeof(int);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, (int*)&sock_def_buf, (socklen_t*)&size);
	printf("send core buffer :%d\n", sock_def_buf);
}

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

	int buffer_size = 1024;
	
	char buffer[buffer_size];
	while (1) {
		int sock_len = sizeof(struct sockaddr);
		int clifd = accept(servfd, (struct sockaddr *)&cliaddr, (socklen_t *)&sock_len);
		
		printf("clifd:%d\n", clifd);
		if (clifd == -1) {
			perror("accept error");
			continue;
		}
		printf("accept ok!\n");
		//int ret = icl_net_peek_read(clifd, &buffer, &buffer_size, NULL);
		int ret = read(clifd, buffer, buffer_size);
		if (ret < 0) {
			handle_error("read error");
		}

		printf("read ok, buffer: %s\n", buffer);
		ret = write(clifd, buffer, buffer_size);
		if (ret <= 0) {
			printf("write error\n");
			return -1;
		}
		printf("write ok\n");
		//printf("icl_net_read ok!\n");
		//ret = icl_net_send(clifd, buffer, strlen(buffer)+1);
		//if (ret < 0) {
		//	handle_error("send error");
		//}
		//printf("icl_net_send ok!\n");
		//close(clifd);
	}

	return 0;
}


