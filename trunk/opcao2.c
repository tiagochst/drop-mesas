#include "definicoes.h"

void opcao2() {
	bagOfWords("bagOfWords.matrix");
	cosseno("cosseno.matrix");
}

void bagOfWords(char *file) {
	FILE *fp;
	int i, j;
	double val;
	Conjunto *inter;

	fp = Fopen(file, "w");
	if (fp == NULL)
		exit(1);

	fprintf(fp, "%d\n", NFile);
	for (i = 0; i < NFile; i++) {
		for (j = 0; j < NFile; j++) {
			if (i == j)
				val = 1.0;
			else {
				inter = conj_interseccao(FileWords[i], FileWords[j], strcmp_);
				val = (double) conj_size(inter) / (double) conj_size(FileWords[i]);
				conj_destroy(inter);
			}

			fprintf(fp, "%.1lf ", val);
		}
		fprintf(fp, "\n");
	}
}

void cosseno(char *file) {
	FILE *fp;
	int i, j, t1, t2, t3;
	double val;

	fp = Fopen(file, "w");
	if (fp == NULL)
		exit(1);

	fprintf(fp, "%d\n", NFile);
	for (i = 0; i < NFile; i++) {
		for (j = 0; j < NFile; j++) {
			if (i == j)
				val = 1.0;
			else {
				t1 = conj_prod_escalar(FileWords[i], FileWords[j], strcmp_);
				t2 = conj_prod_escalar(FileWords[i], FileWords[i], strcmp_);
				t3 = conj_prod_escalar(FileWords[j], FileWords[j], strcmp_);
				val = (double) t1 / sqrt((double) (t2 * t3));
			}

			fprintf(fp, "%.1lf ", val);
		}
		fprintf(fp, "\n");
	}
}
