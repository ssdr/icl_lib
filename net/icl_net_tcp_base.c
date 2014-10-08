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

int icl_accept(int sockfd, struct sockaddr *cliaddr, socklen_t addrlen)
{
	return accept(sockfd, cliaddr, addrlen);
}


in_addr_t icl_int_addr(const char *strptr)
{
	return icl_int_addr(strptr);
}

int icl_inet_aton(const char *strptr, struct in_addr *addrptr)
{
	return int_aton(strptr, addrptr);
}

char *icl_inet_ntoa(struct in_addr inaddr)
{
	return inet_ntoa(inaddr);
}


uint16_t icl_htons(uint16_t host16bitvalue)
{
	return htons(host16bitvalue);
}
