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

Conjunto *conj_init();
void conj_destroy(Conjunto *c);
int conj_vazio(Conjunto *c);
int conj_size(Conjunto *c);
int conj_size_freq(Conjunto *c);
void conj_insere(Conjunto *c, void *e, int n_bytes, funcao_cmp cmp);
Conjunto *conj_interseccao(Conjunto *c1, Conjunto *c2, funcao_cmp cmp);
Conjunto *conj_uniao(Conjunto *c1, Conjunto *c2, funcao_cmp cmp);
int conj_prod_escalar(Conjunto *c1, Conjunto *c2, funcao_cmp cmp);

#endif /* CONJUNTO_H_ */
