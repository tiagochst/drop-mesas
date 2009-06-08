#ifndef CONJUNTO_H_
#define CONJUNTO_H_

typedef struct conjunto_ {
	void *i;
	struct conjunto_ *next;
	int sz;
} Conjunto;

typedef int (*funcao)(void*, void*);

Conjunto *conj_init();
void conj_destroy(Conjunto *c);
int conj_vazio(Conjunto *c);
int conj_size(Conjunto *c);
void conj_insere(Conjunto *c, void *e, int n_bytes, funcao cmp);
Conjunto *conj_interseccao(Conjunto *c1, Conjunto *c2, funcao cmp);
Conjunto *conj_diferenca(Conjunto *c1, Conjunto *c2, funcao cmp);

#endif /*CONJUNTO_H_*/
