/*
 *
 * author: xiemin
 * file_name: icl_dns.c
 * company: ifeng
 * date: 2014-09-30
 *
 */

/*
 * gethostbyname 是不可重入函数，在多线程环境下会出现位置错误，可以使用gethostbyname_r代替
 */

#include <icl_net_dns.h>

struct hostent *icl_gethostbyname(char *hostname)
{
	return gethostbyname(hostname);
}


struct hostent *icl_gethostbyname_r(char *hostname)
{
	char    buf[1024];
	struct  hostent  *hostinfo, *phost;
	int     ret;

	/* 这块内存需要自己释放，否则会存在内存泄露 */
	hostinfo = malloc(sizeof(struct hostent));

	if(gethostbyname_r(hostname, hostinfo, buf, sizeof(buf), &phost, &ret)) {
		printf("ERROR:gethostbyname(%s) ret:%d", hostname, ret);
		return NULL;
	}
	else {
		int i;
		printf("gethostbyname(%s) success:ret:%d,", hostname , ret);
		if(phost) {
			printf("name:%s,addrtype:%d(AF_INET:%d),len:%d",
					phost->h_name,phost->h_addrtype,AF_INET,
					phost->h_length);
		}
		for(i = 0;hostinfo->h_aliases[i];i++) {
			//printf("hostinfo alias is:%s\n",hostinfo->h_aliases[i]);
			;;
		}
		for(i = 0;hostinfo->h_addr_list[i];i++) {
			//printf("host addr is:%s\n",inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[i]));
			;;
		}
	}
	return hostinfo;
}

