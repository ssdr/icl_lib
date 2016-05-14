/*
 *
 * author: xiemin
 * file_name: icl_dns.h
 * company: ifeng
 * date: 2014-09-30
 *
 */



#ifndef ICL_DNS_H_
#define ICL_DNS_H_

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>

struct hostent *icl_gethostbyname(char *hostname);

int icl_host2addr(const char *host, struct in_addr *addr, char *buff);

#endif /*ICL_DNS_H_*/
