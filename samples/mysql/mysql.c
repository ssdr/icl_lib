#include <stdio.h>
#include <string.h>
#include <mysql.h>


int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int flag, t;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "6748355", "spytest", 0, NULL, 0)) {
		printf("Failed to connect to Mysql!\n");
		return -1;
	}else {
		printf("Connected to Mysql successfully!\n");
	}
	char query[] = "select * from log";
	/*查询，成功则返回0*/
	flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
	if(flag) {
		printf("Query failed!\n");
		return -1;
	}else {
		printf("[%s] made...\n", query);
	}

	/////////////////////////////////////////////////////////////////query
	/*mysql_store_result讲全部的查询结果读取到客户端*/
	res = mysql_store_result(&mysql);
	/*mysql_fetch_row检索结果集的下一行*/
	while(row = mysql_fetch_row(res)) {
		/*mysql_num_fields返回结果集中的字段数目*/
		for(t=0; t<mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
	}
	/////////////////////////////////////////////////////////////////insert
	char insert[] = "insert into log(title, keyword, content) values('sleep', 'rest', 'I have a dream')";
	/*插入，成功则返回0*/
	flag = mysql_real_query(&mysql, insert, (unsigned int)strlen(insert));
	if(flag) {
		printf("Insert data failure!\n");
		return -1;
	}else {
		printf("Insert data success!\n");
	}
	/////////////////////////////////////////////////////////////////del
	char delete[] = "delete from log where log_id=3";
	/*删除，成功则返回0*/
	flag = mysql_real_query(&mysql, delete, (unsigned int)strlen(delete));
	if(flag) {
		printf("Delete data failure!\n");
		return -1;
	}else {
		printf("Delete data success!\n");
	}
	mysql_close(&mysql);
	return 0;
}
