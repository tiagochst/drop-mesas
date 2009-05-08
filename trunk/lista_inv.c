#include "definicoes.h"

char *delimiters = " .,;:!?()[]{}<>'\"\t\\/";

ListaInv_Prim *LIPrim;
ListaInv_Sec *LISec;
int N_LIPrim;
int N_LISec;

void lista_inv_start(char *prim, char *sec) {
  int n;

  FInvPrim = fopen(prim, "rb");
  FInvSec = fopen(sec, "rb");
  LIPrim = NULL;
  LISec = NULL;

  n = 0;
  if(FInvPrim != NULL) {
    fread(&n, sizeof(int), 1, FInvPrim);

    LIPrim = (ListaInv_Prim *) malloc(n*sizeof(ListaInv_Prim));
    fread(LIPrim, sizeof(ListaInv_Prim), n, FInvPrim);
  }
  N_LIPrim = n;

  n = 0;
  if(FInvSec != NULL) {
    fread(&n, sizeof(int), 1, FInvSec);

    LISec = (ListaInv_Sec *) malloc(n*sizeof(ListaInv_Sec));
    fread(LISec, sizeof(ListaInv_Sec), n, FInvSec);
  }
  N_LISec = n;
}

void lista_inv_end(char *prim, char *sec) {
  int n;

  FInvPrim = fopen(prim, "wb");
  FInvSec = fopen(sec, "wb");

  n = N_LIPrim;
  fwrite(&n, sizeof(int), 1, FInvPrim);
  fwrite(LIPrim, sizeof(ListaInv_Prim), n, FInvPrim);

  n = N_LISec;
  fwrite(&n, sizeof(int), 1, FInvSec);
  fwrite(LISec, sizeof(ListaInv_Sec), n, FInvSec);

  free(LIPrim);
  free(LISec);
}

int strcmp_(void *a, void *b) {
	return strcmp((char*)a, (char*)b);
}

void lista_inv_insere(char *s, int id) {
  conjunto *c = conj_init(), *i;
  char *tok;

  /* separa a string s em tokens */
  tok = strtok(s, delimiters);
  while(tok != NULL) {
    conj_insere(c, (void*)tok, strcmp_);
    tok = strtok(NULL, delimiters);
  }

  for(i=c->next ; i!=NULL ; i=i->next)
    lista_inv_insere_((char*)i->i, id);

  conj_destroy(c);
}

void lista_inv_insere_(char *s, int id) {
  int k = lista_inv_Sec_busca(s);
  if(k == FAIL)
    lista_inv_Sec_insere(s, id);
  lista_inv_Prim_insere(k, id);
}

int lista_inv_Sec_busca(char *s) {
  /* uma busca binária */
  int esq=0, dir=N_LISec, meio, cmp;

  while(esq <= dir) {
  	meio = (esq+dir)/2;
  	cmp = strcmp(LISec[meio].s, s);
  	if(cmp == 0) return meio;
  	if(cmp > 0) dir = meio-1;
  	else esq = meio+1;
  }

  return FAIL;
}

int lista_inv_Prim_insere(int k, int id) {
  return FAIL;
}

int lista_inv_Sec_insere(char *s, int ind1) {
  ListaInv_Sec *aux = (ListaInv_Sec *) realloc(LISec, (N_LISec+1)*sizeof(ListaInv_Sec)); 
  if(aux == NULL) return FAIL;

  LISec = aux;
  N_LISec++;

  strcpy(LISec[N_LISec-1].s, s);
  LISec[N_LISec-1].ind1 = ind1;
  qsort(LISec, N_LISec, sizeof(ListaInv_Sec), ListaInv_Sec_cmp);

  return OK;
}

int ListaInv_Sec_cmp(const void *i, const void *j) {
  ListaInv_Sec *a = (ListaInv_Sec *)i;
  ListaInv_Sec *b = (ListaInv_Sec *)j;
  return strcmp(a->s, b->s);
}
