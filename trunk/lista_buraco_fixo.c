#include "definicoes.h"

int get_avail_list(FILE *fp);
void set_avail_list(FILE *fp, int avail_list);

void buraco_fixo_escreve(FILE *fp, BuracoFixo *X) {
	char c = VAZIO;

	fwrite(&c, sizeof(char), 1, fp);
	fwrite(X, sizeof(int), 1, fp);
}

int buraco_fixo_le(FILE *fp, BuracoFixo *X) {
	if (fread(X, sizeof(BuracoFixo), 1, fp) == 1)
		return OK;
	return FAIL;
}

void buraco_fixo_insere(FILE *fp, int pos) {
	BuracoFixo X;

	X.next = get_avail_list(fp);
	set_avail_list(fp, pos);

	fseek(fp, pos, SEEK_SET);
	buraco_fixo_escreve(fp, &X);
}

int buraco_fixo_busca_vazio(FILE *fp) {
	return get_avail_list(fp);
}

void buraco_fixo_remove(FILE *fp) {
	int save = (int)ftell(fp);
	char c;
	BuracoFixo X;

	fread(&c, sizeof(char), 1, fp);
	buraco_fixo_le(fp, &X);

	set_avail_list(fp, X.next);
	fseek(fp, save, SEEK_SET);
}

int get_avail_list(FILE *fp) {
	int avail_list;
	fseek(fp, sizeof(int), SEEK_SET);
	fread(&avail_list, sizeof(int), 1, fp);
	return avail_list;
}

void set_avail_list(FILE *fp, int avail_list) {
	fseek(fp, sizeof(int), SEEK_SET);
	fwrite(&avail_list, sizeof(int), 1, fp);
}
