#include "definicoes.h"

char *delimiters = " .,;:!?()[]{}<>'\"\t\\/";

ListaInv_Prim *LIPrim;
ListaInv_Sec *LISec;
int N_LIPrim;
int N_LISec;
int avail_list_LIPrim;

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

int lista_inv_insere_(char *s, int id) {
  int aux, k;

  k = lista_inv_Sec_busca(s);
  aux = lista_inv_Prim_insere(k, id);

  if(k == FAIL)
    if(lista_inv_Sec_insere(s, aux) == FAIL)
      return FAIL;

  return OK;
}

void lista_inv_busca(char *s) {
  conjunto *c = conj_init(), *ans = conj_init(), *i, *aux;
  char *tok;
  int k;

  /* insere em 'ans' todos IDs de especies */

  /* separa a string s em tokens */
  tok = strtok(s, delimiters);
  while(tok != NULL) {
    conj_insere(c, (void*)tok, strcmp_);
    tok = strtok(NULL, delimiters);
  }

  for(i=c->next ; i!=NULL ; i=i->next) {
    k = lista_inv_Sec_busca((char*)i->i);

    /* gera lista de IDs relacionados */
    aux = conj_init();
    while(k != FAIL) {
      conj_insere(aux, (void*)LIPrim[k].chave, intcmp_);
      k = LIPrim[k].next;
    }

    ans = conj_interseccao(ans, aux, intcmp_);
    conj_destroy(aux);
  }

  /* itera em 'ans' fazendo algo */

  conj_destroy(ans);
  conj_destroy(c);
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
  int pos;
  ListaInv_Prim *aux;

  if(avail_list_LIPrim == FAIL) {
    /* nao tem buraco, dar realloc no LIPrim */
    aux = (ListaInv_Prim*) realloc(LIPrim, (N_LIPrim+1)*sizeof(ListaInv_Prim));
    if(aux == NULL) return FAIL;
    LIPrim = aux;
    
    pos = N_LIPrim++;
  }
  else {
    pos = avail_list_LIPrim;
    avail_list_LIPrim = LIPrim[pos].next;
  }

  LIPrim[pos].chave = id;
  if(k == FAIL) {
    /* insere um novo */
    LIPrim[pos].next = -1;
  }
  else {
    /* basta alterar a lista ligada */
    LIPrim[pos].next = LIPrim[k].next;
    LIPrim[k].next = pos;
  }

  /* e devolve a posicao */
  return pos;
}

int lista_inv_Sec_insere(char *s, int ind1) {
  int i;
  ListaInv_Sec *aux = (ListaInv_Sec *) realloc(LISec, (N_LISec+1)*sizeof(ListaInv_Sec)); 
  if(aux == NULL) return FAIL;

  LISec = aux;
  N_LISec++;

  for(i=N_LISec-1 ; i>0 && strcmp(s, LISec[i-1].s)>0 ; i--) {
    LISec[i] = LISec[i-1];
    /*strcpy(LISec[i].s, LISec[i-1].s);
    LISec[i].ind1 = LISec[i-1].ind1;*/
  }
  strcpy(LISec[i].s, s);
  LISec[i].ind1 = ind1;

  return OK;
}
/*
int ListaInv_Sec_cmp(const void *i, const void *j) {
  ListaInv_Sec *a = (ListaInv_Sec *)i;
  ListaInv_Sec *b = (ListaInv_Sec *)j;
  return strcmp(a->s, b->s);
}
*/