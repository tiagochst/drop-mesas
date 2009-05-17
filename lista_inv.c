#include "definicoes.h"

char *delimiters = " .,;:!?()[]{}<>'\"\t\\/";

ListaInv_Prim *LIPrim;
ListaInv_Sec *LISec;
int N_LIPrim;
int N_LISec;
int avail_list_LIPrim;

conjunto *strtokenizer(char *s);

void debug() {
	int i;
	for (i = 0; i < N_LISec; i++)
		printf("LISec[%d] = {%s, %d}\n", i, LISec[i].s, LISec[i].ind1);
	putchar('\n');

	for (i = 0; i < N_LIPrim; i++)
		printf("LIPrim[%d] = {%d, %d}\n", i, LIPrim[i].idE, LIPrim[i].next);
	putchar('\n');

	Pause();
}

void lista_inv_start(char *prim, char *sec) {
	FInvPrim = fopen(prim, "rb");
	FInvSec = fopen(sec, "rb");
	LIPrim = NULL;
	LISec = NULL;
	avail_list_LIPrim = FAIL;

	N_LIPrim = 0;
	if (FInvPrim != NULL) {
		fread(&N_LIPrim, sizeof(int), 1, FInvPrim);
		fread(&avail_list_LIPrim, sizeof(int), 1, FInvPrim);

		LIPrim = (ListaInv_Prim *) malloc(N_LIPrim*sizeof(ListaInv_Prim));
		fread(LIPrim, sizeof(ListaInv_Prim), N_LIPrim, FInvPrim);

		fclose(FInvPrim);
	}

	N_LISec = 0;
	if (FInvSec != NULL) {
		fread(&N_LISec, sizeof(int), 1, FInvSec);

		LISec = (ListaInv_Sec *) malloc(N_LISec*sizeof(ListaInv_Sec));
		fread(LISec, sizeof(ListaInv_Sec), N_LISec, FInvSec);

		fclose(FInvSec);
	}

	/*debug();*/
}

void lista_inv_end(char *prim, char *sec) {
	FInvPrim = fopen(prim, "wb");
	FInvSec = fopen(sec, "wb");

	fwrite(&N_LIPrim, sizeof(int), 1, FInvPrim);
	fwrite(&avail_list_LIPrim, sizeof(int), 1, FInvPrim);
	fwrite(LIPrim, sizeof(ListaInv_Prim), N_LIPrim, FInvPrim);

	fwrite(&N_LISec, sizeof(int), 1, FInvSec);
	fwrite(LISec, sizeof(ListaInv_Sec), N_LISec, FInvSec);

	free(LIPrim);
	free(LISec);

	fclose(FInvPrim);
	fclose(FInvSec);
}

void lista_inv_insere(char *s, int id) {
	conjunto *c, *i;

	c = strtokenizer(s);

	for (i=c->next; i!=NULL; i=i->next)
		lista_inv_insere_((char*)i->i, id);

	conj_destroy(c);
}

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

void lista_inv_busca(char *s) {
	conjunto *c, *ans = conj_init(), *i, *aux, *inter;
	int k, j;

	/* insere em 'ans' todos IDs de especies */
	for (j=0; j<N_IEspec; j++) {
		conj_insere(ans, (void*)(&IEspec[j].id), sizeof(int), intcmp_);
	}

	c = strtokenizer(s);

	for (i=c->next; i!=NULL; i=i->next) {
		k = lista_inv_Sec_busca((char*) i->i);
		if (k != FAIL)
			k = LISec[k].ind1;

		/* gera lista de IDs relacionados */
		aux = conj_init();
		while (k != FAIL) {
			/*if(especie_busca(LIPrim[k].idE, NULL) == FAIL) {
				/\* no caso da espécie ter sido apagada, devemos atualizar a lista invertida *\/
				lista_inv_deleta_((char*) i->i, LIPrim[k].idE);
			}*/
			conj_insere(aux, (void*)(&LIPrim[k].idE), sizeof(int), intcmp_);
			k = LIPrim[k].next;
		}

		inter = conj_interseccao(ans, aux, intcmp_);
		conj_destroy(ans);
		conj_destroy(aux);
		ans = inter;
	}

	/* itera em 'ans' fazendo algo */
	puts("Espécies correspondentes à busca:");
	for (i=ans->next; i!=NULL; i=i->next) {
		printf("<%d>\n", *(int*)i->i);
	}
	Pause();

	conj_destroy(ans);
	conj_destroy(c);
}

