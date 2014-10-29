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
#include <errno.h>

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
		break;
	default: {
				 char buf[] = "parent";
				 int ret = write(fd, buf, sizeof(buf));
				 if (ret == -1) {
					 printf("parent write error(%d:%s)\n", errno, strerror(errno));
				 }
				 close(fd);
				 return -1;
			 }
	}
	/*child*/
	char buf[] = "child";
	int ret = write(fd, buf, sizeof(buf));
	if (ret == -1) {
		printf("child write error(%d:%s)\n", errno, strerror(errno));
		return -1;
	}
	printf("child close fd %d\n", fd);
	close(fd);
	return 0;
}


