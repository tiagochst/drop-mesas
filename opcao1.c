#include "definicoes.h"

void opcao1() {
	char *nome_arq, *arq;
	int i, n;
	FILE *fp;

	puts("Digite o nome do arquivo:");
	scanf(" %as", &nome_arq);

	fp = fopen(nome_arq, "r");
	if (fp == NULL)
		exit(1);

	fscanf(fp, " %d", &n);
	for (i=0; i<n; i++) {
		fscanf(fp, " %a[^\n]", &arq);
		gera_vetor(arq);
		free(arq);
	}

	fclose(fp);
	free(nome_arq);
}

void gera_vetor(char *arq) {
	int len;
	char *arq_vet;

	len = strlen(arq)+1;
	arq_vet = (char *) malloc(len * sizeof(char));
	strcpy(arq_vet, arq);
	arq_vet[len-4] = 'v';
	arq_vet[len-3] = 'e';
	arq_vet[len-2] = 't';

	puts(arq_vet);
	free(arq_vet);
}
