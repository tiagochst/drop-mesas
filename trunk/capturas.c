#include "definicoes.h"

/* CAPTURA BUSCA
 * busca captura de ID 'idC', e salva seu registro em 'K' ao
 * final da busca, o ponteiro no arquivo estará imediatamente
 * antes do começo do registro dessa captura */
int captura_busca(int idC, Captura *K) {
	int i, k, n, avail_list, save;
	Captura X;

	fseek(FCaptu, 0, SEEK_SET);
	fread(&n, sizeof(int), 1, FCaptu);
	fread(&avail_list, sizeof(int), 1, FCaptu);
	for (i=0, k=-1; i<n; i++) {
		save = (int)ftell(FCaptu);
		X = captura_read(FCaptu);

		if (X.idC == FAIL)
			i--;
		if (X.idC == idC) {
			k = i;
			break;
		}
	}

	if (k == -1)
		return FAIL;
	if (K != NULL)
		*K = X;

	fseek(FCaptu, save, SEEK_SET);
	return OK;
}

/* CAPTURA INSERE
 * lê os valores da entrada padrao e insere no arquivo
 * de tamanho fixo  */
void captura_insere(FILE *file_input) {
	int n, i;
	Captura X;

	fscanf(file_input, " %d", &n);
	for(i=0 ; i<n ; i++) {
		X = captura_read_(file_input);
		X.idC = i;
		if (indice_busca("individuo", X.idI) == FAIL) {
			fprintf(stderr, "ERRO [captura_insere]: O individuo associado nao existe.\n");
			return;
		}

		captura_insere_(X);
		indice_fail(SISecCaptu);
	}
}

/* CAPTURA INSERE 2
 * função mais baixo nível de inserção
 * - busca na lista ligada de buracos por um espaço
 * - adiciona a captura no índice secundário */
void captura_insere_(Captura X) {
	int pos;

	pos = buraco_fixo_busca_vazio(FCaptu);
	if (pos == FAIL) {
		fseek(FCaptu, 0, SEEK_END);
	} else {
		fseek(FCaptu, pos, SEEK_SET);
		buraco_fixo_remove(FCaptu);
	}

	indice_sec_insere("captura", X.idI, ftell(FCaptu));
	captura_write(FCaptu, &X);
	muda_n_bin(FCaptu, +1);
}

/* CAPTURA ATUALIZA
 * lê o ID da captura a ser atualizada e
 * modifica seus valores conforme digitado pelo usuário */
void captura_atualiza() {
	int idC;
	Captura X;

	system("clear");

	puts("** ATUALIZACAO CAPTURAS **");
	printf("Digite o ID da captura: ");
	scanf(" %d", &idC);

	if (captura_busca(idC, &X) == FAIL) {
		puts("Nao existe captura com este ID!\n");
		Pause();
	} else {
		printf("ID da captura: ");
		printf("%d\n", X.idC);
		printf("ID do individuo: ");
		printf("%d\n", X.idI);
		muda_int(&X.idI);
		printf("Comprimento: ");
		printf("%d\n", X.comprimento);
		muda_int(&X.comprimento);
		printf("Largura: ");
		printf("%d\n", X.largura);
		muda_int(&X.largura);
		printf("Peso: ");
		printf("%d\n", X.peso);
		muda_int(&X.peso);
		printf("Data de Captura: ");
		data_escreve(stdout, X.data);
		muda_Data(&X.data);
		printf("Local de Captura: ");
		printf("%s\n", X.local);
		muda_string(X.local);

		captura_write(FCaptu, &X);
	}
}

/* CAPTURA LÊ
 * lê todos os registros de captura e os imprime na tela */
void captura_le() {
	int n, avail_list;
	Captura aux;
	system("clear");

	puts("** LEITURA CAPTURAS **");
	printf("\n");

	fseek(FCaptu, 0, SEEK_SET);
	fread(&n, sizeof(int), 1, FCaptu);
	fread(&avail_list, sizeof(int), 1, FCaptu);
	while (n--) {
		aux = captura_read(FCaptu);
		if (aux.idC == FAIL)
			n++;
		else
			captura_write_(stdout, aux, 1);
	}

	Pause();
}

/* CAPTURA DELETA
 * deleta um registro de captura de ID dado pelo usuário */
void captura_deleta() {
	int idC;
	Captura X;

	system("clear");

	puts("** DELECAO CAPTURA **");
	printf("Digite o ID da captura a ser deletada: ");
	scanf(" %d", &idC);

	if (captura_busca(idC, &X) == FAIL) {
		puts("Nao existe captura com este ID!\n");
		Pause();
	} else {
		captura_write_(stdout, X, 1);
		if (!Pergunta("Confirma exclusao?"))
			return;

		indice_sec_deleta("captura", X.idI, ftell(FCaptu));
		buraco_fixo_insere(FCaptu, (int) ftell(FCaptu));
		muda_n_bin(FCaptu, -1);
		indice_fail(SISecCaptu);
	}
}

/* CAPTURA READ
 * lê de arquivo binário um único registro de captura */
Captura captura_read(FILE *fin) {
	Captura X;
	char c;

	fread(&c, sizeof(char), 1, fin);
	if (c == VAZIO) {
		fseek(fin, sizeof(Captura), SEEK_CUR);

		X.idC = FAIL;
		return X;
	}

	fread(&X, sizeof(Captura), 1, fin);
	return X;
}

/* CAPTURA READ 2
 * lê de arquivo txt ou do teclado
 * um único registro de captura */
Captura captura_read_(FILE *fin) {
	Captura X;
	char linha[500], *tok;

	fscanf(fin," %[^\n]", linha);

	/*
	tok = strtok(linha, "|");
	sscanf(tok, " %d", &X.idC);
	*/

	tok = strtok(NULL, "|");
	sscanf(tok, " %d", &X.idI);

	tok = strtok(NULL, "|");
	sscanf(tok, " %d", &X.comprimento);

	tok = strtok(NULL, "|");
	sscanf(tok, " %d", &X.largura);

	tok = strtok(NULL, "|");
	sscanf(tok, " %d", &X.peso);

	tok = strtok(NULL, "|");
	X.data = data_le_str(tok);

	tok = strtok(NULL, "|");
	sscanf(tok, " %s", X.local);

	return X;
}

/* CAPTURA WRITE
 * escreve em arquivo binário um único registro de captura */
void captura_write(FILE *fout, Captura *X) {
	char c = USADO;
	fwrite(&c, sizeof(char), 1, fout);
	fwrite(X, sizeof(Captura), 1, fout);
}

/* CAPTURA WRITE 2
 * escreve em arquivo txt ou na tela
 * um único registro de captura */
void captura_write_(FILE *fout, Captura X, int print) {
	if (print) printf("ID da Captura: ");
	fprintf(fout, "%d\n", X.idC);
	if (print) printf("ID do Individuo: ");
	fprintf(fout, "%d\n", X.idI);
	if (print) printf("Comprimento: ");
	fprintf(fout, "%d\n", X.comprimento);
	if (print) printf("Largura: ");
	fprintf(fout, "%d\n", X.largura);
	if (print) printf("Peso: ");
	fprintf(fout, "%d\n", X.peso);
	if (print) printf("Data de Captura: ");
	data_escreve(fout, X.data);
	if (print) printf("Local de Captura: ");
	fprintf(fout, "%s\n", X.local);

	if (print) printf("\n");
}
