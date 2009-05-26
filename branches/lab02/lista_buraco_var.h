#ifndef LISTA_BURACO_VAR_H_
#define LISTA_BURACO_VAR_H_

typedef struct {
	int sz, prev, next;
} BuracoVar;

void buraco_var_escreve(FILE *fp, int sz, int prev, int next);
int buraco_var_le(FILE *fp, BuracoVar *x);
int buraco_var_busca_vazio(FILE *fp, int sz);
int buraco_var_insere(FILE *fp, int sz, int pos);
void buraco_var_remove(FILE *fp);

#endif /* LISTA_BURACO_VAR_H_ */
