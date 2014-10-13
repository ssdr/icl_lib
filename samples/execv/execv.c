/*
 * execv.c
 *
 *  Created on: 2014年10月12日
 *      Author: peterxiemin
 */

#include <icl_fork.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argv[1] == NULL) {
		printf("argv[1] == NULL \n");
		return -1;
	}
	if (strncmp(argv[1], "0", strlen("0")) == 0) {
		int fd = open("/tmp/a.txt", O_RDWR);
		int fdbak = dup(fd);
		int status = fcntl(fd, F_SETFD, FD_CLOEXEC);
		if (status < 0) {
			printf("fcntl error \n");
		}
		if (fd == -1) {
			printf("fopen error(%d:%s)\n", errno, strerror(errno));
		}
		printf("fd :%d, fdbak :%d\n", fd, fdbak);
		pid_t pid = fork();
		switch (pid) {
			case -1: {
						 printf("fork error(%d:%s)\n", errno, strerror(errno));
						 return -1;
					 }
			case 0:  {
						 printf("child execl\n");
						 argv[1] = "1";
						 int ret = execvp(argv[0], argv);
						 if (ret < 0) {
							 printf("execv error(%d:%s)\n", errno, strerror(errno));
						 }
						 return -1;
					 }
			default:
					 break;
		}
		sleep(5);
		char buf[128];
		int ret = read(3, buf, 5);
		buf[5] = '\0';
		printf("exev read ret : %d (%d)(%s)\n", ret, errno, strerror(errno));
		if (ret > 0) {
			printf("buf:%s\n", buf);
		}
	}

	if (strncmp(argv[1], "1", strlen("1")) == 0) {
		sleep(10);
		char buf[128];
		int fd = open("/tmp/a.txt", O_RDWR);
		printf("exec open fd :%d\n", fd);

		int ret = read(3, buf, 5);
		buf[5] = '\0';
		printf("exev read ret : %d (%d)(%s)\n", ret, errno, strerror(errno));
		if (ret > 0) {
			printf("buf:%s\n", buf);
		}
		close(fd);
		close(4);
		close(3);
	}

	return 0;
}

