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
#include <time.h>
#define handle_error(msg)	\
	do { perror(msg);exit(-1);} while(0)

int get_def_sbuf(int fd)
{
	int sock_def_buf;
	int size = sizeof(int);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (int*)&sock_def_buf, (socklen_t*)&size);
	return sock_def_buf;
}

int set_socket_tmout(int fd)
{
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
	return 0;
}

int main(int argc, char *argv[]) 
{
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
	int max_block_len =  get_def_sbuf(clifd) * 2 - 2096;
	/*
	 * 解释：max_block_len这个值很特殊。如果wirte的第三个参数大于这个值，write就会阻塞。
	 * 如果小于这个值就会立即返回写成功
	 *
	 */
	char buffer2[max_block_len];

	/* 
	 * 这里可以模拟http头信息
	 * char buffer[] = "Get: https://github.com/peterxiemin/icl_lib/edit/master/samples/net/client/client.c\r\n"
	 * 			       "User-Agent: Mozilla/5.0 (Windows NT 6.3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.65 Safari/537.36\r\n"
	 * 				   "X-Requested-With: ShockwaveFlash/15.0.0.223\r\n\r\n"
	 *
	 */


	ret = write(clifd, buffer2, max_block_len);
	if (ret <= 0) {
		printf("icl_net_send error\n");
		return -1;
	}
	printf("icl_net_send ok! ret: %d\n", ret);
	set_socket_tmout(clifd);
	printf("clifd read block.....\n");
	/*
	 * 读操作可以做各种封装，具体可以参考icl_net_tcp_base.c
	 */
	while(1) {
		ret = read(clifd, buffer2, max_block_len);
		//ret = icl_net_read(clifd, buffer2, max_block_len);
		if (ret < 0) {
			printf("icl_net_read error\n");
			return -1;
		}
		printf("ret: %d", ret);
	}
	printf("icl_net_read ok!, buffer2: %.*s\n", max_block_len, buffer2);
	printf("def_buf: %d\n", get_def_sbuf(clifd));
	close(clifd);
	return 0;
}

