/*
 *  icl_mysqlapi.c
 *  icllib
 *
 *  Created by peterxm on 14-11-24.
 *  Copyright (c) 2014年 peterxm. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <icl_mysqlapi.h>

/*
 * 基础malloc等操作，这里暂不封装，如果提供线上使用，建议参考icl_lib中malloc的封装
 */

Icl_Mysql *createdb(char *host, char *sock, char *user, char *pass, char *db, unsigned int port)
{
	Icl_Mysql *icl_mysql = malloc(sizeof(Icl_Mysql));
	icl_mysql->mysql = mysql_init((MYSQL*) NULL);
	if (icl_mysql->mysql == NULL) {
		printf("mysql_init failed\n");
		return NULL;
	}
	if (sock == NULL) {
		icl_mysql->host = malloc(strlen(host)+1);
		strcpy(icl_mysql->host, host);
		icl_mysql->port = port;
	}
	else {
		icl_mysql->host = NULL;
		icl_mysql->port = 0;
		icl_mysql->sock = malloc(strlen(sock)+1);
		strcpy(icl_mysql->sock, sock);
	}

	icl_mysql->user = malloc(strlen(user) + 1);
	strcpy(icl_mysql->user, user);
	icl_mysql->pass = malloc(strlen(pass) + 1);
	strcpy(icl_mysql->pass, pass);
	icl_mysql->db = malloc(strlen(db) + 1);
	strcpy(icl_mysql->db, db);
	icl_mysql->nqbuf = 0;
}

void *icl_freedb(Icl_Mysql *icl_mysql) {
	mysql_close(icl_mysql->mysql);
	if (icl_mysql->host != NULL) {
		free(icl_mysql->host);
	}
	free(icl_mysql->user);
	free(icl_mysql->pass);
	free(icl_mysql->db);
	free(icl_mysql);
}


void icl_opendb(Icl_Mysql *icl_mysql)
{
	MYSQL *ret = mysql_real_connect(icl_mysql->mysql,
					icl_mysql->host,
					icl_mysql->user,
					icl_mysql->pass,
					icl_mysql->db,
					icl_mysql->port,
					NULL, 0);
	if (ret == NULL) {
		icl_errordb(icl_mysql);	
	}
	mysql_real_query(icl_mysql->mysql, "SET CHARACTER SET gb2312", 24);
}

void icl_reopendb(Icl_Mysql *icl_mysql)
{
	free(icl_mysql->mysql);
	icl_mysql->mysql = mysql_init((MYSQL *) NULL);
	MYSQL *ret = mysql_real_connect(icl_mysql->mysql,
					icl_mysql->host,
					icl_mysql->user,
					icl_mysql->pass,
					icl_mysql->db,
					icl_mysql->port,
					NULL, 0);
	if (ret == NULL) {
		icl_errordb(icl_mysql);	
	}
	mysql_real_query(icl_mysql->mysql, "SET CHARACTER SET gb2312", 24);
}


void icl_qpushdb(Icl_Mysql *icl_mysql) 
{
	int i = 0;
	while (i < icl_mysql->nqbuf) {
		int n = 9;
		while (n) {
			int ret = mysql_real_query(icl_mysql->mysql, icl_mysql->qbuf[i], icl_mysql->qlen[i]);
			if (ret) {
				/* 这块逻辑需要在确认一下 */
				int err = mysql_errno(icl_mysql->mysql);
				if (err == CR_SERVER_LOST || err == CR_SERVER_GONE_ERROR || err == CR_CONN_HOST_ERROR ) {
					printf("(%d)%s\n", mysql_errno(icl_mysql->mysql), mysql_error(icl_mysql->mysql));
					printf("reopen mysql handler....");
					sleep((10-n) * 5);
					icl_reopendb(icl_mysql);
					n--;
				}
				else {
					printf("query failed , query : %s\n", icl_mysql->qbuf[i]);
					icl_errordb(icl_mysql);
					break;
				}
			}
			else {
				/* success */
				break;
			}
		}
		free(icl_mysql->qbuf[i]);
		i++;
	}
	icl_mysql->nqbuf = 0;
}

/* select 操作,flag ：1可以马上执行，并且返回结果，如果是insert等操作，可以使用缓存，到达MAXBUFNUM后，一次性插入*/
int icl_querydb(Icl_Mysql *icl_mysql, int flag, char *query, unsigned int len)
{
	int n = 9;
	/* 这是一个很重要的标志, 可以根据nqbuf这个条件添加icl_qmodedb设置是否使用缓存 */
	if (flag == 0 && icl_mysql->nqbuf >= 0 ) {
		icl_mysql->qbuf[icl_mysql->nqbuf] = malloc(len+1);
		memcpy(icl_mysql->qbuf[icl_mysql->nqbuf], query, len);
		icl_mysql->qbuf[icl_mysql->nqbuf][len] = '\0';
		icl_mysql->qlen[icl_mysql->nqbuf] = len;
		icl_mysql->nqbuf++;
		if (icl_mysql->nqbuf == MAXSQLNUM) {
			icl_qpushdb(icl_mysql);		
		}
		return 0;
	}

	while (n) {
		int ret = mysql_real_query(icl_mysql->mysql, query, len);
		if (ret) {
			/* 这块逻辑需要在确认一下 */
			int err = mysql_errno(icl_mysql->mysql);
			if (err == CR_SERVER_LOST || err == CR_SERVER_GONE_ERROR || err == CR_CONN_HOST_ERROR ) {
				printf("(%d)%s\n", mysql_errno(icl_mysql->mysql), mysql_error(icl_mysql->mysql));
				printf("reopen mysql handler....");
				sleep((10-n) * 5);
				icl_reopendb(icl_mysql);
				n--;
			}
			else {
				printf("query failed , query : %s\n", query);
				icl_errordb(icl_mysql);
				return -1;
			}
		}
		else {
			/* success */
			return 0;
		}
	}
	return -1;
}

void icl_errordb(Icl_Mysql *icl_mysql)
{
	printf("host: %s\n", icl_mysql->host);
	printf("user: %s\n", icl_mysql->user);
	printf("pass: XXXXXXXX\n", icl_mysql->pass);
	printf("database: %s\n", icl_mysql->db);
	printf("port: %d\n", icl_mysql->port);
	printf("error: (%d) %s\n", mysql_errno(icl_mysql->mysql), mysql_error(icl_mysql->mysql));
}


/* 用完后使用mysql_free_result()释放res
 * 调用mysql_fetch_row()从结果集合中取出行
 * mysql_row_seek()从结果集合中获得当前的行位置。
 * mysql_row_tell()在设置当前的行位置。
 *          */
MYSQL_RES *icl_mysql_store_result(Icl_Mysql *icl_mysql)
{
	MYSQL_RES *res;
	res=mysql_store_result(icl_mysql->mysql);
	if( mysql_field_count(icl_mysql->mysql) && res==NULL  ) icl_errordb(icl_mysql);
	return(res);
}
