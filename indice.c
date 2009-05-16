#include "definicoes.h"

Indice_Prim *IEspec;
int N_IEspec;
int FAIL_IEspec;


void indice_start(char *espec) {
  int i, n, offset;
  int flag;
  Especie X;
  /*-----------ESPECIE------------*/
  FIndEspec = fopen(espec, "rb");
  IEspec = NULL;
  
  n = 0;
  if (FIndEspec != NULL) {
    fread(&n, sizeof(int), 1, FIndEspec);
    fread(&flag, sizeof(int), 1, FIndEspec);
    /*---RECONSTROI INDICE----*/
    if (flag == FAIL){ 
      fseek(FEspec, 0, SEEK_SET);
      fscanf(FEspec, " %d", &n);
      IEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      N_IEspec = n;
      i = 0;
      while (n--) {
	X = especie_read(FEspec, &offset, NULL);
	if (X.id == -1) {
	  n++;
	  continue;
	}
	else{
	  IEspec[i].id = X.id;
	  IEspec[i].offset = offset;
	  i++;
	}	  
      }
    }else{
      IEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
      fread(IEspec, sizeof(Indice_Prim), n, FIndEspec);

      N_IEspec = n;
    }
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
  FIndEspec = fopen(espec, "wb");

  n = N_IEspec;

  for (i=0; i<n; i++)
    printf("%d %d\n", IEspec[i].id, IEspec[i].offset);

  fwrite(&n, sizeof(int), 1, FIndEspec);
  fwrite(&flag, sizeof(int), 1, FIndEspec);
  fwrite(IEspec, sizeof(Indice_Prim), n, FIndEspec);

  free(IEspec);
  fclose(FIndEspec);
}

void indice_fail(char *espec){
  int n = 0;
  int flag = -1;
  if(!FAIL_IEspec){
    FIndEspec = fopen(espec,"wb");
    fwrite(&n, sizeof(int), 1, FIndEspec);
    fwrite(&flag, sizeof(int), 1, FIndEspec);
    /*Diz que o arquivo de especie esta desatualizado*/
    FAIL_IEspec = 1;
    fclose(FIndEspec);
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

