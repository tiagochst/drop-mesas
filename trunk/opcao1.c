#include "definicoes.h"

Conjunto *colecao_sem_freq;

void colecao_gera();
void colecao_destroy();

void opcao1() {
	int i;

	colecao_gera();
	for (i = 0; i < NFile; i++) {
		tfIdf(i, muda_ext(FileNames[i], "vet"));
	}
	colecao_destroy();
}

void colecao_gera() {
	int i;
	Conjunto *uniao;

	colecao_sem_freq = conj_init();
	for (i = 0; i < NFile; i++) {
		uniao = conj_uniao(colecao_sem_freq, FileWords[i], Termo_cmp, Termo_copy, 1);
		conj_destroy(colecao_sem_freq, Termo_free);
		colecao_sem_freq = uniao;
	}
}

void colecao_destroy() {
	conj_destroy(colecao_sem_freq, Termo_free);
}

void tfIdf(int k, char *arq_vet) {
	int conj_sz;
	Conjunto *d, *q;
	double tf, idf, tfidf;

	FILE *fp = Fopen(arq_vet, "w");
	if (fp == NULL)
		exit(1);

	conj_sz = conj_size_freq(FileWords[k]);
	q = colecao_sem_freq->next;
	d = FileWords[k]->next;
	for (; q != NULL; q = q->next) {
		for (; d != NULL && Termo_cmp(d->i, q->i) < 0; d = d->next);

		/* tf */
		if (d != NULL && Termo_cmp(d->i, q->i) == 0) {
			tf = (double) d->freq / (double) conj_sz;

			/* idf */
			idf = log10( (double) NFile / (double) q->freq );

			/* td-idf */
			tfidf = tf * idf;
			((Termo*) d->i)->peso = tfidf;

			/* imprimindo vetor no arquivo */
			fprintf(fp, "%s ", ((Termo*) d->i)->s);
			fprintf(fp, print_double, tfidf);
			fprintf(fp, "\n");
		} else {
			tfidf = 0.0;
		}
	}

	fclose(fp);
	free(arq_vet);
}
