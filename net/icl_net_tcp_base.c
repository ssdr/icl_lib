/*
 * icl_net_tcp_base.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */


#include <icl_net_tcp_base.h>

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

int icl_net_peek_read(int clifd, char *buf, int buf_len, 
			const char *peek, int peek_len)
{
	/* strict check for use input */
	char peek_def[2];
	peek_def[0] = 13; /* CR */
	peek_def[1] = 10; /* LF */
	if (peek == NULL || peek_len <= 0) {
		peek = peek_def;peek_len=2;
	}
	char *p = buf;
	int left = buf_len;	
	while (left >= 0) {
		int ret = read(clifd, p, peek_len);
		if (ret <= 0) return -1;
		if (strncmp(p, peek, peek_len) == 0) {
			printf("readbuf find terminator.\n");
			return 0;
		}
		p+=peek_len; left-=peek_len;
	}
	return -1;
}
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
			printf("icl_net_read : read return value :%d < 0 . error: %d\n", used, strerror(errno));
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
		printf("icl_cli_confd init error.");
		return (-1);
	}
	while (left > 0)
	{
		used = send(clifd, p, left, 0);
		printf("used: %d\n", used);
		if (used > 0) {
			left -= used;
			p += used;
		}
		else {
			printf("send error , error: %d", strerror(errno));
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


