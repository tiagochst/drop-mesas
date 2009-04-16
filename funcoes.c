#include "definicoes.h"

int print_menu(int x) {
  int in, max;

  system("clear");
  if(x==0) {
    /* menu principal */
    puts("**************************");
    puts("* Gerenciar dados sobre: *");
    puts("* 1. especies            *");
    puts("* 2. individuos          *");
    puts("* 3. captura             *");
    puts("* 4. consultas           *");
    puts("*                        *");
    puts("* 0. sair do programa    *");
    puts("**************************");

    max = 4;
  }
  else if(x==1) {
    /* especies */
    puts("**************************");
    puts("* ESPECIES               *");
    puts("* efetuar:               *");
    puts("* 1. insercao            *");
    puts("* 2. leitura             *");
    puts("* 3. atualizacao         *");
    puts("* 4. delecao             *");
    puts("*                        *");
    puts("* 0. menu principal      *");
    puts("**************************");

    max = 4;
  }
  else if(x==2) {
    /* individuos */
    puts("**************************");
    puts("* INDIVIDUOS             *");
    puts("* efetuar:               *");
    puts("* 1. insercao            *");
    puts("* 2. leitura             *");
    puts("* 3. atualizacao         *");
    puts("* 4. delecao             *");
    puts("*                        *");
    puts("* 0. menu principal      *");
    puts("**************************");

    max = 4;
  }
  else if(x==3) {
    /* capturas */
    puts("**************************");
    puts("* CAPTURAS               *");
    puts("* efetuar:               *");
    puts("* 1. insercao            *");
    puts("* 2. leitura             *");
    puts("* 3. atualizacao         *");
    puts("* 4. delecao             *");
    puts("*                        *");
    puts("* 0. menu principal      *");
    puts("**************************");

    max = 4;
  }
  else if(x==4) {
    /* capturas */
    puts("***************************************************************");
    puts("* CONSULTAS                                                   *");
    puts("* efetuar:                                                    *");
    puts("* 1. Dado um individuo, exibir seu historico de monitoramento *");
    puts("* 2. Dado um individuo, exibir os dados da ultima captura     *");
    puts("* 3. Dada uma especie e um peso minimo, mostrar dados da      *");
    puts("*     ultima captura de individuos dessa especie              *");
    puts("* 4. Dado um individuo, exibir o caminho do arquivo de imagem *");
    puts("*     de sua especie                                          *");
    puts("*                                                             *");
    puts("* 0. menu principal                                           *");
    puts("***************************************************************");

    max = 4;
  }
  else {
    return 0;
  }

  scanf(" %d", &in);
  while(in<0 || in>max) {
    puts("Entrada incorreta. Digite novamente");
    scanf(" %d", &in);
  }
  return in;
}

void muda_string(char *s) {
  char c;

  printf("Deseja alterar este valor? (y/n) ");
  while(scanf("%c", &c)==1 && tolower(c)!='y' && tolower(c)!='n');
  if(tolower(c)=='n') return;

  printf("Digite o novo valor: ");
  scanf(" %s", s);
}

void muda_int(int *i) {
  char c;

  printf("Deseja alterar este valor? (y/n) ");
  while(scanf("%c", &c)==1 && tolower(c)!='y' && tolower(c)!='n');
  if(tolower(c)=='n') return;

  printf("Digite o novo valor: ");
  scanf(" %d", i);
}

void muda_char(char *x) {
  char c;

  printf("Deseja alterar este valor? (y/n) ");
  while(scanf("%c", &c)==1 && tolower(c)!='y' && tolower(c)!='n');
  if(tolower(c)=='n') return;

  printf("Digite o novo valor: ");
  scanf(" %c", x);
}

void Pause() {
  char c;
  puts("Pressione (q) para continuar. . .");
  while(scanf("%c", &c)==1 && tolower(c)!='q');
}

int Pergunta(char *s) {
  char c;
  puts(s);
  puts("Pressione (s)im ou (n)ao. . .");
  while(scanf("%c", &c)==1 && tolower(c)!='s' && tolower(c)!='n');
  return (tolower(c)=='s')?(1):(0);
}

FILE *open_file(char *s) {
  FILE *fp = fopen(s, "r+");

  if(fp == NULL) {
    fp = fopen(s, "w+");
    fprintf(fp, "%03d\n", 0); /* numero de registros */
    lista_escreve(fp, SZ_REG, -1, -1); /* no cabeca */
  }

  return fp;
}

FILE *open_file_bin(char *s) {
  int zero = 0;
  FILE *fp = fopen(s, "r+b");

  if(fp == NULL) {
    fp = fopen(s, "w+b");
    fwrite(&zero,sizeof(int),1,fp);
  }

  return fp;
}
