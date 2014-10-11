/*
 * icl_net_tcp_base.h
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */

#ifndef ICL_NET_TCP_BASE_H_
#define ICL_NET_TCP_BASE_H_

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/*
 * family
 */

#define MAXLINE  1024 * 1024 * 10
#define PROTOCOL 0

enum icl_socket_domain
{
	ICL_LOCAL    = PF_LOCAL,
	ICL_UNIX     = PF_INET,
	ICL_INET     = PF_INET,
	ICL_ROUTE    = PF_ROUTE,
	ICL_KEY      = PF_KEY,
	ICL_INET6    = PF_INET6,
	//ICL_SYSTEM   = PF_SYSTEM,
	//ICL_NDRV     = PF_NDRV
};

/*
 * type
 */
enum icl_socket_type
{
	ICL_STREAM    = SOCK_STREAM,
	ICL_DGRAM     = SOCK_DGRAM,
	ICL_RAW       = SOCK_RAW,
	//ICL_SEQPACKET = SOCK_DEQPACKET,
	ICL_RDM       = SOCK_RDM
};

/*
 *  protocol 此参数很少涉及，暂时默认为0
 */


int icl_socket(int family, int type, int protocol);

int icl_connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);

int icl_bind(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);

int icl_listen(int sockfd, int baklog);

int icl_accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);

int icl_net_read(int clifd, char *buffer, int len);

int icl_net_send(int clifd, const char *buffer, int len);


/*
 * 套接字地址结构
 *
 * struct in_addr {
 * 			in_addr_t s_addr;
 * 	};
 *
 * 	struct sockaddr_in {
 * 			uint8_t	sin_len;
 * 			sa_family_t	sin_family;
 * 			in_port_t	sin_port;
 * 			struct in_addr	sin_addr;
 * 			char	sin_zero[8];
 * 	};
 *
 * 	通用套接字地址结构
 *
 * 	struct sockaddr {
 * 			uint8_t	sa_len;
 * 			sa_family_t sa_family;
 * 			char sa_data[14];
 * 	};
 *
 *
 *
 */


in_addr_t icl_inet_addr(const char *strptr);

int icl_inet_aton(const char *strptr, struct in_addr *addrptr);

char *icl_inet_ntoa(struct in_addr inaddr);


uint16_t icl_htons(uint16_t host16bitvalue);

#endif /* ICL_NET_TCP_BASE_H_ */
