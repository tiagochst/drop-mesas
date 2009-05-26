#include "definicoes.h"

char *delimiters = " .,;:!?()[]{}<>'\"\t\\/";

ListaInv_Prim *LIPrim;
ListaInv_Sec *LISec;
int N_LIPrim;
int N_LISec;
int avail_list_LIPrim;
char flag_atualizado;

Conjunto *strtokenizer(char *s);
void set_flag_atualizado_OK();
void set_flag_atualizado_FAIL();
void lista_inv_rebuild();
void lista_inv_reset(char *prim, char *sec);

/* LISTA INVERTIDA START
 * carrega a lista invertida do arquivo ou
 * a reconstrói caso o arquivo esteja desatualizado */
void lista_inv_start(char *prim, char *sec) {
	FInvPrim = fopen(prim, "rb");
	FInvSec = fopen(sec, "rb");
	LIPrim = NULL;
	LISec = NULL;
	avail_list_LIPrim = FAIL;
	flag_atualizado = OK;

	N_LIPrim = 0;
	if (FInvPrim != NULL) {
		fread(&flag_atualizado, sizeof(char), 1, FInvPrim);
		fread(&N_LIPrim, sizeof(int), 1, FInvPrim);
		fread(&avail_list_LIPrim, sizeof(int), 1, FInvPrim);

		if (flag_atualizado == FAIL) {
			fclose(FInvPrim);
			lista_inv_reset(prim, sec);
			lista_inv_rebuild();
			return;
		}

		LIPrim = (ListaInv_Prim *) malloc(N_LIPrim * sizeof(ListaInv_Prim));
		fread(LIPrim, sizeof(ListaInv_Prim), N_LIPrim, FInvPrim);

		fclose(FInvPrim);
		FInvPrim = fopen(prim, "rb+");
	} else
		FInvPrim = fopen(prim, "wb");

	N_LISec = 0;
	if (FInvSec != NULL) {
		fread(&N_LISec, sizeof(int), 1, FInvSec);

		LISec = (ListaInv_Sec *) malloc(N_LISec * sizeof(ListaInv_Sec));
		fread(LISec, sizeof(ListaInv_Sec), N_LISec, FInvSec);

		fclose(FInvSec);
		FInvSec = fopen(sec, "rb+");
	} else
		FInvSec = fopen(sec, "wb");
}

/* LISTA INVERTIDA END
 * finaliza a lista invertida, reescrevendo no arquivo */
void lista_inv_end() {
	lista_inv_write();

	free(LIPrim);
	free(LISec);

	fclose(FInvPrim);
	fclose(FInvSec);
}

/* LISTA INVERTIDA WRITE
 * escreve a lista invertida no arquivo */
void lista_inv_write() {
	if (flag_atualizado == OK)
		return;

	fseek(FInvPrim, 0, SEEK_SET);
	fseek(FInvSec, 0, SEEK_SET);

	fwrite(&flag_atualizado, sizeof(char), 1, FInvPrim);
	fwrite(&N_LIPrim, sizeof(int), 1, FInvPrim);
	fwrite(&avail_list_LIPrim, sizeof(int), 1, FInvPrim);
	fwrite(LIPrim, sizeof(ListaInv_Prim), N_LIPrim, FInvPrim);

	fwrite(&N_LISec, sizeof(int), 1, FInvSec);
	fwrite(LISec, sizeof(ListaInv_Sec), N_LISec, FInvSec);

	set_flag_atualizado_OK();
}

/* LISTA INVERTIDA INSERE
 * dada a descrição e o ID de certa espécie, adiciona
 * na lista invertida cada palavra, relacionando-a com
 * o ID da espécie
 * - esta função só quebra o texto em palavras e chama
 * função auxiliar para inserir cada palavra separadamente */
void lista_inv_insere(char *s, int id) {
	Conjunto *c, *i;

	set_flag_atualizado_FAIL();

	c = strtokenizer(s);

	for (i = c->next; i != NULL; i = i->next)
		lista_inv_insere_((char*) i->i, id);

	conj_destroy(c);
}

/* LISTA INVERTIDA INSERE 2
 * insere uma única palavra na lista invertida, relacionando-a
 * com o ID dado */
int lista_inv_insere_(char *s, int id) {
	int aux, k;

	k = lista_inv_Sec_busca(s);
	if (k != FAIL)
		k = LISec[k].ind1;

	if ((aux = lista_inv_Prim_insere(k, id)) == FAIL)
		return FAIL;

	if (k == FAIL)
		if (lista_inv_Sec_insere(s, aux) == FAIL)
			return FAIL;

	return OK;
}

