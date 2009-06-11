#include <stdlib.h>
#include <string.h>
#include "conjunto.h"

/* INICIALIZA CONJUNTO
 * gera o nó cabeça e o devolve */
Conjunto *conj_init() {
	Conjunto *y = (Conjunto *) malloc(sizeof(Conjunto));
	y->i = NULL;
	y->next = NULL;
	return y;
}

/* DESTRÓI CONJUNTO
 * desaloca todos os nós */
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

int conj_size_freq(Conjunto *c) {
	int n;
	for (n = 0, c = c->next; c != NULL; c = c->next)
		n += c->freq;
	return n;
}

/* INSERE CONJUNTO
 * dado um elemento, seu número de bytes,
 * e uma função de comparação, insere o elemento
 * no conjunto na posição correta */
void conj_insere(Conjunto *c, void *e, int n_bytes, funcao_cmp cmp) {
	Conjunto *novo;

	while (c->next != NULL && cmp(c->next->i, e) < 0)
		c = c->next;

	if (c->next != NULL && cmp(c->next->i, e) == 0) {
		(c->next->freq)++;
		return;
	}

	novo = (Conjunto *) malloc(sizeof(Conjunto));
	novo->i = malloc(n_bytes);
	memcpy(novo->i, e, n_bytes);
	novo->sz = n_bytes;
	novo->next = c->next;
	novo->freq = 1;
	c->next = novo;
}

/* INTERSECÇÃO DE CONJUNTO
 * dados 2 conjuntos e uma função de comparação
 * devolve a intersecção dos conjuntos */
Conjunto *conj_interseccao(Conjunto *c1, Conjunto *c2, funcao_cmp cmp) {
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

/* UNIÃO DE CONJUNTO
 * dados 2 conjuntos e uma função de comparação
 * devolve a união dos conjuntos */
Conjunto *conj_uniao(Conjunto *c1, Conjunto *c2, funcao_cmp cmp) {
	Conjunto *uniao = conj_init();
	int i;
	c1 = c1->next;
	c2 = c2->next;

	while (c1 != NULL) {
		for (i = 0; i < c1->freq; i++)
			conj_insere(uniao, c1->i, c1->sz, cmp);
		c1 = c1->next;
	}
	while (c2 != NULL) {
		for (i = 0; i < c2->freq; i++)
			conj_insere(uniao, c2->i, c2->sz, cmp);
		c2 = c2->next;
	}

	return uniao;
}

int conj_prod_escalar(Conjunto *c1, Conjunto *c2, funcao_cmp cmp) {
	int prod = 0, diff;
	c1 = c1->next;
	c2 = c2->next;

	while (c1 != NULL && c2 != NULL) {
		diff = cmp(c1->i, c2->i);

		if (diff == 0) {
			prod += c1->freq * c2->freq;
			c1 = c1->next;
			c2 = c2->next;
		} else if (diff < 0)
			c1 = c1->next;
		else
			c2 = c2->next;
	}

	return prod;
}
