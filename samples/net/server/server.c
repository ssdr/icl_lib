/*
 * server.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */

#include <stdio.h>


int icl_net_read(int clifd, char *buf, int len)
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
		used = read(clifd, p, left);
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

int icl_net_send(int clifd, const char *buf, int len)
{
	int left = len;
	int used;
	char *p = buf;
	// sanity check
	if (clifd < 0) {
		printf("icl_cli_confd init error.");
		return (-1);
	}
	while (left > 0)
	{
		used = send(clifd, p, left, 0);
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

	int servfd = socket(SOCK_STREAM, PF_INET, 0);
	sockaddr_in servaddr, cliaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(addr.sin_zero),8);
	int ret = bind(servfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	if (ret <　0) {
		printf("bind error : port 8080\n");
		return -1;
	}
	ret = listen(servfd, 1024);
	if (ret <　0) {
		printf("listen error\n");
		return -1;
	}

	int buffer[4096];
	memset(buffer, 0,  4096);
	while (1) {
		int clifd = accept(servfd, (struct sockaddr *)&cliaddr, sizeof(struct sockaddr));
		if (clifd == -1) {
			printf("accept error\n");
			return -1;
		}
		int ret = icl_net_read(clifd, buffer, 4096);
		if (ret < 0) {
			printf("read error\n");
		}
		int ret = icl_net_send(clifd, buffer, strlen(buffer));
		if (ret < 0) {
			printf("send error\n");
		}
		close(clifd);
	}

	return 0;
}


