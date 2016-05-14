//
//  icl_file_opt.h
//  icllib
//
//  Created by peterxm on 14-9-1.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//


#ifndef ICLLIB_ICL_FILE_OPT_H
#define ICLLIB_ICL_FILE_OPT_H

#include <stdio.h>
#include <stdlib.h>


// open and possibly create a file
int icl_open(const char *path, int flags);
int icl_open2(const char *path, int flags, mode_t mode);

// stream open functions
FILE *icl_fopen(const char *path, const char *mode);
FILE *icl_fdopen(int fd, const char *mode);

// reposition a stream
int icl_fseek(FILE *stream, long off_set, int whence);
long icl_ftell(FILE *stream);

// close a stream
int icl_fclose(FILE *stream);

// get file size by stat()
unsigned long icl_get_flsz(const char *path);

// print file stat info
void icl_stat(const char *pathname);

int icl_link(const char *src_pathname, const char *dst_pathname);
int icl_unlink(const char *pathname);

int icl_fwrite(void *ptr, int size, int nmemb, FILE *stream);
int icl_fread(void *ptr, int size, int nmemb, FILE *stream);
int icl_write(int fd, void *buf, int count);
int icl_read(int fd, void *buf, int count);
int icl_io(void *ptr, int size, int nmemb, void *stream, int flags);

#endif
