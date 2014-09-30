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


struct hostent *icl_gethostbyname(char *hostname);

struct hostent *icl_gethostbyname_r(char *hostname);

#endif /*ICL_DNS_H_*/
