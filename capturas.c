#include "definicoes.h"

int captura_busca(int idC, Captura *K) {
  int i, k, n, avail_list, save;
  Captura X;

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  fread(&avail_list, sizeof(int), 1, FCaptu);
  for (i=0, k=-1; i<n; i++) {
    save = (int) ftell(FCaptu);
    X = captura_read(FCaptu);

    if (X.idC == FAIL)
      i--;
    if (X.idC == idC) {
      k = i;
      break;
    }
  }

  if (k == -1)
    return FAIL;
  if (K != NULL)
    *K = X;

  fseek(FCaptu, save, SEEK_SET);
  return OK;
}

/* CAPTURA INSERE
   Le os valores da entrada padrao e insere no arquivo
   de tamanho fixo  */
void captura_insere() {
  Captura X;
  system("clear");

  puts("** INSERE CAPTURA **");
  X = captura_read_(stdin);
  if(captura_busca(X.idC, NULL) != FAIL) {
    puts("\nJa ha registro de captura com esse id.");
    puts("Insercao falhou.");
    Pause();
    return;
  }
  if(indice_busca("individuo", X.idI) == FAIL) {
    puts("\nO individuo associado nao existe.");
    puts("Insercao falhou.");
    Pause();
    return;
  }

  captura_insere_(X);

  puts("Captura inserida corretamente.");
}

void captura_insere_(Captura X) {
  int pos;

  pos = buraco_fixo_busca_vazio(FCaptu);
  if(pos == FAIL) {
    fseek(FCaptu, 0, SEEK_END);
  } else {
    fseek(FCaptu, pos, SEEK_SET);
    buraco_fixo_remove(FCaptu);
  }
  
  indice_sec_insere("captura",X.idI,ftell(FCaptu));
  captura_write(FCaptu, &X);
  muda_n_bin(FCaptu, +1);
}

void captura_atualiza() {
  int idC;
  Captura X;

  system("clear");

  puts("** ATUALIZACAO CAPTURAS **");
  printf("Digite o ID da captura: ");
  scanf(" %d", &idC);

  if (captura_busca(idC, &X) == FAIL) {
    puts("Nao existe captura com este ID!\n");
    Pause();
  } else {
      printf("ID da captura: ");
      printf("%d\n", X.idC);
      printf("ID do individuo: ");
      printf("%d\n", X.idI);
      muda_int(&X.idI);
      printf("Comprimento: ");
      printf("%d\n", X.comprimento);
      muda_int(&X.comprimento);
      printf("Largura: ");
      printf("%d\n", X.largura);
      muda_int(&X.largura);
      printf("Peso: ");
      printf("%d\n", X.peso);
      muda_int(&X.peso);
      printf("Data de Captura: ");
      data_escreve(stdout, X.data);
      muda_Data(&X.data);
      printf("Local de Captura: ");
      printf("%s\n", X.local);
      muda_string(X.local);

      captura_write(FCaptu, &X);
  }
}

void captura_le() {
  int n, avail_list;
  Captura aux;
  system("clear");

  puts("** LEITURA CAPTURAS **");
  printf("\n");

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  fread(&avail_list, sizeof(int), 1, FCaptu);
  while (n--) {
    aux = captura_read(FCaptu);
    if (aux.idC == FAIL)
      n++;
    else
      captura_write_(stdout, aux, 1);
  }

  Pause();
}

void captura_deleta() {
  int idC;
  Captura X;

  system("clear");

  puts("** DELECAO CAPTURA **");
  printf("Digite o ID da captura a ser deletada: ");
  scanf(" %d", &idC);

  if(captura_busca(idC, &X) == FAIL) {
    puts("Nao existe captura com este ID!\n");
    Pause();
  } else {
    captura_write_(stdout, X, 1);
    if (!Pergunta("Confirma exclusao?"))
      return;

    buraco_fixo_insere(FCaptu, (int)ftell(FCaptu));
	muda_n_bin(FCaptu, -1);
  }
}

Captura captura_read(FILE *fin) {
  BuracoFixo B;
  Captura X;
  int save;
  char c;

  fread(&c, sizeof(char), 1, fin);
  if(c == VAZIO) {
    save = (int) ftell(fin);
    buraco_fixo_le(fin, &B);

    fseek(fin, save+sizeof(Captura), SEEK_SET);

    X.idC = FAIL;
    return X;
  }

  fread(&X, sizeof(Captura), 1, fin);
  return X;
}

Captura captura_read_(FILE *fin) {
  Captura X;
  int print = (fin==stdin) ? (1) : (0);

  if (print)
    printf("ID da Captura: ");
  fscanf(fin, " %d", &X.idC);
  if (print)
    printf("ID do Individuo: ");
  fscanf(fin, " %d", &X.idI);
  if (print)
    printf("Comprimento: ");
  fscanf(fin, " %d", &X.comprimento);
  if (print)
    printf("Largura: ");
  fscanf(fin, " %d", &X.largura);
  if (print)
    printf("Peso: ");
  fscanf(fin, " %d", &X.peso);
  if (print)
    printf("Data de Captura: ");
  X.data = data_le(fin);
  if (print)
    printf("Local de Captura: ");
  fscanf(fin, " %[^\n]", X.local);

  return X;
}

void captura_write(FILE *fout, Captura *X) {
  char c = USADO;
  fwrite(&c, sizeof(char), 1, fout);
  fwrite(X, sizeof(Captura), 1, fout);
}

void captura_write_(FILE *fout, Captura X, int print) {
  if (print)
    printf("ID da Captura: ");
  fprintf(fout, "%d\n", X.idC);
  if (print)
    printf("ID do Individuo: ");
  fprintf(fout, "%d\n", X.idI);
  if (print)
    printf("Comprimento: ");
  fprintf(fout, "%d\n", X.comprimento);
  if (print)
    printf("Largura: ");
  fprintf(fout, "%d\n", X.largura);
  if (print)
    printf("Peso: ");
  fprintf(fout, "%d\n", X.peso);
  if (print)
    printf("Data de Captura: ");
  data_escreve(fout, X.data);
  if (print)
    printf("Local de Captura: ");
  fprintf(fout, "%s\n", X.local);

  if (print)
    printf("\n");
}
