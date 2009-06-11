#ifndef DEFINICOES_H_
#define DEFINICOES_H_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conjunto.h"

extern int NFile;
extern char** FileNames;
extern FILE** File;

/* funcoes.c */
int print_menu();
void Pause();
char* muda_ext(char *file, char *nova_ext);
FILE* Fopen(char *file, char *modo);
void files_start();
void files_end();

/* opcao1.c */
void opcao1();
void gera_vetor(FILE *fp, char *arq_vet);

/* opcao2.c */
void opcao2();

#endif /*DEFINICOES_H_*/
