#include "definicoes.h"

Indice_Sec *ISIndiv;
int N_ISIndiv;
int FAIL_ISIndiv;

Indice_Sec *ISCaptu;
int N_ISCaptu;
int FAIL_ISCaptu;

void indice_sec_start(char *indiv,char *captu){
  int  n;
  int flag;

  /*-----------INDIVIDUO---------*/
  FISecIndiv = fopen(indiv, "rb");
  ISIndiv = NULL;

  n = 0;
  if (FISecIndiv != NULL) {
    fread(&n, sizeof(int), 1, FISecIndiv);
    fread(&flag, sizeof(int), 1, FISecIndiv);

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

  /*-------------CAPTURA-----------*/
  FISecCaptu = fopen(captu, "rb");
  ISCaptu = NULL;

  n = 0;
  if (FISecCaptu != NULL) {
    fread(&n, sizeof(int), 1, FISecCaptu);
    fread(&flag, sizeof(int), 1, FISecCaptu);

    if (flag == FAIL){
    }else{
      ISCaptu = (Indice_Sec *) malloc(n*sizeof(Indice_Sec));
      fread(ISCaptu, sizeof(Indice_Sec), n, FISecCaptu);

      N_ISCaptu = n;
    }
    fclose(FISecCaptu);
  }
  else   N_ISCaptu = 0;

  FAIL_ISCaptu = 0;
}


void indice_sec_end(char *indiv,char *captu){
  int n;
  int flag= OK;
  /*-------INDIVIDUO---------*/
  FISecIndiv = fopen(indiv, "wb");

  n = N_ISIndiv;
 
  fwrite(&n, sizeof(int), 1, FISecIndiv);
  fwrite(&flag, sizeof(int), 1, FISecIndiv);
  fwrite(ISIndiv, sizeof(Indice_Sec), n, FISecIndiv);

  
  free(ISIndiv);
  fclose(FISecIndiv);
  
  /*-------CAPTURAS----------*/
  FISecCaptu = fopen(captu, "wb");

  n = N_ISCaptu;

  fwrite(&n, sizeof(int), 1, FISecCaptu);
  fwrite(&flag, sizeof(int), 1, FISecCaptu);
  fwrite(ISCaptu,sizeof(Indice_Sec), n, FISecCaptu);

  free(ISCaptu);
  fclose(FISecCaptu);
}

void indice_sec_insere(char *op,int idS,int idP){
  int i, *N;
  Indice_Sec *Indice, *aux;

  if(!strcmp(op,"individuo")){
    N = &N_ISIndiv;
    Indice = ISIndiv;
  } else if(!strcmp(op,"captura")){
    N = &N_ISCaptu;
    Indice = ISCaptu;
  }

  (*N)++;
  aux = (Indice_Sec *)realloc(Indice, (*N)*sizeof(Indice_Sec));
  if(aux == NULL) return;
  Indice = aux;

  i = (*N)-1;
  while(i>0 && (idS < Indice[i-1].idS)) {
    Indice[i] = Indice[i-1];
    i--;
  }

  Indice[i].idS = idS;
  Indice[i].idP = idP;

  /*
  if(!strcmp(op,"individuo")){
    N_ISIndiv++;
    ISIndiv = (Indice_Sec *)realloc(ISIndiv, (N_ISIndiv)*sizeof(Indice_Sec));
    i = N_ISIndiv-1;
    while (i>0 && (idS < ISIndiv[i-1].idS)) {
      ISIndiv[i] = ISIndiv[i-1];
      i--;
    }

    ISIndiv[i].idS = idS;
    ISIndiv[i].idP = idP;
  }
  if(!strcmp(op,"captura")){
    N_ISCaptu++;
    ISCaptu = (Indice_Sec *)realloc(ISCaptu, (N_ISCaptu)*sizeof(Indice_Sec));
    i = N_ISCaptu-1;
    while (i>0 && (idS < ISCaptu[i-1].idS)) {
      ISCaptu[i] = ISCaptu[i-1];
      i--;
    }

    ISCaptu[i].idS = idS;
    ISCaptu[i].idP = idP;
  }
  */
}

int indice_sec_busca(char *op, int id) {
  int N;
  Indice_Sec *Indice;
  int esq,dir,meio;

  if(!strcmp(op,"individuo")){
    N = N_ISIndiv;
    Indice = ISIndiv;
  } else if(!strcmp(op,"captura")){
    N = N_ISCaptu;
    Indice =  ISCaptu;
  }

  esq = 0;
  dir = N-1;
  if(N == 0) return FAIL;
  while(esq <= dir) {
    meio = (esq+dir)/2;
    if(Indice[meio].idS < id) esq = meio+1;
    else dir = meio-1;
  }

  if(Indice[meio].idS == id) return meio;
  if(Indice[meio+1].idS == id) return meio+1;
  return FAIL;
}
