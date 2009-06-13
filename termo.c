#include "definicoes.h"

int Termo_cmp(void *a, void *b) {
	return strcmp(((Termo *) a)->s, ((Termo *) b)->s);
}

double Termo_prod(void *a, void *b) {
	return ((Termo *) a)->peso * ((Termo *) b)->peso;
}

void Termo_free(void *a) {
	free(((Termo *) a)->s);
	free(a);
}

void Termo_copy(void **a, void **b) {
	Termo *x = (Termo*) malloc(sizeof(Termo)), *y = *(Termo**) b;

	x->s = (char*) malloc((strlen(y->s) + 1) * sizeof(char));
	memcpy(x->s, y->s, (strlen(y->s) + 1) * sizeof(char));

	x->peso = y->peso;

	*a = (void*) x;
}

/* TERMO STRING TOKENIZER */
/* divide a string dada em palavras, montando
 * e devolvendo um conjunto das palavras, mas
 * usando a estrutura Termo */
Conjunto *Termo_strtokenizer(char *s) {
	Conjunto *c = conj_init();
	char *tok;
	char *delimiters = "_ .,;:!?()[]{}<>'\"\t\\/";
	Termo t;
	t.peso = 0.0; /* não calculado ainda */

	/* separa a string s em tokens */
	tok = strtok(s, delimiters);
	while (tok != NULL) {
		strtoupper(tok);

		t.s = tok;
		conj_insere(c, (void*) &t, sizeof(Termo), Termo_cmp, Termo_copy);

		tok = strtok(NULL, delimiters);
	}

	return c;
}
