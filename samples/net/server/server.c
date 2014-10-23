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

	char *buffer;
	int buffer_size;
	while (1) {
		int sock_len = sizeof(struct sockaddr);
		int clifd = accept(servfd, (struct sockaddr *)&cliaddr, (socklen_t *)&sock_len);
		if (clifd == -1) {
			handle_error("accept error");
		}
		printf("accept ok!\n");
		int ret = icl_net_peek_read(clifd, buffer, &buffer_size, NULL);
		if (ret < 0) {
			handle_error("read error");
		}
		buffer[buffer_size] = 0;
		printf("%s\n", buffer);
		free(buffer);
		//printf("icl_net_read ok!\n");
		//ret = icl_net_send(clifd, buffer, strlen(buffer)+1);
		//if (ret < 0) {
		//	handle_error("send error");
		//}
		//printf("icl_net_send ok!\n");
		close(clifd);
	}

	return 0;
}


