#include <stdio.h>


int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 1025; i++) {
		FILE *fd = fopen("/tmp/a.c", "r");
		if (fd == NULL) {
			perror(" fopenerror");
			printf("i:%d\t", i);
		}
	}
	return 0;
}
