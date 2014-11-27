#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	 char *a = 0x1;
	 char *b = realloc(a, 10);
	 return 0;
}
