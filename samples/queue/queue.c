#include <stdio.h>
#include <stdlib.h>
#include <icl_list.h>

/* 加入回调函数 */
typedef int Icl_List_Add(Icl_List *h, void *d);
typedef Icl_List *Icl_List_Del(Icl_List *h);



int main(int argc, char *argv[])
{
	int i;
	Icl_List_Add *func_add;
	Icl_List_Del *func_del;
	Icl_List *l = icl_list_init();
	for (i = 0; i < 4; i++) {
		switch (i) {
			case 0: {
						/*
						 * icl_list_push_back;
						 * icl_list_push_front;
						 */
						func_add = icl_list_push_back;
						/*
						 * icl_list_pop_back;
						 * icl_list_pop_front;
						 */
						func_del = icl_list_pop_back;
						break;
					}
			case 1: {
						func_add = icl_list_push_back;
						func_del = icl_list_pop_front;
						break;		
					}
			case 2: {
						func_add = icl_list_push_front;
						func_del = icl_list_pop_back;
						break;
					}
			case 3: {
						func_add = icl_list_push_front;
						func_del = icl_list_pop_front;
						break;
					}
			default:
					return -1;

		}

		int i = 0;
#define TEST_SIZE 1000000
		for (i = 0; i < TEST_SIZE; i++) {
			int *t = malloc(sizeof(int));
			*t = i;
			func_add(l, t);
		}
		printf("size: %d\n", icl_list_size(l));

		for (i = 0; i < TEST_SIZE; i++) {
			Icl_List *p = func_del(l);
			icl_list_free(p);
		}
		printf("size: %d\n", icl_list_size(l));
	}
	icl_list_destroy(l);
	/* for test memory leak */
	//sleep(100);
	return 0;
}
