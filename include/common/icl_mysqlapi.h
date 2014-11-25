/*
 *  icl_mysqlapi.h
 *  icllib
 *
 *  Created by peterxm on 14-11-23.
 *  Copyright (c) 2014年 peterxm. All rights reserved.
 */

#ifndef ICL_MYSQLAPI_H_
#define ICL_MYSQLAPI_H_

#include <mysql.h>
#include <errmsg.h>
#define MAXSQLNUM 2048

typedef struct icl_mysql {
	MYSQL *mysql;
	char *host;
	char *user;
	char *pass;
	char *db;
	unsigned int port;
	char *sock;
	unsigned int nqbuf;
	char *qbuf[MAXSQLNUM];
	unsigned int qlen[MAXSQLNUM];
} Icl_Mysql;

Icl_Mysql *icl_createdb(char *host, char *socket, char *user, char *pass, char *db, unsigned int port);
void *icl_freedb(Icl_Mysql *icl_mysql);
void icl_opendb(Icl_Mysql *icl_mysql);
void icl_reopendb(Icl_Mysql *icl_mysql);
void icl_qpushdb(Icl_Mysql *icl_mysql);
int icl_querydb(Icl_Mysql *icl_mysql, int flag, char *query, unsigned int len);
void icl_errordb(Icl_Mysql *icl_mysql);
MYSQL_RES *icl_mysql_store_result(Icl_Mysql *icl_mysql);

#endif /* ICL_MYSQLAPI_H_ */

