#include "definicoes.h"

Indice_Prim *IPEspec;
int N_IPEspec;

Indice_Prim *IPIndiv;
int N_IPIndiv;

void indice_start(char *espec,char *indiv) {
  int i,n;
  int flag;
  int offset;
  Especie X;
  Individuo Y;
  /*-----------ESPECIE------------*/
  FIPrimEspec = fopen(espec, "rb");
  IPEspec = NULL;

  n = 0;
  if (FIPrimEspec != NULL) {
    fread(&n, sizeof(int), 1, FIPrimEspec);
    fread(&flag, sizeof(int), 1, FIPrimEspec);
    if (flag == FAIL){
      N_IPEspec = 0;
      fseek(FEspec, 0, SEEK_SET);
      fscanf(FEspec, " %d", &i);
      while (i--) {
	X = especie_read(FEspec, &offset, NULL);
	especie_write(stdout, X, 1);
	if (X.id == -1) i++;
	else indice_insere("especie",X.id,offset);
      }
    }else{
      IPEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      fread(IPEspec, sizeof(Indice_Prim), n, FIPrimEspec);

      N_IPEspec = n;
    }
    fclose(FIPrimEspec);
  }
  else   N_IPEspec = 0;
  
  
  /*-----------INDIVIDUO------------*/
  FIPrimIndiv = fopen(indiv, "rb");
  IPIndiv = NULL;

  n = 0;
  if (FIPrimIndiv != NULL) {
    fread(&n, sizeof(int), 1, FIPrimIndiv);
    fread(&flag, sizeof(int), 1, FIPrimIndiv);
    if (flag == FAIL){
      N_IPIndiv = 0;
      fseek(FIndiv, 0, SEEK_SET);
      fscanf(FIndiv, " %d", &i);
      while (i--) {
	Y = individuo_read(FIndiv, &offset, NULL);
	if (Y.idI == -1) {
	  i++;
	  continue;
	}
	else indice_insere("individuo",Y.idI,offset);
      }
    }else{
      IPIndiv = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      fread(IPIndiv, sizeof(Indice_Prim), n, FIPrimIndiv);

      N_IPIndiv = n;
    }
    fclose(FIPrimIndiv);
  }
  else N_IPIndiv = 0;

 

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
  fwrite(IPIndiv, sizeof(Indice_Prim), n, FIPrimIndiv);

  free(IPIndiv);
  fclose(FIPrimIndiv);
}

void indice_insere(char *op,int id, int offset) {
  int i;
  if(!strcmp(op,"especie")){
    printf("%d %d\n",id,offset);
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

int indice_busca(char *op, int id){
  int N;
  Indice_Prim *Indice;
  int esq,dir,meio;

  if(!strcmp(op,"especie")){
    N = N_IPEspec;
    Indice = IPEspec;
  } else if(!strcmp(op,"individuo")){
    N = N_IPIndiv;
    Indice = IPIndiv;
  }

  esq = 0;
  dir = N-1;
  while (esq <= dir) {
    meio = (esq+dir)/2;
    if (Indice[meio].id == id) return meio;
    if (Indice[meio].id > id) dir = meio-1;
    else esq = meio+1;
  }

  return FAIL;
}

void indice_fail(char *sfp){
  int n = 0;
  int flag = FAIL;
  FILE *fp = fopen(sfp,"wb");
  fwrite(&n, sizeof(int), 1, fp);
  fwrite(&flag, sizeof(int), 1, fp);
  fclose(fp);
}
