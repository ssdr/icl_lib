/*
 * author: xiemin
 * file_name: icl_array.c
 * company: ifeng
 * date: 2014-10-29
 *
 */

#include <icl_array.h>
#include <assert.h>
/* TODO:
 * 添加array的删除功能
 */

/*
 * create 和 init合二为一
 */
Icl_Array *icl_array_create(int n, int size) {
	Icl_Array *iay = malloc(sizeof(Icl_Array));
	iay->nelt = n;
	iay->elt_size = size;
	iay->pos = 0;
	iay->p = malloc(n * size);
	return iay;
}

void *icl_array_index(Icl_Array *iay, int idx)
{
	assert(iay != NULL);
	int index = idx;
	//if (idx > iay->pos) {
	//	index = iay->pos;
	//}
	assert(index <= iay->pos);
	return iay->p + (iay->elt_size * index);
}

void *icl_array_push_back(Icl_Array *iay) 
{
	assert(iay != NULL);
	if (iay->pos >= iay->nelt) {
		int ret = icl_array_append(iay);
		if (ret < 0) {
			return NULL;
		}
	}
	void *p = iay->p + (iay->elt_size * iay->pos);
	iay->pos++;
	return p;
}

int icl_array_append(Icl_Array *iay) {
	
	iay->nelt *= 2;
	void *p = realloc(iay->p, iay->nelt * iay->elt_size);
	/*
	 * 这里需要注意， 有坑！
	 * 如果系統空間不足夠， realloc會重新釋放掉原來的空間，創建新的空間， 這樣一來，原來指針
	 * 指向的內容，就無效了。acl和nginx都用不同的方式繞過了這個函數
	 * 在使用过程中， 切忌将各个元素的指针再次引用，以免realloc后，报告空指针异常
	 */
	if (p == NULL) {
		return -1;
	}
	iay->p = p;
	return 0;
}

int icl_array_destroy(Icl_Array *iay) {
	void *p = iay->p;
	if (p) {
		free(p);
	}
	if (iay) {
		free(iay);
	}
	return 0;
}
