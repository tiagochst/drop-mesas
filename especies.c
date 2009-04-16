#include "definicoes.h"

int especie_busca(int id, Especie *K) {
  int i,k, n, sz,save;
  Especie X;

  fseek(FEspec, 0, SEEK_SET);
  fscanf(FEspec, " %d", &n);
  for(i=0,k=-1 ; i<n ; i++) {
    X = especie_read(FEspec, &save, &sz);

    if(X.id == -1) i--;
    if(X.id == id) {
      k = i;
      break;
    }
  }

  if(k == -1) return -1;
  if(K != NULL) *K = X;

  fseek(FEspec, save, SEEK_SET);
  return sz;
}

void especie_insere() {
  Especie X;
  int n, sz, Ssz;
  system("clear");

  puts("** INSERE ESPECIE **");
  X = especie_read_(stdin);

  if(especie_busca(X.id, NULL) != -1) {
    puts("\nJa ha registro de especie com esse id.");
    Pause();
    return;
  }

  sz = especie_conta_caracteres(X);
  Ssz = lista_busca_vazio(FEspec, sz);
  if(Ssz == -1) { 
    /*Se  nao achar um buraco vazio coloca no final do arquivo*/
    fseek(FEspec, 0, SEEK_END);
    Ssz = sz;
  }
  else {
    /* remove da lista ligada */
    lista_remove(FEspec);
  }

  /*Coloca no arquivo o cabeçalho, indicando que está usado */
  if(Ssz - sz > SZ_LISTA) fprintf(FEspec, "%c%04d\n", USADO, sz);
  else fprintf(FEspec, "%c%04d\n", USADO, Ssz);

  especie_write(FEspec, X, 0); /*Escreve as  informações de X*/

  if(Ssz - sz > SZ_LISTA)
    lista_insere(FEspec, Ssz-sz-SZ_REG, ftell(FEspec));

  /* Atualiza a quantidade de registros */
  fseek(FEspec, 0, SEEK_SET);
  fscanf(FEspec, " %d", &n);
  fseek(FEspec, 0, SEEK_SET);
  fprintf(FEspec, "%03d", n+1);
}

/*LE todas as especies existentes e imprime na saida padrao*/
void especie_le() {
  Especie X;
  int n;
  system("clear");

  puts("** LEITURA ESPECIES **");
  printf("\n");

  fseek(FEspec, 0, SEEK_SET);
  fscanf(FEspec, " %d", &n);
  while(n--) {
    X = especie_read(FEspec, NULL, NULL);
    if(X.id == -1) {
      n++; continue;
    }

    especie_write(stdout, X, 1);
  }

  Pause();
}

void especie_deleta() {
  int id, n, sz;
  Especie X;
  system("clear");

  puts("** DELECAO ESPECIE **");
  printf("Digite o ID da especie a ser deletada: ");
  scanf(" %d", &id);

  sz = especie_busca(id, &X);
  if(sz == -1) {
    puts("Nao existe especie com este ID!\n");
    Pause();
  }
  else {
    especie_write(stdout, X, 1);
    if(!Pergunta("Confirma exclusao?")) return;

    lista_insere(FEspec, sz, (int)ftell(FEspec));

    fseek(FEspec, 0, SEEK_SET);
    fscanf(FEspec, " %d", &n);
    fseek(FEspec, 0, SEEK_SET);
    fprintf(FEspec, "%03d", n-1);
  }
}

