#ifndef LISTA_BURACO_FIXO_H_
#define LISTA_BURACO_FIXO_H_

typedef struct {
	int next;
} BuracoFixo;

void buraco_fixo_escreve(FILE *fp, BuracoFixo *X);
int buraco_fixo_le(FILE *fp, BuracoFixo *X);
int buraco_fixo_busca_vazio(FILE *fp);
void buraco_fixo_insere(FILE *fp, int pos);
void buraco_fixo_remove(FILE *fp);

#endif /* LISTA_BURACO_FIXO_H_ */
