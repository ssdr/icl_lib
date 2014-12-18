/*
 * * icl_random.c
 *   Created on: 2014年4月14日
 *   Author: peterxmw
 * */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <icl_random.h>
/*
 * 返回值需要用户手动释放
 */


char *get_char32_random(int seed)
{
	char *p = malloc(sizeof(char) * 32);
	memset(p, 0, 32);
	get_random(p, 1, 32, seed);
	p[31] = '\0';
	return p;
}

char *get_char64_random(int seed)
{
	char *p = malloc(sizeof(char) * 64);
	memset(p, 0, 64);
	get_random(p, 1, 64, seed);
	p[63] = '\0';
	return p;
}

char *get_char128_random(int seed)
{
	char *p = malloc(sizeof(char) * 128);
	memset(p, 0, 128);
	get_random(p, 1, 128, seed);
	p[127] = '\0';
	return p;
}

int get_random(char *p, int size, int nmemb, int seed)
{
	srand((unsigned int)seed);
	int i;
	for (i = 0; i < nmemb; i++)
	{
		if (i%2 == 0) {
			p[i] = rand()%25 + 65;
		}
		else {
			p[i] = rand()%25 + 97;
		}
	}
	return 0;
}
