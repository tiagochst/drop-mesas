#ifndef CONJUNTO_H_
#define CONJUNTO_H_

typedef struct conjunto_ {
	void *i;
	struct conjunto_ *next;
	int sz;
} conjunto;

typedef int (*funcao)(void*, void*);

conjunto *conj_init();
void conj_destroy(conjunto *c);
void conj_insere(conjunto *c, void *e, int sz, funcao cmp);
conjunto *conj_interseccao(conjunto *c1, conjunto *c2, funcao cmp);
conjunto *conj_diferenca(conjunto *c1, conjunto *c2, funcao cmp);

#endif /*CONJUNTO_H_*/
