#include "definicoes.h"
#include <sys/time.h>
#include <time.h>
#include <sys/timeb.h>

void le_dados(char **arg) {
	int i;
	FILE *file_input[3];

	for (i = 0; i < 3; i++) {

		file_input[i] = fopen(arg[i + 1], "r");

		if (file_input[i] == NULL) {
			fprintf(stderr,
					"ERRO [main]: Nao foi possivel abrir um dos arquivos de input.");
			return;
		}
	}
	especie_insere_lab3(file_input[0]);
	individuo_insere_lab3(file_input[1]);
	captura_insere_lab3(file_input[2]);

	for (i = 0; i < 3; i++)
		fclose(file_input[i]);

	printf("Leitura efetuada com sucesso!\n");
}

typedef void (*funcao_consulta)(int);

double executa(funcao_consulta F, Indice_Prim *indice, int n_indice, int N,	int M) {
	int i, j;
	struct timeb time_start, time_end;

	ftime(&time_start);

	for (j = 0; j < N; j++)
		for (i = 0; i < n_indice; i++)
			F(indice[i].id);
	for (i = 0; i < M; i++)
		F(indice[i].id);

	ftime(&time_end);

	return ((double) time_end.time * 1000.0 + (double) time_end.millitm)
			- ((double) time_start.time * 1000.0 + (double) time_start.millitm);
}

void compara_tempo() {
	int i;
	char c;
	int k, n1, n2, m1, m2;
	double t1[4], t2[4];

	printf("Digite a quantidade de consultas a realizar:\n");
	scanf(" %d", &k);

	n1 = k / N_IPIndiv;
	n2 = k / N_IPEspec;
	m1 = k % N_IPIndiv;
	m2 = k % N_IPEspec;

	/* EXECUTA A CONSULTA A */
	t1[0] = executa((funcao_consulta)historico_monitoramento_lab1, IPIndiv, N_IPIndiv, n1, m1);
	t2[0] = executa((funcao_consulta)historico_monitoramento_lab2, IPIndiv, N_IPIndiv, n1, m1);

	/* EXECUTA A CONSULTA B */
	t1[1] = executa((funcao_consulta)ultima_captura_lab1, IPIndiv, N_IPIndiv, n1, m1);
	t2[1] = executa((funcao_consulta)ultima_captura_lab2, IPIndiv, N_IPIndiv, n1, m1);

	/* EXECUTA A CONSULTA C */
	t1[2] = executa((funcao_consulta)ultima_captura_peso_lab1, IPEspec, N_IPEspec, n2, m2);
	t2[2] = executa((funcao_consulta)ultima_captura_peso_lab2, IPEspec, N_IPEspec, n2, m2);

	/* EXECUTA A CONSULTA D */
	t1[3] = executa((funcao_consulta)caminho_especie_lab1, IPIndiv, N_IPIndiv, n1, m1);
	t2[3] = executa((funcao_consulta)caminho_especie_lab2, IPIndiv, N_IPIndiv, n1, m1);

	printf("Consulta   Tempo Lab1(ms)   Tempo Lab2(ms)   Reducao\n");
	for (i=0,c='a'; i<4; i++,c++) {
		printf("4.%c        %-17.0lf%-17.0lf%.2lf%%\n", c, t1[i], t2[i],
				100.0 * ((t1[i] - t2[i]) / t1[i]));
	}

	putchar('\n');
	Pause();
}
