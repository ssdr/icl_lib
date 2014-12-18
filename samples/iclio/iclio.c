#include <stdio.h>
#include <stdlib.h>
#include <icl_file_opt.h>
#include <icl_time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


#define SIZE 1024*1024*1024


int batch_write(FILE *fd, char *buf, int len)
{
	int ret = icl_fwrite(buf, 1, len, fd);
	if (ret < 0) {
		printf("icl_read: ret: %d \n", ret);
	}
}


int main(int argc, char *argv[])
{
	int ret;
	char *buf = (char *)malloc(SIZE);
	FILE *fd = icl_fopen("/tmp/test", "a");
//	int fd = icl_open("/tmp/test", O_RDWR);
	//icl_prtnow();
	//ret = icl_fread(buf, SIZE, 1, fd);
//	ret = icl_read(fd, buf, SIZE);
	//icl_prtnow();
//	close(fd);


	int i = 0;
	char buf1[] = "xiemin\n";
	for (i=0; i<100000000; i++) {
		batch_write(fd, buf1, strlen(buf1));
	}
	
	fclose(fd);
	free(buf);
	return 0;
}
