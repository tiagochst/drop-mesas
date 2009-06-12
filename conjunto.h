#ifndef CONJUNTO_H_
#define CONJUNTO_H_

/* estrutura de um conjunto modificado, em que se
 * um dado elemento for inserido mais de uma vez,
 * sua frequência 'freq' é incrementada */

typedef struct conjunto_ {
	void *i;
	struct conjunto_ *next;
	int sz;
	int freq;
} Conjunto;

typedef int (*funcao_cmp)(void*, void*);
typedef double (*funcao_prod)(void*, void*);
typedef void (*funcao_free)(void*);
typedef void (*funcao_copy)(void**, void**);

Conjunto *conj_init();
void conj_destroy(Conjunto *c, funcao_free Ffree);
int conj_vazio(Conjunto *c);
int conj_size(Conjunto *c);
int conj_size_bytes(Conjunto *c);
void conj_insere(Conjunto *c, void *e, int n_bytes, funcao_cmp Fcmp, funcao_copy Fcopy);
Conjunto *conj_interseccao(Conjunto *c1, Conjunto *c2, funcao_cmp Fcmp, funcao_copy Fcopy);
Conjunto *conj_uniao(Conjunto *c1, Conjunto *c2, funcao_cmp Fcmp, funcao_copy Fcopy, int ignore_freq);
int conj_prod_escalar(Conjunto *c1, Conjunto *c2, funcao_cmp Fcmp, funcao_prod Fprod);

#endif /* CONJUNTO_H_ */
