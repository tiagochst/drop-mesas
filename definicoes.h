#ifndef DEFINICOES_H_
#define DEFINICOES_H_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "conjunto.h"

extern int NFile;
extern char** FileNames;
extern FILE** File;
extern Conjunto** FileWords;

/* funcoes.c */
int print_menu();
char* muda_ext(char *file, char *nova_ext);
FILE* Fopen(char *file, char *modo);
void files_start();
void files_start_read(FILE *fp, Conjunto **c);
void files_end();
int strcmp_(void *a, void *b);
Conjunto *strtokenizer(char *s);

/* opcao1.c */
void opcao1();
void gera_vetor(FILE *fp, char *arq_vet);

/* opcao2.c */
void opcao2();
void bagOfWords(char *file);
void cosseno(char *file);
void okapi(char *file);
void normaliza_gauss(double *data, int N);

#endif /*DEFINICOES_H_*/
