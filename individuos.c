#include "definicoes.h"

int individuo_busca(int id, Individuo *K) {
  /*int i, k, n, sz, save;
  Individuo X;

  fseek(FIndiv, 0, SEEK_SET);
  fscanf(FIndiv, " %d", &n);
  for (i=0, k=-1; i<n; i++) {
    X = individuo_read(FIndiv, &save, &sz);

    if (X.idI == -1)
      i--;
    if (X.idI == id) {
      k = i;
      break;
    }
  }

  if (k == -1)
    return -1;
  if (K != NULL)
    *K = X;

  fseek(FIndiv, save, SEEK_SET);
  return sz;*/
  int sz, save;
  int i = indice_busca("individuo",id);
  Individuo X;

  if(i == FAIL)
    return FAIL;

  fseek(FIndiv, IPIndiv[i].offset, SEEK_SET);
  X = individuo_read(FIndiv, &save, &sz);

  if (K != NULL)
    *K = X;

  fseek(FIndiv, save, SEEK_SET);
  return sz;
}

void individuo_insere() {
  Individuo X;
  system("clear");

  puts("** INSERE INDIVIDUO **");
  X = individuo_read_(stdin);

  if (indice_busca("individuo",X.idI) != FAIL) {
    puts("\nJa ha registro de individuo com esse id.");
    puts("Insercao falhou.");
    Pause();
    return;
  }
  if(indice_busca("especie", X.idE) == FAIL) {
    puts("\nA especie associada nao existe.");
    puts("Insercao falhou.");
    Pause();
    return;
  }

  individuo_insere_(X);
  muda_n(FIndiv, +1);
  indice_fail(SISecIndiv);
  indice_fail(SIPrimIndiv);
  indice_sec_insere("individuo",X.idE,X.idI);

  /* Atualiza a quantidade de registros */
  

  puts("Individuo inserido corretamente.");
}

void individuo_insere_(Individuo X) {
  int sz, Ssz;

  sz = individuo_conta_caracteres(X);
  Ssz = buraco_var_busca_vazio(FIndiv, sz);
  if (Ssz == -1) {
    fseek(FIndiv, 0, SEEK_END);
    Ssz = sz;
  } else {
    /* remove da lista ligada */
    buraco_var_remove(FIndiv);
  }

  /*Insere no indice os dados do individuo*/
  indice_insere("individuo",X.idI,ftell(FIndiv));

  if (Ssz - sz > SZ_LISTA)
    reg_escreve(FIndiv, sz);
  else
    reg_escreve(FIndiv, Ssz);

  individuo_write(FIndiv, X, 0);

  if (Ssz - sz > SZ_LISTA)
    buraco_var_insere(FIndiv, Ssz-sz-SZ_REG, ftell(FIndiv));
}

void individuo_le() {
  Individuo X;
  int i;
  system("clear");

  puts("** LEITURA INDIVIDUOS **");
  printf("\n");
  /*
  fseek(FIndiv, 0, SEEK_SET);
  fscanf(FIndiv, " %d", &n);
  while (n--) {
    X = individuo_read(FIndiv, NULL, NULL);
    if (X.idI == -1) {
      n++;
      continue;
    }

    individuo_write(stdout, X, 1);
    }*/

  for(i=0;i<N_IPIndiv;i++){
    fseek(FIndiv,IPIndiv[i].offset,SEEK_SET);
    X = individuo_read(FIndiv,NULL,NULL);
    individuo_write(stdout, X, 1);
  }

  Pause();
}

void individuo_deleta() {
  int id, sz;
  Individuo X;
  system("clear");

  puts("** DELECAO INDIVIDUO **");
  printf("Digite o ID do individuo a ser deletado: ");
  scanf(" %d", &id);

  sz = individuo_busca(id, &X);
  if (sz == -1) {
    puts("Nao existe individuo com este ID!\n");
    Pause();
  } else {
    individuo_write(stdout, X, 1);
    if (!Pergunta("Confirma exclusao?"))
      return;
    
    individuo_deleta_(sz);
    muda_n(FIndiv, -1);
    indice_fail(SIPrimIndiv);
    indice_fail(SISecIndiv);
    indice_deleta("individuo",id);    
  }
}

void individuo_deleta_(int sz) {
  int save, szY;
  Individuo Y;

  if (buraco_var_insere(FIndiv, sz, (int)ftell(FIndiv)) == FAIL) {
    /* registro muito pequeno para a lista ligada */

    /* vai para o registro seguinte */
    individuo_read(FIndiv, &save, NULL);
    Y = individuo_read(FIndiv, NULL, &szY);

    /* volta para a posicao do anterior e reescreve Y */
    fseek(FIndiv, save, SEEK_SET);
    reg_escreve(FIndiv, sz+szY+SZ_REG);
    individuo_write(FIndiv, Y, 0);
  }
}

void individuo_atualiza() {
  int id, sz;
  Individuo X;
  system("clear");

  puts("** ATUALIZACAO INDIVIDUOS **");
  printf("Digite o ID do individuo a ter dados alterados: ");
  scanf(" %d", &id);

  sz = individuo_busca(id, &X);
  if (sz == -1) {
    puts("Nao existe individuo com este ID!\n");
    Pause();
  } else {
    individuo_deleta_(sz);

    printf("ID do Individuo: ");
    printf("%d\n", X.idI);
    muda_int(&X.idI);
    printf("ID da Especie: ");
    printf("%d\n", X.idE);
    muda_int(&X.idE);
    printf("Sexo: ");
    printf("%c\n", X.sexo);
    muda_char(&X.sexo);

    /* insere de volta */
    individuo_insere_(X);
  }
}

Individuo individuo_read(FILE* fin, int *_save, int *_sz) {
  Individuo X;
  BuracoVar L;
  int jump, save;
  char c;

  save = (int)ftell(fin);

  fscanf(fin, " %c", &c);
  if (c == VAZIO) {
    buraco_var_le(fin, &L);
    fseek(fin, L.sz - SZ_REG + 1, SEEK_CUR);

    X.idI = -1;
    return X;
  }

  fscanf(fin, " %d", &jump);
  X = individuo_read_(fin);

  fseek(fin, save+jump+SZ_REG, SEEK_SET);

  if (_save != NULL)
    *_save = save;
  if (_sz != NULL)
    *_sz = jump;

  return X;
}

Individuo individuo_read_(FILE *fin) {
  Individuo X;
  int print = (fin==stdin) ? (1) : (0);

  if (print)
    printf("ID do Individuo: ");
  fscanf(fin, " %d", &X.idI);
  if (print)
    printf("ID da Especie: ");
  fscanf(fin, " %d", &X.idE);
  if (print)
    printf("Sexo: ");
  fscanf(fin, " %c", &X.sexo);

  return X;
}

void individuo_write(FILE *fout, Individuo X, int print) {
  if (print)
    printf("ID do Individuo: ");
  fprintf(fout, "%d\n", X.idI);
  if (print)
    printf("ID da Especie: ");
  fprintf(fout, "%d\n", X.idE);
  if (print)
    printf("Sexo: ");
  fprintf(fout, "%c\n", X.sexo);

  if (print)
    printf("\n");
}

int individuo_conta_caracteres(Individuo X) {
  int idI, idE;

  idI = 0;
  if (X.idI == 0)
    idI = 1;
  while (X.idI) {
    idI++;
    X.idI/=10;
  }

  idE = 0;
  if (X.idE == 0)
    idE = 1;
  while (X.idE) {
    idE++;
    X.idE/=10;
  }

  return ((idI+1) + (idE+1) + (1));
}
