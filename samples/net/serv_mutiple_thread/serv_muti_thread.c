/*
 * server.c
 *
 *  Created on: 2014年10月8日
 *      Author: peterxiemin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <icl_net_tcp_base.h>
#include <icl_http_parser.h>

#define handle_error(msg) \
	do { perror(msg);exit(-1);} while (0)

struct thread_info {
	pthread_t thread_id;
	int servfd;
	int thread_num;
};
typedef struct thread_info thread_info;

void prt_def_sbuf(int fd)
{
	int sock_def_buf;
	int size = sizeof(int);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (int*)&sock_def_buf, (socklen_t*)&size);
	//printf("send core buffer :%d\n", sock_def_buf);
}

void prt_def_rbuf(int fd)
{
	int sock_def_buf;
	int size = sizeof(int);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, (int*)&sock_def_buf, (socklen_t*)&size);
	//printf("send core buffer :%d\n", sock_def_buf);
}

int on_body(http_parser *_, const char *at, size_t len)
{
	(void)_;
	//printf("%.*s\n", (int)len, at);
	return 0;
}

int on_message_begin(http_parser *_)
{
	(void)_;
	//printf("MESSAGE BEGIN\n");
	return 0;
}

int icl_http_parse(void *data, int len)
{
	char *p = (char *)data;
	http_parser_settings settings;
	memset(&settings, 0, sizeof(settings));
	settings.on_message_begin = NULL;
	settings.on_url = NULL;
	settings.on_header_field = NULL;
	settings.on_header_value = NULL;
	settings.on_headers_complete = NULL;
	settings.on_body = NULL;
	settings.on_message_complete = NULL;

	http_parser parser;
	http_parser_init(&parser, len);
	size_t nparsed = http_parser_execute(&parser, &settings, data, len);

	if (nparsed != (size_t)len) {
		fprintf(stderr, "Error: %s (%s)\n", http_errno_name(HTTP_PARSER_ERRNO(&parser)));
		goto fail;
	}

	return 0;

fail:
	return -1;
}


static void * thread_start(void *arg)
{
	thread_info *tinfo = (thread_info *) arg;
	int servfd = tinfo->servfd;
	int ret = thread_process(servfd);
	if (ret < 0) {
		//printf("thread_process error\n");
	}
	return (void *)0;
}

int thread_process(int servfd)
{
	struct sockaddr cliaddr;
	char *buffer = NULL;
	int buffer_size = 0;
	while (1) {
		int sock_len = sizeof(struct sockaddr);
		int clifd = accept(servfd, (struct sockaddr *)&cliaddr, (socklen_t *)&sock_len);
		if (clifd == -1) {
			handle_error("accept error");
		}
		//printf("accept ok!\n");
		int ret = icl_net_peek_read(clifd, &buffer, &buffer_size, NULL);
		if (ret < 0) {
			if (buffer_size == 0) {
				//printf("peer read error for connection close\n");
			}
			if (buffer_size < 0) {
				//printf("peek read error,(%d)(%s) \n", errno, strerror(errno));
			}
			close(clifd);
			continue;
		}

		if (icl_http_parse(buffer, buffer_size) < 0) {
			char rsp[] = "not vaild http 协议";
			//printf(buffer, strlen(rsp) + 1, "%s", rsp);
			buffer_size = strlen(rsp) + 1;
			//printf("http parse error\n");
		}
		else {
			//printf("http parse success\n");
		}

		ret = icl_net_send(clifd, buffer, buffer_size);
		if (ret == 0)
			//printf("write error\n");
		if (ret < 0)
			//printf("client close \n");
		if (buffer != NULL)
		{
			//printf("%ld\n", (long int)buffer);
			free(buffer);
		}
		close(clifd);
	}
	return 0;
}



	
int main(int argc, char *argv[])
{

	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7744);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	int t_num = 0;
	char ch;

	while((ch = getopt(argc, argv, "t:")) > 0) {
		switch (ch) {
			case 't':
				t_num = atoi(optarg);
				break;
			default:
				//printf("args error\n");
				return -1;
		}
	}

	pthread_attr_t attr;
	void *res;
	int ret = pthread_attr_init(&attr);
	if (ret != 0) {
		//printf("pthread_attr_init error (%d)(%s) \n",errno, strerror(errno));
		return -1;
	}
	
	
	bzero(&(servaddr.sin_zero),8);
	ret = bind(servfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	if (ret < 0) {
		handle_error("bind error port 7744:");
		return -1;
	}
	ret = listen(servfd, 1024);
	if (ret < 0) {
		//printf("listen error\n");
		return -1;
	}
	
	thread_info *tinfo =  calloc(t_num, sizeof(thread_info));
	int i;
	for (i = 0; i < t_num; i++) {
		tinfo[i].thread_num = i;
		tinfo[i].servfd = servfd;
		pthread_create(&tinfo[i], &attr, &thread_start, &tinfo[i]);
	}
	
	ret = pthread_attr_destroy(&attr);
	if (ret != 0) {
		//printf("pthread_attr_init error (%d)(%s) \n",errno, strerror(errno));
		return -1;
	}
	
	for (i = 0; i < t_num; i++) {
		ret = pthread_join(tinfo[i].thread_id, &res);
		if (ret != 0) {
			//printf("pthread_attr_init error (%d)(%s) \n",errno, strerror(errno));
			return -1;
		}
		//printf("thread %d return value %s\n", tinfo[i].thread_id, (char *)res);
		free(res);
	}
	free(tinfo);
	return 0;
}
