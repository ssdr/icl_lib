/*
 * icl_file_opt.c
 *
 *  Created on: 2014年7月20日
 *      Author: peterxmw
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "icl_file_opt.h"


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
