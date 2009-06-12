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
		fprintf(stderr, "ERRO [Fopen]: Erro ao abrir arquivo <%s>.\n", file);
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
	FileWords = (Conjunto **) malloc(NFile * sizeof(Conjunto*));

	for (i = 0; i < NFile; i++) {
		fscanf(fp, " %a[^\r\n]", &FileNames[i]);

		File[i] = Fopen(FileNames[i], "r");
		if (File[i] == NULL)
			exit(1);

		files_start_read(File[i], &FileWords[i]);
	}

	fclose(fp);
	free(nome_arq);
}

void files_start_read(FILE *fp, Conjunto **c) {
	Conjunto *aux, *uniao;
	char *s;

	*c = conj_init();
	while(fscanf(fp, " %a[^\r\n]", &s) == 1) {
		aux = strtokenizer(s);
		uniao = conj_uniao(*c, aux, strcmp_, 0);

		conj_destroy(*c);
		conj_destroy(aux);
		free(s);

		*c = uniao;
	}
}

void files_end() {
	int i;
	for (i = 0; i < NFile; i++) {
		free(FileNames[i]);
		fclose(File[i]);
		conj_destroy(FileWords[i]);
	}
	free(FileNames);
	free(File);
	free(FileWords);
}

void strtoupper(char *s) {
	for (; *s != '\0'; s++)
		*s = toupper(*s);
}

int strcmp_(void *a, void *b) {
	return strcmp((char*) a, (char*) b);
}

/* STRING TOKENIZER */
/* divide a string dada em palavras, montando
 * e devolvendo um conjunto das palavras */
Conjunto *strtokenizer(char *s) {
	Conjunto *c = conj_init();
	char *tok;
	char *delimiters = "_ .,;:!?()[]{}<>'\"\t\\/";

	/* separa a string s em tokens */
	tok = strtok(s, delimiters);
	while (tok != NULL) {
		strtoupper(tok);
		conj_insere(c, (void*) tok, (strlen(tok) + 1) * sizeof(char), strcmp_);
		tok = strtok(NULL, delimiters);
	}

	return c;
}
