//
//  icl_file_opt.h
//  icllib
//
//  Created by peterxm on 14-7-20.
//  Copyright (c) 2014年 peterxm. All rights reserved.
//


#ifndef ICLLIB_ICL_FILE_OPT_H
#define ICLLIB_ICL_FILE_OPT_H

FILE  *icl_fopen(const char *path, const char *mode); 
FILE  *icl_fdopen(int fd, const char *mode);

int icl_fseek(FILE *stream, long off_set, int whence);
int icl_ftell(FILE *stream);
int icl_fclose(FILE *stream);

unsigned long  icl_get_flsz(const char *path);



#endif
