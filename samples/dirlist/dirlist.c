#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	FILE *listfp;
	
	char logpath[] = "/tmp";
	char cmd[256];
	snprintf(cmd, 256, "ls -1 %s", logpath);
	char logname[] = "a.c";
	char d_name[1024];
	char buf[1024];
	struct stat fs;

	listfp = popen(cmd, "r");
	if (listfp == NULL) {
		perror("listfp popen error");
		exit(-1);
	}

	while (!feof(listfp)) {
		if( fgets(d_name, sizeof(d_name), listfp) == NULL  ) continue;
		int i;
		for(i=0;i<strlen(d_name);i++)
		{
			if( d_name[i]=='\n' || d_name[i]=='\r'  )
			{
				d_name[i]='\0';
				break;
			}

		}
		if( strlen(d_name)<=0  ) continue;
		if( strcmp( d_name, "."  )==0 || strcmp( d_name, ".."  )==0  ) continue;
		sprintf(buf, "%s/%s", logpath, d_name);
		if( S_ISLNK(fs.st_mode) || S_ISDIR(fs.st_mode)  ) continue;
		if( strstr( d_name, logname )==NULL  )    continue;
		printf("%s\n", buf);
	}

	return 0;
}
