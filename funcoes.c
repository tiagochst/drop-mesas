#include "definicoes.h"
#include "menu.h"

int print_menu() {
	int in;

	CLEAR_SCREEN();

	PRINT_YELLOW("***********************************\n");
	PRINT_YELLOW("*     Entre com sua opção:        *\n");
	PRINT_YELLOW("***********************************\n");
	PRINT_WALLS(" 1. gerar representação vetorial ");
	PRINT_WALLS(" 2. gerar matriz de distâncias   ");
	PRINT_WALLS(" 3. consultar                    ");
	PRINT_YELLOW("*                                 *\n");
	PRINT_WALLS_BLUE(" 0. sair do programa             ");
	PRINT_YELLOW("***********************************\n");

	while (scanf(" %d", &in) != 1 || in < 0 || in > 3) {
		BLINK_RED("Entrada incorreta. Digite novamente");
		__fpurge(stdin);
	}
	return in;
}

void Pause() {
	char c;
	puts("Pressione (q) para continuar. . .");
	while (scanf("%c", &c) == 1 && tolower(c) != 'q');
}

/* supõe que as extensões nova e antiga tenham mesmo tamanho */
char* muda_ext(char *file, char *nova_ext) {
	int i, j, len = strlen(file);

	char *novo = (char *) malloc((len + 1) * sizeof(char));
	strcpy(novo, file);

	for (i = len; i - 1 && novo[i - 1] != '.'; i--);
	for (j = i; j < len - 1; j++)
		novo[j] = nova_ext[j - i];

	return novo;
}

FILE* Fopen(char *file, char *modo) {
	FILE *fp = fopen(file, modo);
	if (fp == NULL) {
		fprintf(stderr, "[ERRO - Fopen] Arquivo <%s> não existe.\n", file);
	}

	return fp;
}

void files_start() {
	char *nome_arq;
	int i;
	FILE *fp;

	puts("Digite o nome do arquivo:");
	scanf(" %as", &nome_arq);

	fp = Fopen(nome_arq, "r");
	if (fp == NULL)
		exit(1);

	fscanf(fp, " %d", &NFile);
	FileNames = (char**) malloc(NFile * sizeof(char*));
	File = (FILE**) malloc(NFile * sizeof(FILE*));

	for (i = 0; i < NFile; i++) {
		fscanf(fp, " %a[^\n]", &FileNames[i]);

		File[i] = Fopen(FileNames[i], "r");
		if (File[i] == NULL)
			exit(1);
	}

	fclose(fp);
	free(nome_arq);
}

void files_end() {
	int i;
	for (i = 0; i < NFile; i++) {
		free(FileNames[i]);
		fclose(File[i]);
	}
	free(FileNames);
	free(File);
}
