#include <stdlib.h>
#include "conjunto.h"

conjunto *conj_init() {
	conjunto *y = (conjunto *) malloc(sizeof(conjunto));
	y->i = NULL;
	y->next = NULL;
	return y;
}

void conj_destroy(conjunto *c) {
	conjunto *next;
	
	for(; c != NULL ; c = next) {
		next = c->next;
		free(c);
	}
}

void conj_insere(conjunto *c, void *e, funcao cmp) {
	conjunto *novo;
	
	while(c->next != NULL &&
	      cmp(c->next->i, e) < 0)
		c = c->next;

	while(c->next != NULL &&
	      cmp(c->next->i, e) == 0)
		return;

	novo = (conjunto *) malloc(sizeof(conjunto));
	novo->i = e;
	novo->next = c->next;
	c->next = novo;
}

conjunto *conj_interseccao(conjunto *c1, conjunto *c2, funcao cmp) {
	conjunto *inter = conj_init();
	int diff;
	c1 = c1->next;
	c2 = c2->next;
	
	while(c1!=NULL && c2!=NULL) {
		diff = cmp(c1->i, c2->i);
		
		if(diff == 0) conj_insere(inter, c1->i, cmp);
		else if(diff < 0) c1 = c1->next;
		else c2 = c2->next;
	}
	
	return inter;
}

conjunto *conj_diferenca(conjunto *c1, conjunto *c2, funcao cmp) {
	conjunto *difer = conj_init();
	int diff;
	c1 = c1->next;
	c2 = c2->next;
	
	while(c1!=NULL && c2!=NULL) {
		diff = cmp(c1->i, c2->i);
		
		if(diff == 0) {
			c1 = c1->next;
			c2 = c2->next;
		}
		else if(diff < 0) {
			conj_insere(difer, c1->i, cmp);
			c1 = c1->next;
		}
		else c2 = c2->next;
	}
	while(c1!=NULL) {
		conj_insere(difer, c1->i, cmp);
		c1 = c1->next;
	}
	
	return difer;
}
