#include "definicoes.h"

/* INDIVÍDUO BUSCA
 * - busca indivíduo de ID 'id', e salva seu registro em K
 * - ao final da busca, o ponteiro no arquivo estará
 * imediatamente antes do começo do registro dessa captura
 * - utiliza o índice primário implementado */
int individuo_busca_lab1(int id, Individuo *K) {
  int i,k, n, sz,save;
  Individuo X;

  fseek(FIndiv, 0, SEEK_SET);
  fscanf(FIndiv, " %d", &n);
  for(i=0,k=-1 ; i<n ; i++) {
    X = individuo_read(FIndiv, &save, &sz);

    if(X.idI == -1) i--;
    if(X.idI == id) {
      k = i;
      break;
    }
  }

  if(k == -1) return -1;
  if(K != NULL) *K = X;

  fseek(FIndiv, save, SEEK_SET);
  return sz;
}

int individuo_busca_lab2(int id, Individuo *K) {
  int sz, save;
  int i = indice_busca("individuo", id);
  Individuo X;

  if (i == FAIL)
    return FAIL;

  fseek(FIndiv, IPIndiv[i].offset, SEEK_SET);
  X = individuo_read(FIndiv, &save, &sz);

  if (K != NULL)
    *K = X;

  fseek(FIndiv, save, SEEK_SET);
  return sz;
}

/* INDIVÍDUO INSERE
 * - lê os valores da entrada padrao e insere no arquivo
 * de tamanho variável
 * - atualiza o índice secundário */
void individuo_insere() {
  Individuo X;
  system("clear");

  puts("** INSERE INDIVIDUO **");
  X = individuo_read_(stdin);

  if (indice_busca("individuo", X.idI) != FAIL) {
    puts("\nJa ha registro de individuo com esse id.");
    puts("Insercao falhou.");
    Pause();
    return;
  }
  if (indice_busca("especie", X.idE) == FAIL) {
    puts("\nA especie associada nao existe.");
    puts("Insercao falhou.");
    Pause();
    return;
  }

  individuo_insere_(X);
  muda_n(FIndiv, +1);
  indice_fail(SISecIndiv);
  indice_fail(SIPrimIndiv);
  indice_sec_insere("individuo", X.idE, X.idI);

  puts("Individuo inserido corretamente.");
}

/* INDIVÍDUO INSERE 2
 * função mais baixo nível de inserção
 * - busca na lista ligada de buracos por um espaço de tamanho
 * no mínimo 'sz'
 * - o espaço restante é re-inserido na lista ligada de buracos
 * - adiciona o registro no índice primário */
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
  indice_insere("individuo", X.idI, ftell(FIndiv));

  if (Ssz - sz > SZ_LISTA)
    reg_escreve(FIndiv, sz);
  else
    reg_escreve(FIndiv, Ssz);

  individuo_write(FIndiv, X, 0);

  if (Ssz - sz > SZ_LISTA)
    buraco_var_insere(FIndiv, Ssz - sz - SZ_REG, ftell(FIndiv));
}

void individuo_insere_lab3(FILE *fp) {
  int n,i;
  Individuo X;

  fscanf(fp, " %d", &n);
  for(i=0 ; i<n ; i++) {
    X = individuo_read_lab3(fp);

    if (indice_busca("individuo", X.idI) != FAIL) {
      fprintf(stderr, "ERRO [individuo_insere]: Ja ha registro de individuo com esse id.\n");
      fprintf(stderr, "ERRO AQUI: <%d>\n", X.idI);
      return;
    }
    if (indice_busca("especie", X.idE) == FAIL) {
      fprintf(stderr, "ERRO [individuo_insere]: A especie associada nao existe.\n");
      return;
    }

    individuo_insere_(X);
    muda_n(FIndiv, +1);
    indice_fail(SISecIndiv);
    indice_fail(SIPrimIndiv);
    indice_sec_insere("individuo", X.idE, X.idI);
  }
}

/* INDIVÍDUO LÊ
 * lê todos os registros de indivíduos e os imprime na tela */
void individuo_le() {
  Individuo X;
  int i;
  system("clear");

  puts("** LEITURA INDIVIDUOS **");
  printf("\n");

  for (i = 0; i < N_IPIndiv; i++) {
    fseek(FIndiv, IPIndiv[i].offset, SEEK_SET);
    X = individuo_read(FIndiv, NULL, NULL);
    individuo_write(stdout, X, 1);
  }

  Pause();
}

/* INDIVÍDUO DELETA
 * deleta um registro de indivíduo de ID dado pelo usuário
 * - a deleção reflete em alteração no índice primário
 * - a deleção reflete em alteração no índice secundário */
void individuo_deleta() {
  int id, sz;
  Individuo X;
  system("clear");

  puts("** DELECAO INDIVIDUO **");
  printf("Digite o ID do individuo a ser deletado: ");
  scanf(" %d", &id);

  sz = individuo_busca_lab2(id, &X);
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
    indice_deleta("individuo", id);
    indice_sec_deleta("individuo", id, X.idE);
  }
}

