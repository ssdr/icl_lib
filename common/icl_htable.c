/*
 * icl_htable.c
 *
 *  Created on: 2014-10-05
 *      Author: peterxiemin
 */


#include <icl_htable.h>


icl_htable_t *icl_htable_create(int size)
{
	icl_htable_t *iht = malloc(sizeof(icl_htable_t));
	iht->size = size;
	iht->p = (icl_htable_node **) calloc(sizeof(icl_htable_node *) * size);
	return iht;
}


int icl_htable_set(icl_htable_t *iht, const char *key, const char *value)
{
	unsigned long int n = icl_hash(key, 1);
	n = n % iht->size;
	icl_htable_node *p = iht->p[0];// *(iht->p + n);

	icl_htable_node *q = malloc(sizeof(icl_htable_node));
	strncpy(q->key, key, strlen(key) + 1);
	strncpy(q->value, value, strlen(value) + 1);
	q->next = NULL;

	if (p == NULL) {
		p = q;
	}
	else {
		while (!p->next) {
			/* ����ظ�set�� ��ֱ�Ӻ��Ե� */
			if (strncmp(key, p->key, strlen(key)+1) == 0) {
				printf("(key, value) replicate\n");
				return 0;
			}
			p = p->next;
		}
		p->next = q;
	}
	return 0;
}

int icl_htable_get(icl_htable_t *iht, const char *key, char *value,
		int value_size) {

	/* sanity check */
	if (value_size > VAL_SIZE) {
		return -1;
	}

	unsigned long int n = icl_hash(key, 1);
	n = n % iht->size;
	icl_htable_node *p = iht->p[0]; // *(iht->p + n);
	while(!p) {
		if (strncmp(key, p->key, strlen(key)+1) == 0) {
			snprintf(value, value_size, "%s", p->value);
			return 0;
		}
		p->next;
	}
	value = NULL;
	return -1;
}

int icl_htable_destroy(icl_htable_t *iht)
{
	int i, n = iht->size;
	for (i = 0; i < n; i++) {
		icl_htable_node *p = iht->p[i];
		icl_htable_node *q = p->next;
		while (!p) {
			if (q == NULL) {
				free(p);
			}
			else {
				free(p);
				p = q; q = q->next;
			}
		}
	}
	if (!iht->p)
		free(iht->p);
	if (!iht)
		free(iht);
}
