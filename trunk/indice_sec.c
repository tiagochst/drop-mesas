#include "definicoes.h"

Indice_Sec *ISIndiv;
int N_ISIndiv;

Indice_Sec *ISCaptu;
int N_ISCaptu;


void indice_sec_start(char *indiv,char *captu){
  int  i,n;
  int flag;
  int offset;
  int avail_list;
  Individuo X;
  Captura Y;
  
  /*-----------INDIVIDUO---------*/
  FISecIndiv = fopen(indiv, "rb");
  ISIndiv = NULL;

  n = 0;
  if (FISecIndiv != NULL) {
    fread(&n, sizeof(int), 1, FISecIndiv);
    fread(&flag, sizeof(int), 1, FISecIndiv);
    /*reconstroi o indice, em caso de quebra de execucao*/
    if (flag == FAIL){
      N_ISIndiv = 0;
      fseek(FIndiv, 0, SEEK_SET);
      fscanf(FIndiv, " %d", &i);
      while (i--) {
	X = individuo_read(FIndiv, NULL, NULL);
	if (X.idI == -1) {
	  i++;
	  continue;
	}
	else indice_sec_insere("individuo",X.idE,X.idI);
      }      
    }/*caso contrario, le do arquivo de indice*/
    else{
      ISIndiv = (Indice_Sec *) malloc(n*sizeof(Indice_Sec));
      fread(ISIndiv, sizeof(Indice_Sec), n, FISecIndiv);
      
      N_ISIndiv = n;
    }
    fclose(FISecIndiv);
  }
  else  N_ISIndiv = 0;


  /*-------------CAPTURA-----------*/
  FISecCaptu = fopen(captu, "rb");
  ISCaptu = NULL;

  n = 0;
  if (FISecCaptu != NULL) {
    fread(&n, sizeof(int), 1, FISecCaptu);
    fread(&flag, sizeof(int), 1, FISecCaptu);

    if (flag == FAIL){
      fseek(FCaptu,0,SEEK_SET);
      fread(&i,sizeof(int),1,FCaptu);
      fread(&avail_list, sizeof(int), 1, FCaptu);
      while(i--){
	offset = (int ) ftell(FCaptu);
	Y = captura_read(FCaptu);
	if(Y.idC == FAIL) i++;
	else indice_sec_insere("captura",Y.idI,offset);	
      }
    }else{
      ISCaptu = (Indice_Sec *) malloc(n*sizeof(Indice_Sec));
      fread(ISCaptu, sizeof(Indice_Sec), n, FISecCaptu);

      N_ISCaptu = n;
    }
    fclose(FISecCaptu);
  }
  else   N_ISCaptu = 0;

}

/*Encerra o indice secundario escrevendo
  os indices no arquivo */

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

/*Insere no indice de "op" idS (chave secundaria) e 
  idP (o outro atributo)*/
void indice_sec_insere(char *op,int idS,int idP){
  int i;  

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
  
}

void indice_sec_deleta(char *op,int idS,int idP){
  int i,j;
  int pos;
  if(!strcmp(op,"individuo")){
    pos = indice_sec_busca(op,idS);
    for(i=pos;i<N_ISIndiv && ISIndiv[i].idS==idS;i++)
      if(ISIndiv[i].idP==idP) break;
    for(j=i;j<N_ISIndiv;j++)
      ISIndiv[j] = ISIndiv[j+1];
    N_ISIndiv--;
    ISIndiv = (Indice_Sec *)realloc(ISIndiv,(N_ISIndiv)*sizeof(Indice_Sec));
  }

  if(!strcmp(op,"captura")){
    pos = indice_sec_busca(op,idS);
    for(i=pos;i<N_ISCaptu && ISCaptu[i].idS==idS;i++)
      if(ISCaptu[i].idP==idP) break;
    for(j=i;j<N_ISCaptu;j++)
      ISCaptu[j] = ISCaptu[j+1];
    N_ISCaptu--;
    ISCaptu = (Indice_Sec *)realloc(ISCaptu,(N_ISCaptu)*sizeof(Indice_Sec));
  }

}

/*Realiza uma busca binaria, retornando o lemento de menor
  indice*/
int indice_sec_busca(char *op, int id) {
  int N;
  Indice_Sec *Indice;
  int esq,dir,meio;

  if(!strcmp(op,"individuo")){
    N = N_ISIndiv;
    Indice = ISIndiv;
  }else if(!strcmp(op,"captura")){
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