void especie_atualiza() {
  int id, sz, Ssz;
  Especie X;
  system("clear");

  puts("** ATUALIZACAO ESPECIES **");
  printf("Digite o ID da especie a ter dados alterados: ");
  scanf(" %d", &id);

  sz = especie_busca(id, &X);
  if(sz == -1) {
    puts("Nao existe especie com este ID!\n");
    Pause();
  }
  else {
    /* apaga o registro */
    lista_insere(FEspec, sz, (int)ftell(FEspec));

    printf("ID: ");
    printf("%d\n", X.id);
    muda_int(&X.id);
    printf("Caminho da foto: ");
    printf("%s\n", X.camin);
    muda_string(X.camin);
    printf("Data: ");
    printf("%d\n", X.data);
    muda_int(&X.data);
    printf("Nome cientifico: ");
    printf("%s\n", X.nomec);
    muda_string(X.nomec);
    printf("Nome popular: ");
    printf("%s\n", X.nomep);
    muda_string(X.nomep);
    printf("Descricao: ");
    printf("%s\n", X.descr);
    muda_string(X.descr);

    /* insere de volta */
    sz = especie_conta_caracteres(X);
    Ssz = lista_busca_vazio(FEspec, sz);
    if(Ssz == -1) {
      fseek(FEspec, 0, SEEK_END);
      Ssz = sz;
    }
    else lista_remove(FEspec);
    if(Ssz - sz > SZ_LISTA) fprintf(FEspec, "%c%04d\n", USADO, sz);
    else fprintf(FEspec, "%c%04d\n", USADO, Ssz);
    especie_write(FEspec, X, 0);

    if(Ssz - sz > SZ_LISTA)
      lista_insere(FEspec, Ssz-sz-SZ_REG, ftell(FEspec));
  }
}


/* lê UM registro de Especie do arquivo */
Especie especie_read(FILE* fin, int *_save, int *_sz) {
  Especie X;
  Lista L;
  int jump, save;
  char c;

  if(fin == stdin) {
    puts("*************");
    puts("*************");
    puts("** WARNING **");
    puts("*************");
    puts("*************");
    return especie_read_(fin);
  }

  save = (int)ftell(fin);

  fscanf(fin, " %c", &c);
  if(c == VAZIO) {
    lista_le(fin, &L);
    fseek(fin, L.sz - 6, SEEK_CUR);

    X.id = -1;
    return X;
  }

  fscanf(fin, " %d", &jump);
  X = especie_read_(fin);

  fseek(fin, save+jump+SZ_REG, SEEK_SET);

  if(_save != NULL)
    *_save = save;
  if(_sz != NULL)
    *_sz = jump;

  return X;
}

Especie especie_read_(FILE *fin) {
  Especie X;
  int print = (fin==stdin)?(1):(0);

  if(print) printf("ID: ");
  fscanf(fin, " %d", &X.id);
  if(print) printf("Caminho da foto: ");
  fscanf(fin, " %s", X.camin);
  if(print) printf("Data: ");
  fscanf(fin, " %d", &X.data);
  if(print) printf("Nome cientifico: ");
  fscanf(fin, " %s", X.nomec);
  if(print) printf("Nome popular: ");
  fscanf(fin, " %s", X.nomep);
  if(print) printf("Descricao: ");
  fscanf(fin, " %s", X.descr);

  return X;
}

void especie_write(FILE *fout, Especie X, int print) {
  if(print) printf("ID: ");
  fprintf(fout, "%d\n", X.id);
  if(print) printf("Caminho da foto: ");
  fprintf(fout, "%s\n", X.camin);
  if(print) printf("Data: ");
  fprintf(fout, "%d\n", X.data);
  if(print) printf("Nome cientifico: ");
  fprintf(fout, "%s\n", X.nomec);
  if(print) printf("Nome popular: ");
  fprintf(fout, "%s\n", X.nomep);
  if(print) printf("Descricao: ");
  fprintf(fout, "%s\n", X.descr);

  if(print) printf("\n");
}

int especie_conta_caracteres(Especie X) {
  int id,data;

  id = 0;
  if(X.id == 0) id = 1;
  while(X.id) {
    id++; X.id/=10;
  }

  data = 0;
  if(X.data == 0) data = 1;
  while(X.data) {
    data++; X.data/=10;
  }

  return ((id+1)
	  + (strlen(X.camin)+1)
	  + (data+1)
	  + (strlen(X.nomec)+1)
	  + (strlen(X.nomep)+1)
	  + (strlen(X.descr)));
}

