/*
 * fork.c
 *
 *  Created on: 2014年10月12日
 *      Author: peterxiemin
 */

#include <icl_fork.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char argv[])
{
	pid_t pid = fork();
	int fd = open("/tmp/a.txt", O_CREAT|O_WRONLY|O_TRUNC);

	switch (pid) {
	case -1:
		printf("fork error(%d:%s)\n", errno, strerror(errno));
		return -1;
	case 0:
		/*child*/
		sleep(5);
		break;
	default:
		printf("parent close fd\n");
		close(fd);
		return -1;
	}
	/*child*/
	char buf[] = "hello world";
	int ret = write(fd, buf, sizeof(buf));
	if (ret == -1) {
		printf("write error(%d:%s)\n", errno, strerror(errno));
		return -1;
	}
	printf("child over\n");
	return 0;
}


