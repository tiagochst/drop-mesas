#include "definicoes.h"

int captura_busca(int idC, Captura *K) {
  int i, k, n;
  Captura X;

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  for (i=0, k=-1; i<n; i++) {
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

  fseek(FCaptu, -sizeof(Captura), SEEK_CUR);
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
    Pause();
    return;
  }
  if(indice_busca("individuo", X.idI) == FAIL) {
    puts("\nO individuo associado nao existe.");
    Pause();
    return;
  }

  captura_insere_(X);
}

void captura_insere_(Captura X) {
  int n;
  Captura aux;

  fseek(FCaptu, 0, SEEK_SET);

  fread(&n, sizeof(int), 1, FCaptu);
  while (n--) {
    aux = captura_read(FCaptu);
    if (aux.idC == FAIL) {
      fseek(FCaptu, -sizeof(Captura), SEEK_CUR);
      break;
    }
  }

  fwrite(&X, sizeof(Captura), 1, FCaptu);

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

      fwrite(&X, sizeof(Captura), 1, FCaptu);
  }
}

void captura_le() {
  int n;
  Captura aux;
  system("clear");

  puts("** LEITURA CAPTURAS **");
  printf("\n");

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  while (n--) {
    aux = captura_read(FCaptu);
    if (aux.idC == FAIL)
      n++;
    else
      captura_write(stdout, aux, 1);
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
    captura_write(stdout, X, 1);
    if (!Pergunta("Confirma exclusao?"))
      return;

	X.idC = FAIL;
	fwrite(&X, sizeof(Captura), 1, FCaptu);
	muda_n_bin(FCaptu, -1);
  }
}

Captura captura_read(FILE *fin) {
  Captura X;
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

void captura_write(FILE *fout, Captura X, int print) {
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
