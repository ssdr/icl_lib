/*
 *
 * author: xiemin
 * file_name: icl_math.c
 * company: ifeng
 * date: 2014-11-24
 *
 */
#include <stdio.h>
#include <icl_math.h>



void icl_divisor(int x)
{
	int i;
	for (i = 1; i <= x; i++) {
		if (x%i == 0) {
			printf("i:%d\n", i);
		}
	}
}

int icl_max(int a, int b) {
	return  a > b ? a : b;
}


int icl_min(int a, int b) {
	return  a < b ? a : b;
}
