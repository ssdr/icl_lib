/*
 *
 * author	: xiemin
 * file_name: icl_dns.c
 * company	: ifeng
 * date		: 2014-09-30
 *
 */

/*
 * gethostbyname 是不可重入函数，在多线程环境下会出现未知错误，可以使用gethostbyname_r代替
 */

#include <icl_net_dns.h>

struct hostent *icl_gethostbyname(char *hostname)
{
	return gethostbyname(hostname);
}

int icl_host2addr(const char *host, struct in_addr *addr, char *buff) {
    struct hostent he, *result;
    int herr, ret, bufsz = 512;
    //char *buff = NULL;
    do {
        char *new_buff = (char *)realloc(buff, bufsz);
        if (new_buff == NULL) {
            free(buff);
            return ENOMEM;
        }
        buff = new_buff;
        ret = gethostbyname_r(host, &he, buff, bufsz, &result, &herr);
        bufsz *= 2;
    } while (ret == ERANGE);

    if (ret == 0 && result != NULL)
        *addr = *(struct in_addr *)he.h_addr;
    else if (result != &he)
        ret = herr;
    //free(buff);
    return ret;
}
