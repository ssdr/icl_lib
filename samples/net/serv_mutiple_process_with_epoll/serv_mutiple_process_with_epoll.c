#include <stdio.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <icl_htable.h>
#include <icl_net_tcp_base.h>


#define MAX_EVENTS 10

#define handle_error(msg) \
	do { perror(msg);exit(-1);} while (0)


static Icl_Htable *iht = NULL;
/*
 * setnonblocking - 设置句柄为非阻塞方式
 * */
int setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
		return -1;
	}
	return 0;
}

void printf_wtpid(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char buf[128];
	int len = snprintf(buf, 128, "[%d]\t", getpid());
	vsprintf(&buf[len], fmt, args);
	printf("%s", buf);
	va_end(args);
}

void usage()
{
	printf_wtpid("./a -t 3\n");
}

/*
 * epoll在多进程模型下
 * 1、每个进程共享epollfd,则会出现read失败，返回（9）
 * Bad file descriptor. 
 * (1)通过测试，开了两个进程，共享epollfd。 work1正常
 * epoll_wiat返回， 然后accept, 之后再epoll_wait, 继而read、write。 
 * work2居然epoll_wait返回后， 直接出发读写事件,此时，这个文件描述符可能
 * 根本没有加入到此进程的epoll中，就会出现(9) Bad file descriptor。(已经
 * 测试验证) 
 * (2)如果这个文件描述符加入已经加入到epoll中，那么这个是否有数据可读，或者读出
 * 的数据是否是本进程的数据，就不好判断了（测试环境不容易搭建)
 *
 * 2、如果不共享，而是每个进程各自独有epollfd,则不会
 * 出现问题，目前还不清楚原因，需要结合epoll内部机制分析。libevent也遇
 * 到类似情况，需要在fork后， 对event_base，调用event_reinit，才能保证
 * 程序运行正常。
 */
int epoll_base_init(int listen_sock, int *epollfd)
{
	struct epoll_event ev;
	*epollfd = epoll_create(10);
	if (*epollfd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if (epoll_ctl(*epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}
}


int parent_process(int pnum, pid_t pids[])
{
	int i;
	for (i = 0; i < pnum; i++) {
		int ret = waitpid(pids[i], NULL, 0);
		if (ret < 0) {
			printf_wtpid("waitpid error pid:%d\n", pids[i]);
		}
	}
	return 0;
}

int child_process(int epollfd, int listen_sock, struct epoll_event events[])
{
	int ret = epoll_dispatch(epollfd, listen_sock, events);
	return ret;
}
/*
 * 这里使用了icl_htable这个map容器，这里封装，主要为了
 * 使他能够检查fd，之前是否注册过。
 */
int htable_push(Icl_Htable *iht, int fd)
{
	char key[8];
	char value[16];
	snprintf(key, 8, "%d", fd);
	snprintf(value, 16, "%d_%d", fd, getpid());
	int ret = icl_htable_set(iht, key, value);
	if (ret < 0) {
		printf_wtpid("icl_htable_set error\n");
		return -1;
	}
	return 0;
}

int htable_pop(Icl_Htable *iht, int fd)
{
	char key[8];
	char value[16];
	snprintf(key, 8, "%d", fd);
	int ret = icl_htable_get(iht, key, value, 16);
	if (ret < 0) {
		printf_wtpid("[htable_pop] icl_htable_get error\n");
		return -1;
	}
	return 0;

}

int htable_remove(Icl_Htable *iht, int fd)
{
	char key[8];
	snprintf(key, 8, "%d", fd);
	int ret = icl_htable_del(iht, key);
	if (ret < 0) {
		printf_wtpid("icl_htable_del error\n");
		return -1;
	}
	return 0;
}

int epoll_dispatch(int epollfd, int listen_sock, struct epoll_event events[])
{
	int nfds = 0, n, conn_sock;
	struct epoll_event ev;
	struct sockaddr_in local;

	for (;;) {
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_pwait");
			exit(EXIT_FAILURE);
		}

		for (n = 0; n < nfds; ++n) {
			//printf("nfds: %d n:%d epollfd:%d connfd:%d\n", nfds, n, epollfd, events[n].data.fd);
			if (events[n].data.fd == listen_sock) {
				int sock_len = sizeof(struct sockaddr);
				conn_sock = accept(listen_sock, (struct sockaddr *) &local, (socklen_t *)&sock_len);
				if (conn_sock == -1) {
					printf_wtpid("accept error (%d)(%s)\n", errno, strerror(errno));
					exit(EXIT_FAILURE);
				}
				printf_wtpid("accept ok\n", conn_sock);
				setnonblocking(conn_sock);
				ev.events = EPOLLIN;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					printf_wtpid("epoll_ctl_ADD  error (%d)(%s)\n", errno, strerror(errno));
					exit(EXIT_FAILURE);
				}
				htable_push(iht, ev.data.fd);
			} else {
				ev = events[n];
				if (htable_pop(iht, ev.data.fd) < 0) {
					continue;
				}
				char rbuffer[MAXLINE];
				printf_wtpid("epoll_wait return %d\n", ev.data.fd);
				int ret = read(ev.data.fd, rbuffer, MAXLINE);
				if (ret <= 0) {
					epoll_close(epollfd, &ev, "read");
				}
				else {
					printf_wtpid("read ok, rbuffer:%d\n", ret);
					//int m = icl_net_send(ev.data.fd, sendbuf, 10);
					int m = write(ev.data.fd, rbuffer, ret);
					if (m < 0) {
						printf_wtpid("write error\n");
					}
					else {
						printf_wtpid("write ok! :%d\n", m);
					}
					epoll_close(epollfd, &ev, "write");
				}
			}
		}
	}
}