/* LISTA INVERTIDA BUSCA
 * executa busca textual na descrição das espécies
 * - separa o texto em palavras, executa uma busca para cada palavra
 * independentemente, e finalmente faz intersecção dos resultados */
void lista_inv_busca(char *s) {
	Conjunto *c, *ans = conj_init(), *i, *aux, *inter;
	int k, j;

	/* insere em 'ans' todos IDs de especies */
	for (j = 0; j < N_IPEspec; j++) {
		conj_insere(ans, (void*) (&IPEspec[j].id), sizeof(int), intcmp_);
	}

	c = strtokenizer(s);

	for (i = c->next; i != NULL && !conj_vazio(ans); i = i->next) {
		k = lista_inv_Sec_busca((char*) i->i);
		if (k != FAIL)
			k = LISec[k].ind1;

		/* gera lista de IDs relacionados */
		aux = conj_init();
		while (k != FAIL) {
			if (indice_busca("especie", LIPrim[k].idE) == FAIL) {
				/* no caso da espécie ter sido apagada, devemos atualizar a lista invertida */
				j = LIPrim[k].next;
				lista_inv_deleta_((char*) i->i, LIPrim[k].idE);
				k = j;
				continue;
			}
			conj_insere(aux, (void*) (&LIPrim[k].idE), sizeof(int), intcmp_);
			k = LIPrim[k].next;
		}

		inter = conj_interseccao(ans, aux, intcmp_);
		conj_destroy(ans);
		conj_destroy(aux);
		ans = inter;
	}

	/* itera em 'ans' escrevendo os resultados da busca */
	printf("Há %d espécie(s) correspondente(s) à busca:\n", conj_size(ans));
	for (i = ans->next; i != NULL; i = i->next) {
		printf("> %d\n", *(int*) i->i);
	}
	putchar('\n');
	Pause();

	conj_destroy(ans);
	conj_destroy(c);
}

/* LISTA INVERTIDA Secundária BUSCA
 * executa uma busca por palavra */
int lista_inv_Sec_busca(char *s) {
	/* uma busca binária */
	int esq = 0, dir = N_LISec - 1, meio, cmp;

	while (esq <= dir) {
		meio = (esq + dir) / 2;
		cmp = strcmp(LISec[meio].s, s);
		if (cmp == 0)
			return meio;
		if (cmp > 0)
			dir = meio - 1;
		else
			esq = meio + 1;
	}

	return FAIL;
}

/* LISTA INVERTIDA Primária INSERE */
int lista_inv_Prim_insere(int k, int id) {
	int pos;
	ListaInv_Prim *aux;

	if (avail_list_LIPrim == FAIL) {
		/* nao tem buraco, dar realloc no LIPrim */
		aux = (ListaInv_Prim*) realloc(LIPrim, (N_LIPrim + 1)
				* sizeof(ListaInv_Prim));
		if (aux == NULL)
			return FAIL;
		LIPrim = aux;

		pos = N_LIPrim++;
	} else {
		pos = avail_list_LIPrim;
		avail_list_LIPrim = LIPrim[pos].next;
	}

	LIPrim[pos].idE = id;
	if (k == FAIL) {
		/* insere um novo */
		LIPrim[pos].next = -1;
	} else {
		/* basta alterar a lista ligada */
		LIPrim[pos].next = LIPrim[k].next;
		LIPrim[k].next = pos;

		pos = k;
	}

	/* e devolve a posição do começo da lista ligada */
	return pos;
}

/* LISTA INVERTIDA Secundária INSERE */
int lista_inv_Sec_insere(char *s, int ind1) {
	int i;
	ListaInv_Sec *aux = (ListaInv_Sec *) realloc(LISec, (N_LISec + 1)
			* sizeof(ListaInv_Sec));
	if (aux == NULL)
		return FAIL;

	LISec = aux;
	N_LISec++;

	for (i=N_LISec-1; i>0 && strcmp(s, LISec[i-1].s)<0; i--) {
		LISec[i] = LISec[i - 1];
	}
	strcpy(LISec[i].s, s);
	LISec[i].ind1 = ind1;

	return OK;
}

