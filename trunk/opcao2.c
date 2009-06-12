#include "definicoes.h"

void opcao2() {
	bagOfWords("bagOfWords.matrix");
	cosseno("cosseno.matrix");
	okapi("okapi.matrix");
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
			inter = conj_interseccao(FileWords[i], FileWords[j], strcmp_);
			val = (double) conj_size(inter) / (double) conj_size(FileWords[i]);
			conj_destroy(inter);

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
			t1 = conj_prod_escalar(FileWords[i], FileWords[j], strcmp_);
			t2 = conj_prod_escalar(FileWords[i], FileWords[i], strcmp_);
			t3 = conj_prod_escalar(FileWords[j], FileWords[j], strcmp_);
			val = (double) t1 / sqrt((double) (t2 * t3));

			fprintf(fp, "%.1lf ", val);
		}
		fprintf(fp, "\n");
	}
}

void okapi(char *file) {
	FILE *fp;
	int i, j, total_sz;
	double tammed, val, t1, t2, t3, *matrix;
	Conjunto *colecao, *inter, *uniao, *k, *d1, *d2, *q;

	fp = Fopen(file, "w");
	if (fp == NULL)
		exit(1);

	fprintf(fp, "%d\n", NFile);

	total_sz = 0;
	colecao = conj_init();
	for (i = 0; i < NFile; i++) {
		total_sz += conj_size_bytes(FileWords[i]);
		uniao = conj_uniao(colecao, FileWords[i], strcmp_, 1);
		conj_destroy(colecao);
		colecao = uniao;
	}
	tammed = (double) total_sz / (double) NFile;

	matrix = (double*) malloc(NFile * NFile * sizeof(double *));
	for (i = 0; i < NFile; i++) {
		for (j = 0; j < NFile; j++) {
			inter = conj_interseccao(FileWords[i], FileWords[j], strcmp_);

			val = 0.0;
			q = colecao->next;
			d1 = FileWords[i]->next;
			d2 = FileWords[j]->next;
			for (k = inter->next; k != NULL; k = k->next) {
				/* busca o elemento k->i nos conjuntos */
				for (; strcmp_(q->i, k->i) != 0; q = q->next);
				for (; strcmp_(d1->i, k->i) != 0; d1 = d1->next);
				for (; strcmp_(d2->i, k->i) != 0; d2 = d2->next);

				t1 = (3 + d2->freq) / (0.5 + 1.5 * (conj_size_bytes(d2) / tammed) + d2->freq);
				t2 = (NFile - q->freq + 0.5) / (q->freq + 0.5);
				t3 = d1->freq;

				val += t1 * log10(t2) * t3;
			}
			conj_destroy(inter);

			matrix[i*NFile + j] = val;
		}
	}

	normaliza_gauss(matrix, NFile*NFile);

	for (i = 0; i < NFile; i++) {
		for (j = 0; j < NFile; j++)
			fprintf(fp, "%.1lf ", matrix[i*NFile + j]);
		fprintf(fp, "\n");
	}
}

void normaliza_gauss(double *data, int N) {
	int i;
	double soma, media, desvio, xnorm, t;

	soma = 0.0;
	for (i = 0; i < N; i++)
		soma += data[i];
	media = soma / (double) N;

	t = 0.0;
	for (i = 0; i < N; i++)
		t += (media - data[i]) * (media - data[i]);
	desvio = sqrt(t / (N - 1));

	for (i = 0; i < N; i++) {
		xnorm = (((data[i] - media) / (3.0 * desvio)) + 1.0) / 2.0;

		if(xnorm > 1) {
			data[i] = 1.0;
		} else if(xnorm < 0) {
			data[i] = 0.0;
		} else {
			data[i] = xnorm;
		}
	}
}