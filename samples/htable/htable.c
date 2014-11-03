#include <stdio.h>
#include <icl_htable.h>

#define TEST_SIZE 1000
int main(int argc, char *argv[])
{
	Icl_Htable *iht = icl_htable_create(TEST_SIZE/2);
	if (iht == NULL) return -1;
	int i;
	for (i = 0; i < TEST_SIZE; i++) {
		char key[32], value[64];
		snprintf(key, 32, "xie%dmin", i);
		snprintf(value, 64, "wang%dyufeng", i);
		/* add */
		int ret = icl_htable_set(iht, key, value);
		if (ret < 0) {
			printf("icl_htable_set error\n");
		}
		/* del */
		ret = icl_htable_del(iht, key);
		if (ret < 0) {
			printf("icl_htable_set error\n");
		}
		/* query */
		memset(value, 0, 64);
		ret = icl_htable_get(iht, key, value, 64);
		if (ret < 0) {
			printf("icl_htable_get error\n");
		}
		printf("%s\n", value);
	}
	icl_htable_destroy(iht);
	return 0;
}