/* LISTA INVERTIDA ATUALIZA */
/* rotina chamada quando há atualização em espécie */
void lista_inv_atualiza(char *velho, char *novo, int id) {
	Conjunto *cvelho, *cnovo, *difer, *i;

	set_flag_atualizado_FAIL();

	cvelho = strtokenizer(velho);
	cnovo = strtokenizer(novo);

	/* removemos as palavras pertencentes a cvelho-cnovo
	 * e adicionamos as palavras de cnovo-cvelho */
	difer = conj_diferenca(cvelho, cnovo, strcmp_);
	for (i = difer->next; i != NULL; i = i->next)
		lista_inv_deleta_((char *) i->i, id);
	conj_destroy(difer);

	difer = conj_diferenca(cnovo, cvelho, strcmp_);
	for (i = difer->next; i != NULL; i = i->next)
		lista_inv_insere_((char *) i->i, id);
	conj_destroy(difer);

	conj_destroy(cvelho);
	conj_destroy(cnovo);
}

/* LISTA INVERTIDA DELETA */
/* esta rotina não é utilizada: quando uma espécie
 * é removida, a remoção na lista invertida só é
 * efetuada durante a busca */
void lista_inv_deleta(char *s, int id) {
	Conjunto *c, *i;

	set_flag_atualizado_FAIL();

	c = strtokenizer(s);

	for (i = c->next; i != NULL; i = i->next)
		lista_inv_deleta_((char *) i->i, id);

	conj_destroy(c);
}

/* LISTA INVERTIDA DELETA 2
 * deleção de apenas um registro na lista invertida
 * - remoção da palavra 's', relacionada ao ID de espécie 'id' */
void lista_inv_deleta_(char *s, int id) {
	int k = lista_inv_Sec_busca(s);

	set_flag_atualizado_FAIL();

	lista_inv_Prim_deleta(&LISec[k].ind1, id);

	if (LISec[k].ind1 == FAIL) {
		/* se todos os registros para essa palavra
		 * foram apagados da LIPrim */
		for (; k < N_LISec - 1; k++)
			LISec[k] = LISec[k + 1];
		N_LISec--;
	}
}

/* LISTA INVERTIDA Primária DELETA */
void lista_inv_Prim_deleta(int *k, int id) {
	int save;
	for (; LIPrim[*k].idE != id; k = &LIPrim[*k].next);

	save = LIPrim[*k].next;
	LIPrim[*k].next = avail_list_LIPrim;
	avail_list_LIPrim = *k;

	*k = save;
}

/* STRING TOKENIZER */
/* divide a string dada em palavras, montando
 * e devolvendo um conjunto das palavras */
Conjunto *strtokenizer(char *s) {
	Conjunto *c = conj_init();
	char *tok;

	/* separa a string s em tokens */
	tok = strtok(s, delimiters);
	while (tok != NULL) {
		strtoupper(tok);
		conj_insere(c, (void*) tok, (strlen(tok) + 1) * sizeof(char), strcmp_);
		tok = strtok(NULL, delimiters);
	}

	return c;
}

/* SET FLAG ATUALIZADO = OK */
void set_flag_atualizado_OK() {
	if (flag_atualizado == OK)
		return;

	flag_atualizado = OK;
	fseek(FInvPrim, 0, SEEK_SET);
	fwrite(&flag_atualizado, sizeof(char), 1, FInvPrim);

	fflush(FInvPrim);
}

/* SET FLAG ATUALIZADO = FAIL */
void set_flag_atualizado_FAIL() {
	if (flag_atualizado == FAIL)
		return;

	flag_atualizado = FAIL;
	fseek(FInvPrim, 0, SEEK_SET);
	fwrite(&flag_atualizado, sizeof(char), 1, FInvPrim);

	fflush(FInvPrim);
}

/* LISTA INVERTIDA REBUILD */
/* reconstrução da lista invertida em caso de
 * interrupção do programa */
void lista_inv_rebuild() {
	int i;
	Especie X;

	for (i = 0; i < N_IPEspec; i++) {
		fseek(FEspec, IPEspec[i].offset, SEEK_SET);
		X = especie_read(FEspec, NULL, NULL);
		lista_inv_insere(X.descr, X.id);
	}

	lista_inv_write();
}

/* LISTA INVERTIDA RESET
 * destrói os arquivos da lista invertida */
void lista_inv_reset(char *prim, char *sec) {
	FInvPrim = fopen(prim, "wb");
	FInvSec = fopen(sec, "wb");

	flag_atualizado = OK; /* para forcar set_flag_atualizado_FAIL() a executar */
	set_flag_atualizado_FAIL();
}