int epoll_close(int epollfd, struct epoll_event *ev, char *type)
{
	if (epoll_ctl(epollfd, EPOLL_CTL_DEL, ev->data.fd, ev) == -1) {
		printf_wtpid("epoll_ctl: epoll_close: %s, %d, %s\n", type, errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (htable_remove(iht, ev->data.fd) < 0) {
		printf_wtpid("htable remove error\n");
		exit(-1);
	}
	printf_wtpid("close client fd :%d\n", ev->data.fd);
	close(ev->data.fd);
}


int main(int argc, char *argv[])
{
	int n, pnum = 0;
	char buf[MAXLINE];
	struct epoll_event ev, events[MAX_EVENTS];
	int listen_sock, epollfd;
	struct sockaddr_in  servaddr;
	iht = icl_htable_create(1000);
	char ch;
	while ((ch=getopt(argc, argv, "t:")) != -1) {
		switch (ch) {
			case 't':
				pnum = atoi(optarg);
				break;
			default:
				usage();
				exit(-1);
		}
	}	

	/* Set up listening socket, 'listen_sock' (socket(),
	   bind(), listen()) */
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7744);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(servaddr.sin_zero),8);
	int ret = bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	if (ret < 0) {
		handle_error("bind error port 7744:");
		return -1;
	}
	ret = listen(listen_sock, 1024);
	if (ret < 0) {
		printf_wtpid("listen error\n");
		return -1;
	}
	/////////////////////////////////////////
	epoll_base_init(listen_sock, &epollfd);
	/////////////////////////////////////////
	pid_t pids[pnum];
	int i;
	pid_t pid;
	for (i = 0; i < pnum; i++) {
		pid = fork();
		switch (pid) {
			case -1: {
						 perror("fork error\n");
						 exit(-1);
					 }
			case 0: {
						/* parent */
						printf_wtpid("child:%d\n", i);
						child_process(epollfd, listen_sock, events);
						/* 这里直接退出，不会进入接下来的循环工作 */
						exit(0);

					}
			default: {
						 /* child */
						 pids[i] = pid;
						 printf_wtpid("parent:%d\n", pid);
						 break;

					 }
		}
	}
	parent_process(pnum, pids);
	return 0;
}
