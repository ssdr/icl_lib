/*
 * icl_htable.c
 *
 *  Created on: 2014-10-29
 *      Author: peterxiemin
 */
#include <icl_hash.h>
#include <icl_htable.h>


Icl_Htable *icl_htable_create(int size)
{
	Icl_Htable *iht = malloc(sizeof(Icl_Htable));
	if (iht == NULL) {
		return NULL;
	}	
	iht->size = size;
	iht->p = (Icl_Htable_Node **) calloc(size, sizeof(Icl_Htable_Node *));
	if (iht->p == NULL) {
		return NULL;
	}
	return iht;
}


int icl_htable_set(Icl_Htable *iht, const char *key, const char *value)
{
	unsigned long int n = icl_hash_func2(key, 1);
	n = n % iht->size;

	Icl_Htable_Node *q = malloc(sizeof(Icl_Htable_Node));
	if (q == NULL) {
		return -1;
	}
	snprintf(q->key, strlen(key) + 1, "%s", key);
	snprintf(q->value, strlen(value) + 1, "%s", value);
	q->next = NULL;
	if (iht->p[n] == NULL) {
		iht->p[n] = q;
	}
	else {
		Icl_Htable_Node *p = iht->p[n];
		do {
			if (strcmp(key, p->key) == 0) {
				printf("(key, value) replicate\n");
				return 0;
			}
		} while (p->next != NULL && (p=p->next));
		p->next = q;
	}
	return 0;
}

int icl_htable_get(Icl_Htable *iht, const char *key, char *value,
		int value_size) {

	/* sanity check */
	if (value_size > VAL_SIZE) {
		return -1;
	}

	unsigned long int n = icl_hash_func2(key, 1);
	n = n % iht->size;
	Icl_Htable_Node *p = iht->p[n]; // *(iht->p + n);
	while (p != NULL) {
		if (strcmp(key, p->key) == 0) {
			snprintf(value, value_size, "%s", p->value);
			return 0;
		}
		p = p->next;
	}
	value = NULL;
	return -1;
}

int icl_htable_destroy(Icl_Htable *iht)
{
	int i, n = iht->size;
	for (i = 0; i < n; i++) {
		if (iht->p[i] == NULL) {
			continue;
		}
		Icl_Htable_Node *t = iht->p[i];
		Icl_Htable_Node *k = t->next;
		while (1) {
			if (k == NULL) {
				free(t);
				break;
			}
			free(t);
			t = k; k = k->next;
		}
	}
	if (iht->p != NULL) {
		free(iht->p);
	}
	if (iht != NULL) {
		free(iht);
	}
}
