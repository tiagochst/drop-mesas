#include "definicoes.h"

Indice_Prim *IPEspec;
int N_IPEspec;
int FAIL_IPEspec;

Indice_Prim *IPIndiv;
int N_IPIndiv;
int FAIL_IPIndiv;

void indice_start(char *espec,char *indiv) {
  int i,n;
  int flag;
  /*-----------ESPECIE------------*/
  FIPrimEspec = fopen(espec, "rb");
  IPEspec = NULL;

  n = 0;
  if (FIPrimEspec != NULL) {
    fread(&n, sizeof(int), 1, FIPrimEspec);
    fread(&flag, sizeof(int), 1, FIPrimEspec);
    if (flag == FAIL){
    }else{
      IPEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      fread(IPEspec, sizeof(Indice_Prim), n, FIPrimEspec);

      N_IPEspec = n;
    }
    fclose(FIPrimEspec);
  }
  else   N_IPEspec = 0;

  FAIL_IPEspec = 0;

  printf("%d\n", N_IPEspec);
  for (i=0; i<n; i++)
    printf("%d %d\n", IPEspec[i].id, IPEspec[i].offset);

  /*-----------INDIVIDUO------------*/
  FIPrimIndiv = fopen(indiv, "rb");
  IPIndiv = NULL;

  n = 0;
  if (FIPrimIndiv != NULL) {
    fread(&n, sizeof(int), 1, FIPrimIndiv);
    fread(&flag, sizeof(int), 1, FIPrimIndiv);
    if (flag == FAIL){
    }else{
      IPIndiv = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      fread(IPIndiv, sizeof(Indice_Prim), n, FIPrimIndiv);

      N_IPIndiv = n;
    }
    fclose(FIPrimIndiv);
  }
  else N_IPIndiv = 0;

  FAIL_IPIndiv = 0;

  printf("%d\n", N_IPIndiv);
  for (i=0; i<n; i++)
    printf("%d %d\n", IPIndiv[i].id, IPIndiv[i].offset);

}


void indice_end(char *espec,char *indiv) {
  int i;
  int n;
  int flag= OK;

  /*-------ESPECIE-------*/
  FIPrimEspec = fopen(espec, "wb");

  n = N_IPEspec;

  for (i=0; i<n; i++)
    printf("%d %d\n", IPEspec[i].id, IPEspec[i].offset);

  fwrite(&n, sizeof(int), 1, FIPrimEspec);
  fwrite(&flag, sizeof(int), 1, FIPrimEspec);
  fwrite(IPEspec, sizeof(Indice_Prim), n, FIPrimEspec);

  free(IPEspec);
  fclose(FIPrimEspec);

  /*-------INDIVIDUO------*/
  FIPrimIndiv = fopen(indiv, "wb");

  n = N_IPIndiv;

  for (i=0; i<n; i++)
    printf("%d %d\n", IPIndiv[i].id, IPIndiv[i].offset);

  fwrite(&n, sizeof(int), 1, FIPrimIndiv);
  fwrite(&flag, sizeof(int), 1, FIPrimIndiv);
  fwrite(IPEspec, sizeof(Indice_Prim), n, FIPrimIndiv);

  free(IPIndiv);
  fclose(FIPrimIndiv);
}

void indice_insere(char *op,int id, int offset) {
  int i;
  if(!strcmp(op,"especie")){
    N_IPEspec++;
    IPEspec = (Indice_Prim *)realloc(IPEspec,N_IPEspec*sizeof(Indice_Prim));
    i = N_IPEspec-1;
    while (i>0 && (id < IPEspec[i-1].id)) {
      IPEspec[i] = IPEspec[i-1];
      i--;
    }
    IPEspec[i].id = id;
    IPEspec[i].offset = offset;
  }
  if(!strcmp(op,"individuo")){
    N_IPIndiv++;
    IPIndiv = (Indice_Prim *)realloc(IPIndiv,N_IPIndiv*sizeof(Indice_Prim));
    i = N_IPIndiv-1;
    while (i>0 && (id < IPIndiv[i-1].id)) {
      IPIndiv[i] = IPIndiv[i-1];
      i--;
    }
    IPIndiv[i].id = id;
    IPIndiv[i].offset = offset;
  }

}

void indice_deleta(char *op,int id) {
  int i;
  int pos = indice_busca(op,id);
  if (pos == -1){
    printf("Nao existe registro com esse indice!\n");
    return;
  }

  if(!strcmp(op,"especie")){
    for (i=pos; i<N_IPEspec; i++) IPEspec[i] = IPEspec[i+1];
    N_IPEspec--;
    IPEspec = (Indice_Prim *)realloc(IPEspec, (N_IPEspec)*sizeof(Indice_Prim));
    printf("Registro removido com sucesso!\n");

  }
  if(!strcmp(op,"individuo")){
    for (i=pos; i<N_IPIndiv; i++)  IPIndiv[i] = IPIndiv[i+1];
    N_IPIndiv--;
    IPIndiv = (Indice_Prim *)realloc(IPIndiv, (N_IPIndiv)*sizeof(Indice_Prim));
    printf("Registro removido com sucesso!\n");
  }
}

int indice_busca(char *op,int id){
  int i,N;
  Indice_Prim *Indice;
  int ini,fim,meio;

  if(!strcmp(op,"especie")){
    N = N_IPEspec;
    Indice = (Indice_Prim *)malloc(N*sizeof(Indice_Prim));
    for(i=0;i<N;i++) Indice[i] = IPEspec[i];
  }
  if(!strcmp(op,"individuo")){
    N = N_IPIndiv;
    Indice = (Indice_Prim *)malloc(N*sizeof(Indice_Prim));
    for(i=0;i<N;i++) Indice[i] = IPIndiv[i];
  }

  ini = 0, fim = N-1;
  if(N == 0 || Indice[ini].id > id || Indice[fim].id < id) {
    free(Indice);
    return -1;
  }

  if (Indice[ini].id == id){
    free(Indice);
    return ini;
  }
  if (Indice[fim].id == id){
    free(Indice);
    return fim;
  }

  while (fim - ini >= 2) {
    printf("%d %d\n",ini,fim);
    meio = (ini + fim)/2;
    if (Indice[meio].id > id)
      fim = meio;
    else if (Indice[meio].id < id)
      ini = meio;
    else{
      free(Indice);
      return meio;
    }
  }
  free(Indice);
  return -1;
}

