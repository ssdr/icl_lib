#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <icl_random.h>

int domain(int seed)
{
	char *p = get_char128_random(seed);
	printf("%s\n", p);
	free(p);
	return 0;
}

int main(int argc, char *argv[])
{
	int i;
	for (i=1; i < 10; i++) {
		domain(i);
	}
}
