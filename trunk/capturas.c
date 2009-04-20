#include "definicoes.h"

/* CAPTURA INSERE
   Le os valores da entrada padrao e insere no arquivo
   de tamanho fixo  */
void captura_insere(){
  Captura X;
  system("clear");

  puts("** INSERE CAPTURA **");
  X = captura_read_(stdin);

  captura_insere_(X);
}

void captura_insere_(Captura X){
  int n;
  Captura aux;

  fseek(FCaptu, 0, SEEK_SET);

  fread(&n, sizeof(int), 1, FCaptu);
  while(n--) {
    aux = captura_read(FCaptu);
    if(aux.id == -1){
      fseek(FCaptu, -sizeof(Captura), SEEK_CUR);
      break;
    }
  }

  fwrite(&X, sizeof(Captura), 1, FCaptu);

  muda_n_bin(FCaptu, +1);
}

void captura_atualiza(){
  int id, i,n;
  Captura aux;

  system("clear");

  puts("** ATUALIZACAO CAPTURAS **");
  printf("Digite o ID: ");
  scanf(" %d", &id);

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  
  for(i=0 ; i<n ; i++){
    aux = captura_read(FCaptu);

    if(aux.id == -1) i--;
    else if(aux.id == id){
      printf("ID: ");
      printf("%d\n", aux.id);
      muda_int(&aux.id);
      printf("Comprimento: ");
      printf("%d\n", aux.comprimento);
      muda_int(&aux.comprimento);
      printf("Largura: ");
      printf("%d\n", aux.largura);
      muda_int(&aux.largura);
      printf("Peso: ");
      printf("%d\n", aux.peso);
      muda_int(&aux.peso);
      printf("Data de Captura: ");
      printf("%d\n", aux.data);
      muda_int(&aux.data);
      printf("Local de Captura: ");
      printf("%s\n", aux.local);
      muda_string(aux.local);

      fseek(FCaptu, -sizeof(Captura), SEEK_CUR);
      fwrite(&aux, sizeof(Captura), 1, FCaptu);

      return;
    }
  }

  printf("Nao foram encontradas capturas do individuo de ID %d\n", id);
  Pause();
}

void captura_le(){
  int n;
  Captura aux;
  system("clear");

  puts("** LEITURA CAPTURAS **");
  printf("\n");

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  while(n--){
    aux = captura_read(FCaptu);
    if(aux.id == -1) n++;
    else captura_write(stdout, aux, 1);
  }

  Pause();
}

void captura_deleta(){
  int id, n;
  Captura aux;

  system("clear");

  puts("** DELECAO CAPTURA **");
  printf("Digite o ID do individuo capturado a ser deletado: ");
  scanf(" %d", &id);

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  while(n--) {
    aux = captura_read(FCaptu);
    if(aux.id == -1) n++;
    else if(aux.id == id) {
      captura_write(stdout, aux, 1);

      if(Pergunta("Voce deseja apagar este registro?")) {
	fseek(FCaptu, -sizeof(Captura), SEEK_CUR);
	aux.id = -1;
	fwrite(&aux, sizeof(Captura), 1, FCaptu);

	/* reduz o número de registros no cabeçalho */
	muda_n_bin(FCaptu, -1);

	return;
      }
    }
  }

  printf("Nao foram encontradas capturas do individuo de ID %d\n", id);
  Pause();
}

Captura captura_read(FILE *fin) {
  Captura X;
  fread(&X, sizeof(Captura), 1, fin);
  return X;
}

Captura captura_read_(FILE *fin) {
  Captura X;
  int print = (fin==stdin)?(1):(0);

  if(print) printf("ID: ");
  fscanf(fin, " %d", &X.id);
  if(print) printf("Comprimento: ");
  fscanf(fin, " %d", &X.comprimento);
  if(print) printf("Largura: ");
  fscanf(fin, " %d", &X.largura);
  if(print) printf("Peso: ");
  fscanf(fin, " %d", &X.peso);
  if(print) printf("Data de Captura: ");
  fscanf(fin, " %d", &X.data);
  if(print) printf("Local de Captura: ");
  fscanf(fin, " %[^\n]", X.local);

  return X;
}

void captura_write(FILE *fout, Captura X, int print) {
  if(print) printf("ID do Individuo: ");
  fprintf(fout, "%d\n", X.id);
  if(print) printf("Comprimento: ");
  fprintf(fout, "%d\n", X.comprimento);
  if(print) printf("Largura: ");
  fprintf(fout, "%d\n", X.largura);
  if(print) printf("Peso: ");
  fprintf(fout, "%d\n", X.peso);
  if(print) printf("Data de Captura: ");
  fprintf(fout, "%d\n", X.data);
  if(print) printf("Local de Captura: ");
  fprintf(fout, "%s\n", X.local);

  if(print) printf("\n");
}
