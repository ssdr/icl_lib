#include <stdio.h>
#include <stdlib.h>
#include <event.h>
#include <string.h>
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>    
#include <netdb.h>
#include <icl_net_tcp_base.h>

struct event_base *base;

#define handle_error(x) \
	do { perror(x); exit(-1); } while (0);


int event_close(int fd, void *arg)
{
	printf("Client Close\n");

	// 连接结束(=0)或连接错误(<0)，将事件删除并释放内存空间
	struct event *ev = (struct event*)arg;
	event_del(ev);
	free(ev);

	close(fd);
	return 0;
}

// 读事件回调函数
void onRead(int clifd, short ievent, void *arg)
{
	char buf[MAXLINE];
	int ret = read(clifd, buf, MAXLINE);
	if (ret <= 0) {
		event_close(clifd, arg);
		return;
	}
	else{
		ret = icl_net_send(clifd, buf, ret);
		if (ret < 0) {
			printf("write error \n");
		}
		else {
			printf("write ok \n");
		}
		event_close(clifd, arg);
	}
	return;
}


// 连接请求事件回调函数
void onAccept(int servfd,  short ievent, void *arg)
{
	struct sockaddr_in cliaddr;

	socklen_t size = sizeof(cliaddr);
	int clifd = accept(servfd, (struct sockaddr*)&cliaddr, &size);

	// 连接注册为新事件 (EV_PERSIST为事件触发后不默认删除)
	struct event *ev = (struct event *) malloc(sizeof(struct event));
	event_set(ev, clifd, EV_READ|EV_PERSIST, onRead, ev);
	event_base_set(base, ev);
	event_add(ev, NULL);
}


int main(int argc, char *argv[])
{
	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr, cliaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7744);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(servaddr.sin_zero),8);
	int ret = bind(servfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	if (ret < 0) {
		handle_error("bind error port 7744:");
		return -1;
	}
	ret = listen(servfd, 1024);
	if (ret < 0) {
		printf("listen error\n");
		return -1;
	}
	// 初始化base
	base = event_base_new();

	struct event evListen;
	// 设置事件
	event_set(&evListen, servfd, EV_READ|EV_PERSIST, onAccept, NULL);
	// 设置为base事件
	event_base_set(base, &evListen);
	// 添加事件
	event_add(&evListen, NULL);

	// 事件循环
	event_base_dispatch(base);	
	return 0;
}
