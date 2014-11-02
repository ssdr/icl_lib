/*
 * icl_net_tcp_base.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */

#include <string.h>
#include <stdlib.h>
#include <icl_net_tcp_base.h>
#include <fcntl.h>

int icl_socket(int family, int type, int protocol)
{
	return socket(family, type, protocol);
}

int icl_connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	return connect(sockfd, servaddr, addrlen);
}

int icl_bind(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	return bind(sockfd, servaddr, addrlen);
}

int icl_listen(int sockfd, int backlog)
{
	return listen(sockfd, backlog);
}

int icl_accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	return accept(sockfd, cliaddr, addrlen);
}


/* block , 贪心算法， 有多少去多少， 直到遇到结束标志
 * 如果没有遇到结束标记，就会阻塞
 * */
int icl_net_peek_read(int clifd, char **buf, int *ret_info, const char *peek)
{
	/* strict check for usr input */
	if (peek == NULL) {
		char peek_def[2];
		/*
		 * \r\n
		 */
		peek_def[0] = 13; /* CR */
		peek_def[1] = 10; /* LF */
		peek = peek_def;
	}

	*buf =  malloc(MAXLINE);
	int size = MAXLINE;
	int left = MAXLINE;
	char p[MAXLINE + 1] ;
	int used = 0;
	do{
		memset(p, 0, MAXLINE + 1);
		int ret = read(clifd, p, MAXLINE);
		if (ret <= 0) {
			*ret_info = ret;
			return -1;
		}
		if (ret > left) {
			size *= 2;
			/* safe alloc */
			char *new_buf = realloc(*buf, size);
			if (new_buf == NULL) {
				*ret_info = -1;
				free(*buf);
				return -1;
			}
			*buf = new_buf;
			left = size - used;
		}
		memcpy(&((*buf)[used]), p, ret);
		used += ret;
		left -= ret;
	} while(strstr(p, peek) == 0);
	*ret_info = used;
	return 0;
}

/* block len是多少，就取多少，如果内核缓冲区大于len
 * 抛弃，如果不足，就会阻塞。
 * */
int icl_net_read(int clifd, char *buf, int len)
{
	int left = len;
	int used = 0;
	char *p = buf;
	// sanity check
	if (clifd < 0) {
		printf("icl_net_read: icl_cli_confd init error.\n");

		return (-1);
	}
	while (left > 0) {
		used = read(clifd, p, left);
		printf("##########[icl_net_read] read ret :%d\n", used);
		if (used > 0) {
			left -= used;
			p += used;
		}
		else if (used == 0) {
			printf("icl_net_read : connection close.\n");
			return 0;
		}
		/* used < 0 */
		else {
			/* nonblock */
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				printf("EAGAIN OR EWOULDBLOCK\n");
				continue;
			}
			printf("icl_net_read : read return value :%d < 0 . error: %s\n", used, strerror(errno));
			return -1;
		}
	}
	return 0;
}


int icl_net_send(int clifd, const char *buf, int len)
{
	int left = len;
	int used;
	const char *p = buf;
	// sanity check
	if (clifd < 0) {
		printf("icl_cli_confd init error.\n");
		return (-1);
	}
	while (left > 0)
	{
		/*
		 * the same func
		 * used = write(clifd, p, left);
		 */
		used = send(clifd, p, left, 0);
		if (used > 0) {
			left -= used;
			p += used;
		}
		else {
			printf("send error , error: %s(%d)\n", strerror(errno), errno);
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				continue;
			}
			return -1;
		}
	}
	return (0);
}

in_addr_t icl_int_addr(const char *strptr)
{
	return inet_addr(strptr);
}

int icl_inet_aton(const char *strptr, struct in_addr *addrptr)
{
	return inet_aton(strptr, addrptr);
}

char *icl_inet_ntoa(struct in_addr inaddr)
{
	return inet_ntoa(inaddr);
}


uint16_t icl_htons(uint16_t host16bitvalue)
{
	return htons(host16bitvalue);
}

int icl_getsockopt(int sockfd, int level, int optname,
		void *optval, socklen_t *optlen) {
	/* level: SOL_SOCKET
	 * optname: SO_SNDBUF SO_RCVBUF
	 * optval int *
	 */
	return getsockopt(sockfd, level, optname, optval, optlen);

}
/*
 * send 的阻塞条件，经过测试， 如果send(fd, buf, size);如果
 * size > SO_SNDBUF - 2096 ，则会出现阻塞，否则，无论对端是
 * 否接受数据，都不会阻塞， 由内核自己去处理
 */
int icl_setsockopt(int sockfd, int level, int optname,
		const void *optval, socklen_t optlen) {
	/* level: SOL_SOCKET
	 * optname: SO_SNDBUF SO_RCVBUF
	 * optval char *
	 */
	return setsockopt(sockfd, level, optname, optval, optlen);
}

int icl_setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
		return -1;
	}
	return 0;
}

int icl_set_close_exec(int fd)
{
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1) {
		return -1;
	}
	return 0;
}
