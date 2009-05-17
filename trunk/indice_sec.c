#include "definicoes.h"

Indice_Sec *ISIndiv;
int N_ISIndiv;
int FAIL_ISIndiv;

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


void indice_sec_end(char *indiv) {
  int i;
  int n;
  int flag= OK;
  FISecIndiv = fopen(indiv, "wb");

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

int indice_sec_busca(int id) {
  int ini = 0, fim = N_ISIndiv-1, meio;
  if(N_ISIndiv == 0) return -1;
  if (ISIndiv[ini].idS > id || ISIndiv[fim].idS < id)
    return -1;

  if (ISIndiv[ini].idS == id)
    return ini;
  if (ISIndiv[fim].idS == id)
    return fim;

  while (fim - ini >= 2) {
    printf("%d %d\n",ini,fim);
    meio = (ini + fim)/2;
    if (ISIndiv[meio].idS > id)
      fim = meio;
    else if (ISIndiv[meio].idS < id)
      ini = meio;
    else
      return meio;
  }

  return -1;
}
