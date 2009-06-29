#include "definicoes.h"

void opcao3() {
	double **v1, **v2, **v3;
	double **vet;
	int n;

	v1 = le_matriz("bagOfWords.matrix", &n);
	v2 = le_matriz("cosseno.matrix", &n);
	v3 = le_matriz("okapi.matrix", &n);

	vet = calcula_media(v1, v2, v3, n);

	compara(vet, n);

	limpa_matrix(v1, n);
	limpa_matrix(v2, n);
	limpa_matrix(v3, n);
	limpa_matrix(vet, n);
}

/*
 * LEITURA DE MATRIZES
 * - Lê a matriz contida em file e armazena a dimensão em n
 */
double **le_matriz(char *file, int *n) {
	int i, j;
	FILE *fp;
	double **vet;
	fp = Fopen(file, "r");

	fscanf(fp, "%d", &(*n));
	vet = (double **) malloc((*n) * sizeof(double *));
	for (i = 0; i < (*n); i++) {
		vet[i] = (double *) malloc((*n) * sizeof(double));
		for (j = 0; j < (*n); j++)
			fscanf(fp, "%lf", &vet[i][j]);
	}
	fclose(fp);
	return vet;
}

/* CALCULA MEDIA
 * Dada 3 matrizes v1, v2 e v3 de dimensão n, calculamos a média delas
 * (média aritmética termo a termo) e devolvemos a matriz resultante
 */
double **calcula_media(double **v1, double **v2, double **v3, int n) {
	int i, j;
	double **vet;

	vet = (double **) malloc(n * sizeof(double *));
	for (i = 0; i < n; i++) {
		vet[i] = (double *) malloc(n * sizeof(double));
		for (j = 0; j < n; j++) {
			vet[i][j] = (v1[i][j] + v2[i][j] + v3[i][j]) / 3;
		}

	}
	return vet;

}

/*
 * Compara a matriz das medias
 * na linha n (arquivo n) teremos a distancia do
 * n ao m, quanto menor a distancia mais proximo ele eh
 */
void compara(double **vet, int n) {
	int i, j;
	int pos;
	int id;

	do {
		printf("Digite o identificador do arquivo (Max = %d Min = 0):\n", n - 1);
		scanf("%d", &id);
	} while (id >= n || id < 0);

	for (j = 0; j < n; j++) {
		pos = n-1;
		for (i = 0; i < n; i++)
			if (vet[id][i] < vet[id][j])
				pos--;

		printf("%d - %s\n", pos, FileNames[j]);
	}

	Pause();
}

/* LIMPA MATRIZ
 * Libera a memória que foi alocada dinamicamente
 */
void limpa_matrix(double **v, int n) {
	int i;

	for (i = 0; i < n; i++) {
		free(v[i]);
	}
	free(v);
}