int lista_inv_Sec_busca(char *s) {
	/* uma busca binária */
	int esq=0, dir=N_LISec-1, meio, cmp;

	while (esq <= dir) {
		meio = (esq+dir)/2;
		cmp = strcmp(LISec[meio].s, s);
		if (cmp == 0)
			return meio;
		if (cmp > 0)
			dir = meio-1;
		else
			esq = meio+1;
	}

	return FAIL;
}

int lista_inv_Prim_insere(int k, int id) {
	int pos;
	ListaInv_Prim *aux;

	if (avail_list_LIPrim == FAIL) {
		/* nao tem buraco, dar realloc no LIPrim */
		aux = (ListaInv_Prim*) realloc(LIPrim, (N_LIPrim+1)
				*sizeof(ListaInv_Prim));
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

int lista_inv_Sec_insere(char *s, int ind1) {
	int i;
	ListaInv_Sec *aux = (ListaInv_Sec *) realloc(LISec, (N_LISec+1)
			*sizeof(ListaInv_Sec));
	if (aux == NULL)
		return FAIL;

	LISec = aux;
	N_LISec++;

	for (i=N_LISec-1; i>0 && strcmp(s, LISec[i-1].s)<0; i--) {
		LISec[i] = LISec[i-1];
	}
	strcpy(LISec[i].s, s);
	LISec[i].ind1 = ind1;

	return OK;
}

void lista_inv_atualiza(char *velho, char *novo, int id) {
	conjunto *cvelho, *cnovo, *difer, *i;

	cvelho = strtokenizer(velho);
	cnovo = strtokenizer(novo);

	/* tem que remover as palavras pertencentes a cvelho-cnovo
	 * e adicionar as palavras de cnovo-cvelho */
	difer = conj_diferenca(cvelho, cnovo, strcmp_);
	for(i=difer->next ; i!=NULL; i=i->next)
		lista_inv_deleta_((char *)i->i, id);
	conj_destroy(difer);

	difer = conj_diferenca(cnovo, cvelho, strcmp_);
	for(i=difer->next ; i!=NULL; i=i->next)
		lista_inv_insere_((char *)i->i, id);
	conj_destroy(difer);

	conj_destroy(cvelho);
	conj_destroy(cnovo);
}

void lista_inv_deleta(char *s, int id) {
	conjunto *c, *i;

	c = strtokenizer(s);

	for (i=c->next; i!=NULL; i=i->next)
		lista_inv_deleta_((char *)i->i, id);

	conj_destroy(c);
}

void lista_inv_deleta_(char *s, int id) {
	int k = lista_inv_Sec_busca(s);
	lista_inv_Prim_deleta(&LISec[k].ind1, id);

	if (LISec[k].ind1 == FAIL) {
		/* se todos os registros para essa palavra
		 * foram apagados da LIPrim */
		for (; k < N_LISec-1; k++)
			LISec[k] = LISec[k+1];
		N_LISec--;
	}
}

void lista_inv_Prim_deleta(int *k, int id) {
	int save;
	for (; LIPrim[*k].idE != id; k = &LIPrim[*k].next);

	save = LIPrim[*k].next;
	LIPrim[*k].next = avail_list_LIPrim;
	avail_list_LIPrim = *k;

	*k = save;
}

conjunto *strtokenizer(char *s) {
	conjunto *c = conj_init();
	char *tok;

	/* separa a string s em tokens */
	tok = strtok(s, delimiters);
	while (tok != NULL) {
		strtoupper(tok);
		conj_insere(c, (void*)tok, (strlen(tok)+1)*sizeof(char), strcmp_);
		tok = strtok(NULL, delimiters);
	}

	return c;
}
