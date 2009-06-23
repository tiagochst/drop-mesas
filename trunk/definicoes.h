#ifndef DEFINICOES_H_
#define DEFINICOES_H_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "conjunto.h"

typedef struct {
  char *s;
  double peso;
} Termo;

extern const char *print_double;

extern int NFile;
extern char** FileNames;
extern FILE** File;
extern Conjunto** FileWords;

/* funcoes.c */
int print_menu();
char* muda_ext(char *file, char *nova_ext);
void strtoupper(char *s);
FILE* Fopen(char *file, char *modo);
void files_start();
void files_start_read(FILE *fp, Conjunto **c);
void files_end();
void Pause();

/* termo.c */
int Termo_cmp(void *a, void *b);
double Termo_prod(void *a, void *b);
void Termo_free(void *a);
void Termo_copy(void **a, void **b);
Conjunto *Termo_strtokenizer(char *s);

/* opcao1.c */
void opcao1();
void tfIdf(int i, char *arq_vet);

/* opcao2.c */
void opcao2();
void bagOfWords(char *file);
void cosseno(char *file);
void okapi(char *file);
void normaliza_gauss(double *data, int N);

/* opcao3.c */
void opcao3();
double **le_matriz(char *file,int *n);
double **calcula_media(double **v1,double **v2,double **v3,int n);
void compara(double **vet,int n);
int comp1(const void *a,const void *b);
int comp2(const void *a,const void *b);
void limpa_matrix(double **v,int n);

#endif /*DEFINICOES_H_*/
