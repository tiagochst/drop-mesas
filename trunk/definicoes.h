#ifndef _DEFINICOES_H_
#define _DEFINICOES_H_

/** includes **/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/** defines **/
#define SZ_LISTA (13)
#define SZ_1 (4)
#define SZ_2 (SZ_LISTA)
#define SZ_CAB (SZ_1 + SZ_2)

#define SZ_REG (7)

#define VAZIO '*'
#define USADO '#'

#define OK   (1)
#define FAIL (-1)

/** variaveis extern **/
extern FILE *FIndiv;
extern FILE *FEspec;
extern FILE *FCaptu_fix;
extern FILE *FCaptu_var;

/** estruturas **/
typedef struct {
  int id;
  char camin[256];
  int data;
  char nomec[31];
  char nomep[31];
  char descr[501];
} Especie;

typedef struct {
  int idE;
  int idI;
  char sexo;
} Individuo;

typedef struct{
  int id;
  int comprimento;
  int largura;
  int peso;
  int data;
  char local[51];
} Captura;

typedef struct {
  int sz, prev, next;
} Lista;

/** prototipos das funcoes **/
int print_menu(int x);
void muda_string(char *s);
void muda_int(int *i);
void muda_char(char *x);
void Pause();
int Pergunta(char *s);
FILE *open_file(char *s);
FILE *open_file_bin(char *s);
void muda_n(FILE *fp, int var);

void captura_insere();
void captura_insere_fix(Captura X);
void captura_insere_var(Captura X);
void captura_atualiza();
void captura_atualiza_fix(int id);
void captura_le();
void captura_le_fix();
void captura_le_var();
void captura_deleta();
int captura_deleta_fix(int id);
Captura captura_read(FILE *fin, int print);
void captura_write(FILE *fout, Captura X, int print);
Captura captura_read_var(FILE *fin);
void captura_write_var(FILE *fout, Captura X);
int captura_conta_bytes(Captura X);

int especie_busca(int id, Especie *K);
void especie_insere();
void especie_insere_(Especie X);
void especie_le();
void especie_deleta();
void especie_deleta_(int sz);
void especie_atualiza();
Especie especie_read(FILE *fin, int *_save, int *_sz);
Especie especie_read_(FILE *fin);
void especie_write(FILE *fout, Especie X, int print);
int especie_conta_caracteres(Especie X);

int individuo_busca(int id, Individuo *K);
void individuo_insere();
void individuo_insere_(Individuo X);
void individuo_le();
void individuo_deleta();
void individuo_deleta_(int sz);
void individuo_atualiza();
Individuo individuo_read(FILE* fin, int *_save, int *_sz);
Individuo individuo_read_(FILE *fin);
void individuo_write(FILE *fout, Individuo X, int print);
int individuo_conta_caracteres(Individuo X);

void lista_escreve(FILE *fp, int sz, int prev, int next);
int lista_le(FILE *fp, Lista *x);
int lista_busca_vazio(FILE *fp, int sz);
int lista_insere(FILE *fp, int sz, int pos);
void lista_remove(FILE *fp);

void historico_monitoramento();
void ultima_captura();
void ultima_captura_peso();
void caminho_especie();

#endif
