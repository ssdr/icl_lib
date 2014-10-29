/*
 * icl_array.c
 *
 *  Created on: 2014Äê10ÔÂ29ÈÕ
 *      Author: peterxiemin
 */


#include <icl_array.h>
#include <assert.h>
#define TEST_SIZE 10

struct A {
	int t;
};
typedef struct A A;

int main(int argc, char *argv[])
{

	Icl_Array *iay = icl_array_create(5, sizeof(A));
	A *a;
	a = icl_array_push_back(iay); 
	a->t = 1;
	printf("pos :%d nelt: %d\n", iay->pos, iay->nelt);
	a = icl_array_push_back(iay); 
	a->t = 2;
	printf("pos :%d nelt: %d\n", iay->pos, iay->nelt);
	a = icl_array_push_back(iay); 
	a->t = 3;
	printf("pos :%d nelt: %d\n", iay->pos, iay->nelt);
	a = icl_array_push_back(iay); 
	a->t = 4;
	printf("pos :%d nelt: %d\n", iay->pos, iay->nelt);
	a = icl_array_push_back(iay); 
	a->t = 5;
	printf("pos :%d nelt: %d\n", iay->pos, iay->nelt);
	a = icl_array_push_back(iay); 
	a->t = 6;
	printf("pos :%d nelt: %d\n", iay->pos, iay->nelt);
	int i;
	for (i = 0; i < 5; i++) {
		a = icl_array_index(iay, i);
		printf("%d\n", a->t);
	}
	icl_array_destroy(iay);
	return 0;
}




