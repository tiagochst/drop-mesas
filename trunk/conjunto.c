#include <stdlib.h>
#include <string.h>
#include "conjunto.h"

Conjunto *conj_init() {
	Conjunto *y = (Conjunto *) malloc(sizeof(Conjunto));
	y->i = NULL;
	y->next = NULL;
	return y;
}

void conj_destroy(Conjunto *c) {
	Conjunto *next;

	next = c->next;
	free(c);
	for (c = next; c != NULL; c = next) {
		next = c->next;
		free(c->i);
		free(c);
	}
}

int conj_vazio(Conjunto *c) {
	return (c->next == NULL)?(1):(0);
}

int conj_size(Conjunto *c) {
	int n;
	for (n = 0; c->next != NULL; n++, c = c->next);
	return n;
}

void conj_insere(Conjunto *c, void *e, int n_bytes, funcao cmp) {
	Conjunto *novo;

	while (c->next != NULL && cmp(c->next->i, e) < 0)
		c = c->next;

	if (c->next != NULL && cmp(c->next->i, e) == 0)
		return;

	novo = (Conjunto *) malloc(sizeof(Conjunto));
	novo->i = malloc(n_bytes);
	memcpy(novo->i, e, n_bytes);
	novo->sz = n_bytes;
	novo->next = c->next;
	c->next = novo;
}

Conjunto *conj_interseccao(Conjunto *c1, Conjunto *c2, funcao cmp) {
	Conjunto *inter = conj_init();
	int diff;
	c1 = c1->next;
	c2 = c2->next;

	while (c1!=NULL && c2!=NULL) {
		diff = cmp(c1->i, c2->i);

		if (diff == 0) {
			conj_insere(inter, c1->i, c1->sz, cmp);
			c1 = c1->next;
			c2 = c2->next;
		} else if (diff < 0)
			c1 = c1->next;
		else
			c2 = c2->next;
	}

	return inter;
}

Conjunto *conj_diferenca(Conjunto *c1, Conjunto *c2, funcao cmp) {
	Conjunto *difer = conj_init();
	int diff;
	c1 = c1->next;
	c2 = c2->next;

	while (c1!=NULL && c2!=NULL) {
		diff = cmp(c1->i, c2->i);

		if (diff == 0) {
			c1 = c1->next;
			c2 = c2->next;
		} else if (diff < 0) {
			conj_insere(difer, c1->i, c1->sz, cmp);
			c1 = c1->next;
		} else
			c2 = c2->next;
	}
	while (c1!=NULL) {
		conj_insere(difer, c1->i, c1->sz, cmp);
		c1 = c1->next;
	}

	return difer;
}
