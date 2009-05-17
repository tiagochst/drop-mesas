#include "definicoes.h"

Indice_Prim *IEspec;
int N_IEspec;
int FAIL_IEspec;


Indice_Sec *ISIndiv;
int N_ISIndiv;
int FAIL_ISIndiv;

void indice_start(char *espec) {
  int i, n, offset;
  int flag;
  Especie X;
  /*-----------ESPECIE------------*/
  FIPrimEspec = fopen(espec, "rb");
  IEspec = NULL;

  n = 0;
  if (FIPrimEspec != NULL) {
    fread(&n, sizeof(int), 1, FIPrimEspec);
    fread(&flag, sizeof(int), 1, FIPrimEspec);
    /*---RECONSTROI INDICE----*/
    if (flag == FAIL){
      fseek(FEspec, 0, SEEK_SET);
      fscanf(FEspec, " %d", &n);
      IEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      while (n--) {
	X = especie_read(FEspec, &offset, NULL);
	if (X.id == -1) {
	  n++;
	  continue;
	}
	else{
	  indice_insere(X.id,offset);
	}
      }
    }else{
      IEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      fread(IEspec, sizeof(Indice_Prim), n, FIPrimEspec);

      N_IEspec = n;
    }
    fclose(FIPrimEspec);
  }
  else   N_IEspec = 0;

  FAIL_IEspec = 0;

  printf("%d\n", N_IEspec);
  for (i=0; i<n; i++)
    printf("%d %d\n", IEspec[i].id, IEspec[i].offset);

}


void indice_end(char *espec) {
  int i;
  int n;
  int flag= OK;
  FIPrimEspec = fopen(espec, "wb");

  n = N_IEspec;

  for (i=0; i<n; i++)
    printf("%d %d\n", IEspec[i].id, IEspec[i].offset);

  fwrite(&n, sizeof(int), 1, FIPrimEspec);
  fwrite(&flag, sizeof(int), 1, FIPrimEspec);
  fwrite(IEspec, sizeof(Indice_Prim), n, FIPrimEspec);

  free(IEspec);
  fclose(FIPrimEspec);
}

void indice_fail(char *espec){
  int n = 0;
  int flag = -1;
  if(!FAIL_IEspec){
    FIPrimEspec = fopen(espec,"wb");
    fwrite(&n, sizeof(int), 1, FIPrimEspec);
    fwrite(&flag, sizeof(int), 1, FIPrimEspec);
    /*Diz que o arquivo de especie esta desatualizado*/
    FAIL_IEspec = 1;
    fclose(FIPrimEspec);
  }
}

void indice_insere(int id, int offset) {
  int i;

  N_IEspec++;
  IEspec = (Indice_Prim *)realloc(IEspec, (N_IEspec)*sizeof(Indice_Prim));
  i = N_IEspec-1;
  while (i>0 && (id < IEspec[i-1].id)) {
    IEspec[i] = IEspec[i-1];
    i--;
  }

  IEspec[i].id = id;
  IEspec[i].offset = offset;
}

void indice_deleta(int id) {
  int i;
  int pos = indice_busca(id);
  printf("%d\n", pos);
  if (pos == -1) {
    printf("Nao existe arquivo com esse indice!\n");
  }else {
    for (i=pos; i<N_IEspec; i++)
      IEspec[i] = IEspec[i+1];
    N_IEspec--;
    IEspec = (Indice_Prim *)realloc(IEspec, (N_IEspec)*sizeof(Indice_Prim));
    printf("Registro removido com sucesso!\n");
  }
}

int indice_busca(int id) {
  int ini = 0, fim = N_IEspec-1, meio;
  if(N_IEspec == 0) return -1;
  if (IEspec[ini].id > id || IEspec[fim].id < id)
    return -1;

  if (IEspec[ini].id == id)
    return ini;
  if (IEspec[fim].id == id)
    return fim;

  while (fim - ini >= 2) {
    meio = (ini + fim)/2;
    if (IEspec[meio].id > id)
      fim = meio;
    else if (IEspec[meio].id < id)
      ini = meio;
    else
      return meio;
  }

  return -1;
}

/*----FUNCOES PARA INDICE SECUNDARIO---*/

void indice_sec_start(char *indiv){
  int i, n;
  int flag;
  Individuo X;

  FISecIndiv = fopen(indiv, "rb");
  ISIndiv = NULL;

  n = 0;
  if (FISecIndiv != NULL) {
    fread(&n, sizeof(int), 1, FISecIndiv);
    fread(&flag, sizeof(int), 1, FISecIndiv);
    /*---RECONSTROI INDICE----*/
    if (flag == FAIL){
      fseek(FIndiv, 0, SEEK_SET);
      fscanf(FIndiv, " %d", &n);
      ISIndiv = (Indice_Sec *) malloc(n*sizeof(Indice_Sec));
      while (n--) {
	X = individuo_read(FIndiv, NULL, NULL);
	if (X.idI == -1) {
	  n++;
	  continue;
	}
	else{
	  indice_sec_insere(X.idE,X.idI);
	}
      }
    }else{
      ISIndiv = (Indice_Sec *) malloc(n*sizeof(Indice_Sec));
      fread(ISIndiv, sizeof(Indice_Sec), n, FISecIndiv);

      N_ISIndiv = n;
    }
    fclose(FISecIndiv);
  }
  else   N_ISIndiv = 0;

  FAIL_ISIndiv = 0;
}


void indice_sec_end(char *espec) {
  int i;
  int n;
  int flag= OK;
  FISecIndiv = fopen(espec, "wb");

  n = N_ISIndiv;

  fwrite(&n, sizeof(int), 1, FISecIndiv);
  fwrite(&flag, sizeof(int), 1, FISecIndiv);
  fwrite(ISIndiv, sizeof(Indice_Sec), n, FISecIndiv);

  for(i=0;i<N_ISIndiv;i++)
    printf("%d %d\n",ISIndiv[i].idS,ISIndiv[i].idP);

  free(ISIndiv);
  fclose(FISecIndiv);
}

void indice_sec_insere(int idS,int idP){
  int i = N_ISIndiv;

  N_ISIndiv++;
  ISIndiv = (Indice_Sec *)realloc(ISIndiv, (N_ISIndiv)*sizeof(Indice_Sec));
  while (i>0 && (idS < ISIndiv[i-1].idS)) {
    ISIndiv[i] = ISIndiv[i-1];
    i--;
  }

  ISIndiv[i].idS = idS;
  ISIndiv[i].idP = idP;

}

