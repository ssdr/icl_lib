/*
 * author: xiemin
 * file_name: icl_array.c
 * company: ifeng
 * date: 2014-09-29
 *
 */

#include <icl_array.h>

/*
 * 将create和init合二为一
 */
icl_array_t *icl_array_create(int n, int size) {
	icl_array_t *iat = malloc(sizeof(icl_array_t));
	iat->nelt = n;
	iat->elt_size = size;
	iat->pos = 0;
	iat->p = malloc(n * size);
	return iat;
}

void *icl_array_push_back(icl_array_t *iat) {
	if (iat == NULL) {
		printf("icl_array_t is NULL\n");
		return -1;
	}

	if (iat->pos >= iat->nelt) {
		icl_array_append(iat);
	}
	void *p = iat->p + (iat->elt_size * iat->pos);
	iat->pos++;
	return p;
}

/*
 * 如果空间不足， 再扩大一倍的容量
 */
int icl_array_append(icl_array_t *iat) {
	void *p = realloc(iat->p, iat->nelt * iat->elt_size * 2);
	/*
	 * 这里需要注意， 有坑！
	 * 如果系統空間不足夠， realloc會重新釋放掉原來的空間，創建新的空間， 這樣一來，原來指針
	 * 指向的內容，就無效了。acl和nginx都用不同的方式繞過了這個函數
	 * 在使用过程中， 切忌将各个元素的指针再次引用，以免realloc后，报告空指针异常
	 */
	if (p == NULL) {
		return -1;
	}
	iat->p = p;
	return 0;
}

int icl_array_destroy(icl_array_t *iat) {
	void *p = iat->p;
	if (p) {
		free(p);
	}
	if (iat) {
		free(iat);
	}
	return 0;
}
