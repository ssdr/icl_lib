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

int main(int argc, char argv[]) {
	if (strncmp(argv[1], "0", strlen("0"))) {
		pid_t pid = fork();
		int fd = open("/tmp/a.txt", O_CREAT | O_WRONLY | O_TRUNC);
		if (fd == -1) {
			printf("fopen error(%d:%s)\n", errno, strerror(errno));
		}
		switch (pid) {
		case -1:
			printf("fork error(%d:%s)\n", errno, strerror(errno));
			return -1;
		case 0:
			/*child*/
			/* 通过参数进行控制 */
			int ret = execl(argv[0], "1", (char *) 0);
			if (ret < 0) {
				printf("execv error(%d:%s)\n", errno, strerror(errno));
			}
			return -1;
		default:
			break;
		}
	}

	if (strncmp(argv[1], "1", strlen("1"))) {
		char buf[] = "hello world";
		int fd = open("/tmp/a.txt", O_CREAT | O_WRONLY | O_TRUNC);
		if (fd == -1) {
			printf("fopen error(%d:%s)\n", errno, strerror(errno));
		}
		printf("child close fd %d\n", fd);
		close(fd);
	}

	return 0;
}

