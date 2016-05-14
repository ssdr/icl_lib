/*
 * icl_file_opt.c
 *
 *  Created on : 2014年9月1日
 *      Author : peterxmw
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "icl_file_opt.h"


int icl_open(const char *path, int flags)
{
	return open(path, flags);
}

int icl_open2(const char *path, int flags, mode_t mode)
{
	return open(path, flags, mode);
}

FILE *icl_fopen(const char *path, const char *mode)
{
	return fopen(path, mode);
}

FILE *icl_fdopen(int fd, const char *mode)
{
	return fdopen(fd, mode);
}

int icl_fseek(FILE *stream, long off_set, int whence)
{
	return fseek(stream, off_set, whence);
}

long icl_ftell(FILE *stream)
{
	return ftell(stream);
}

int icl_fclose(FILE *stream)
{
	return fclose(stream);
}

unsigned long icl_get_flsz(const char *path)
{
	unsigned long filesize = -1;
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}

void icl_stat(const char *pathname)
{
	struct stat sb;
	if (stat(pathname, &sb) == -1) {
		perror("stat");
		exit(EXIT_SUCCESS);
	}
	printf("File type:                ");

	switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break;
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}
	printf("Mode:                     %lo (octal)\n",
			(unsigned long) sb.st_mode);

	printf("Link count:               %ld\n", (long) sb.st_nlink);
	printf("Ownership:                UID=%ld   GID=%ld\n",
			(long) sb.st_uid, (long) sb.st_gid);

	printf("Preferred I/O block size: %ld bytes\n",
			(long) sb.st_blksize);
	printf("File size:                %lld bytes\n",
			(long long) sb.st_size);
	printf("Blocks allocated:         %lld\n",
			(long long) sb.st_blocks);

	printf("Last status change:       %s", ctime(&sb.st_ctime));
	printf("Last file access:         %s", ctime(&sb.st_atime));
	printf("Last file modification:   %s", ctime(&sb.st_mtime));
}

/*
 * 可以使用link和stat配合创建lockfile，避免使用记录锁，降低复杂度，提高性能
 * 参考ts封包项目，lockfile解决多进程操作*.bin文件
 *
 * */
int icl_link(const char *src_pathname, const char *dst_pathname)
{
	int ret = link(src_pathname, dst_pathname);
	/* failed */
	if (ret != 0)
	{
		printf("icl_link failed (%d)(%s)\n", errno, strerror(errno));
	}
	/* sucess */
	return 0;
}


int icl_unlink(const char *pathname)
{
	int ret = unlink(pathname);
	/* failed */
	if (ret != 0)
	{
		printf("icl_unlink failed (%d)(%s)\n", errno, strerror(errno));
	}
	/* sucess */
	return 0;
}


#define READ	0
#define WRITE	1
#define FREAD	2
#define FWRITE	3

/* stream */

int icl_fwrite(void *ptr, int size, int nmemb, FILE *stream)
{
	return icl_io(ptr, size, nmemb, stream, FWRITE);
}

int icl_fread(void *ptr, int size, int nmemb, FILE *stream)
{
	return icl_io(ptr, size, nmemb, stream, FREAD);
}

/* no stream */

int icl_write(int fd, void *buf, int count)
{
	return icl_io(buf, count, 1, &fd, WRITE);
}

int icl_read(int fd, void *buf, int count)
{
	return icl_io(buf, count, 1, &fd, READ);
}

int icl_io(void *ptr, int size, int nmemb, void *stream, int flags)
{
	int left = size * nmemb;
	char *p = ptr;
	int ret = -1;
	while (left) {
		switch (flags) {
			case FREAD: {
				FILE *s = (FILE *) stream;
				ret = fread(p, nmemb, left/nmemb, s);
				printf("icl_io ret: %d\n", ret);
				break;
			}
			case FWRITE: {
				FILE *s = (FILE *) stream;
				ret = fwrite(p, nmemb, left/nmemb, s);
				break;
			}
			case READ: {
				int fd = *(int *) stream;
				ret = read(fd, p, left);
				printf("icl_io ret: %d\n", ret);
				break;
			}
			case WRITE: {
				int fd = *(int *) stream;
				ret = write(fd, p, left);
				break;
			}
			default: {
				printf("flag error\n");
				return -1;
			}
		}

		if (ret == 0) {
			printf("iclio end-of-file\n");
			return -1;
		}
		if (ret < 0) {
			printf("iclio failed (%d: %s)\n", errno, strerror(errno));
			return -1;
		}
		left -= ret;
		p += ret;
	}
	return 0;
}
