#include "definicoes.h"

void opcao2() {
	bagOfWords("bagOfWords.matrix");
	cosseno("cosseno.matrix");
}

void bagOfWords(char *file) {
	FILE *fp;
	int i,j;
	double val;

	fp = Fopen(file, "w");
	if(fp == NULL)
		exit(1);

	for(i=0 ; i<NFile ; i++) {
		for(j=0 ; j<=i ; j++) {
			if(i == j) val = 0.0;
			else {
			}

			fprintf(fp, "%.1lf ", val);
		}
		fprintf(fp, "\n");
	}
}

void cosseno(char *file) {
}