/* INDIVÍDUO DELETA 2
 * função mais baixo nível para deleção
 * - insere o espaço na lista ligada de buracos */
void individuo_deleta_(int sz) {
  int save, szY;
  Individuo Y;

  if (buraco_var_insere(FIndiv, sz, (int) ftell(FIndiv)) == FAIL) {
    /* registro muito pequeno para a lista ligada */

    /* vai para o registro seguinte */
    individuo_read(FIndiv, &save, NULL);
    Y = individuo_read(FIndiv, NULL, &szY);

    /* volta para a posicao do anterior e reescreve Y */
    fseek(FIndiv, save, SEEK_SET);
    reg_escreve(FIndiv, sz + szY + SZ_REG);
    individuo_write(FIndiv, Y, 0);
  }
}

/* INDIVÍDUO ATUALIZA
 * lê o ID da indivíduo a ser atualizado e
 * modifica seus valores conforme digitado pelo usuário
 * - equivale a uma remoção seguida de inserção */
void individuo_atualiza() {
  int id, sz;
  Individuo X;
  system("clear");

  puts("** ATUALIZACAO INDIVIDUOS **");
  printf("Digite o ID do individuo a ter dados alterados: ");
  scanf(" %d", &id);

  sz = individuo_busca_lab2(id, &X);
  if (sz == -1) {
    puts("Nao existe individuo com este ID!\n");
    Pause();
  } else {
    individuo_deleta_(sz);
    indice_fail(SIPrimIndiv);
    indice_fail(SISecIndiv);
    indice_deleta("individuo", X.idI);

    printf("ID do Individuo: ");
    printf("%d\n", X.idI);
    printf("ID da Especie: ");
    printf("%d\n", X.idE);
    muda_int(&X.idE);
    printf("Sexo: ");
    printf("%c\n", X.sexo);
    muda_char(&X.sexo);

    /* insere de volta */
    indice_sec_insere("individuo", X.idI, X.idE);
    individuo_insere_(X);
  }
}

/* INDIVÍDUO READ
 * lê de arquivo texto um único registro de espécie
 * - 'save' indica a posição imediatamente anterior ao registro
 * - 'sz' indica o tamanho virtual do registro
 * - ao término da função, o ponteiro do arquivo está posicionado
 * imediatamente antes do próximo registro */
Individuo individuo_read(FILE* fin, int *_save, int *_sz) {
  Individuo X;
  BuracoVar L;
  int jump, save;
  char c;

  save = (int) ftell(fin);

  fscanf(fin, " %c", &c);
  if (c == VAZIO) {
    buraco_var_le(fin, &L);
    fseek(fin, L.sz - (SZ_LISTA-SZ_REG), SEEK_CUR);

    X.idI = -1;
    return X;
  }

  fscanf(fin, " %d", &jump);
  X = individuo_read_(fin);

  fseek(fin, save + jump + SZ_REG, SEEK_SET);

  if (_save != NULL)
    *_save = save;
  if (_sz != NULL)
    *_sz = jump;

  return X;
}

/* INDIVÍDUO READ 2
 * lê de arquivo texto ou teclado um registro de indivíduo */
Individuo individuo_read_(FILE *fin) {
  Individuo X;
  int print = (fin == stdin) ? (1) : (0);

  if (print) printf("ID do Individuo: ");
  fscanf(fin, " %d", &X.idI);
  if (print) printf("ID da Especie: ");
  fscanf(fin, " %d", &X.idE);
  if (print) printf("Sexo: ");
  fscanf(fin, " %c", &X.sexo);

  return X;
}

Individuo individuo_read_lab3(FILE *fin) {
  Individuo X;
  char *linha, *tok;

  fscanf(fin," %a[^\r\n]", &linha);

  tok = strtok(linha, "|");
  sscanf(tok, " %d", &X.idE);

  tok = strtok(NULL, "|");
  sscanf(tok, " %d", &X.idI);

  tok = strtok(NULL, "|");
  sscanf(tok, " %c", &X.sexo);

  free(linha);
  return X;
}

/* INDIVÍDUO WRITE
 * escreve em arquivo txt ou na tela
 * um único registro de indivíduo */
void individuo_write(FILE *fout, Individuo X, int print) {
  if (print) printf("ID do Individuo: ");
  fprintf(fout, "%d\n", X.idI);
  if (print) printf("ID da Especie: ");
  fprintf(fout, "%d\n", X.idE);
  if (print) printf("Sexo: ");
  fprintf(fout, "%c\n", X.sexo);

  if (print) printf("\n");
}

/* INDIVÍDUO CONTA CARACTERES
 * devolve o número de bytes que o registro ocupará
 * quando escrito em arquivo texto */
int individuo_conta_caracteres(Individuo X) {
  int idI, idE;

  idI = 0;
  if (X.idI == 0)
    idI = 1;
  while (X.idI) {
    idI++;
    X.idI /= 10;
  }

  idE = 0;
  if (X.idE == 0)
    idE = 1;
  while (X.idE) {
    idE++;
    X.idE /= 10;
  }

  return ((idI+1)
	  + (idE+1)
	  + (1));
}
