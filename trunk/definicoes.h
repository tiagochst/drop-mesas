#ifndef _DEFINICOES_H_
#define _DEFINICOES_H_

/** includes **/
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "conjunto.h"
#include "data.h"
#include "lista_buraco_var.h"
#include "lista_buraco_fixo.h"

/** defines **/
#define SZ_CAB (4)
#define SZ_LISTA (21)
#define SZ_REG (9)

#define VAZIO '*'
#define USADO '#'

#define OK   (1)
#define FAIL (-1)

/** estruturas **/
typedef struct {
	int id;
	int offset;
} Indice_Prim;

typedef struct {
	int idP;
	int idS;
} Indice_Sec;

typedef struct {
	int id;
	char camin[256];
	Data data;
	char nomec[31];
	char nomep[31];
	char descr[501];
} Especie;

typedef struct {
	int idE;
	int idI;
	char sexo;
} Individuo;

typedef struct {
	int idC;
	int idI;
	int comprimento;
	int largura;
	int peso;
	Data data;
	char local[51];
} Captura;

typedef struct {
	int idE;
	int next;
} ListaInv_Prim;

typedef struct {
	char s[30];
	int ind1;
} ListaInv_Sec;

/** variaveis extern **/
extern FILE *FIndiv;
extern FILE *FEspec;
extern FILE *FCaptu;
extern FILE *FInvPrim;
extern FILE *FInvSec;
extern FILE *FIPrimEspec;
extern FILE *FIPrimIndiv;
extern FILE *FISecIndiv;
extern FILE *FISecCaptu;

extern char *SIPrimEspec;
extern char *SIPrimIndiv;
extern char *SISecIndiv;
extern char *SISecCaptu;

extern Indice_Prim *IPEspec;
extern int N_IPEspec;

extern Indice_Prim *IPIndiv;
extern int N_IPIndiv;

extern Indice_Sec *ISIndiv;
extern int N_ISIndiv;

extern Indice_Sec *ISCaptu;
extern int N_ISCaptu;

/** prototipos das funcoes **/
int print_menu(int x);
int print_menu_lab3();
void muda_string(char *s);
void muda_int(int *i);
void muda_char(char *x);
void muda_Data(Data *d);
void Pause();
int Pergunta(char *s);
FILE *open_file(char *s);
FILE *open_file_bin(char *s);
void reg_escreve(FILE *fp, int sz);
void muda_n(FILE *fp, int var);
void muda_n_bin(FILE *fp, int var);
int strcmp_(void *a, void *b);
int intcmp_(void *a, void *b);
void strtoupper(char *s);

void captura_insere();
void captura_insere_lab3(FILE *fp);
Captura captura_read_lab3(FILE *fp);
void captura_insere_(Captura X);
void captura_atualiza();
void captura_le();
void captura_deleta();
Captura captura_read(FILE *fin);
Captura captura_read_(FILE *fin);
void captura_write(FILE *fout, Captura *X);
void captura_write_(FILE *fout, Captura X, int print);

int especie_busca_lab1(int id, Especie *K);
int especie_busca_lab2(int id, Especie *K);
void especie_insere();
void especie_insere_lab3(FILE *fp);
Especie especie_read_lab3(FILE *fin);
void especie_insere_(Especie X);
void especie_le();
void especie_deleta();
void especie_deleta_(int sz);
void especie_atualiza();
Especie especie_read(FILE *fin, int *_save, int *_sz);
Especie especie_read_(FILE *fin);
void especie_write(FILE *fout, Especie X, int print);
int especie_conta_caracteres(Especie X);

int individuo_busca_lab1(int id, Individuo *K);
int individuo_busca_lab2(int id, Individuo *K);
void individuo_insere();
void individuo_insere_lab3(FILE *fp);
Individuo individuo_read_lab3(FILE *fin);
void individuo_insere_(Individuo X);
void individuo_le();
void individuo_deleta();
void individuo_deleta_(int sz);
void individuo_atualiza();
Individuo individuo_read(FILE* fin, int *_save, int *_sz);
Individuo individuo_read_(FILE *fin);
void individuo_write(FILE *fout, Individuo X, int print);
int individuo_conta_caracteres(Individuo X);

void historico_monitoramento_lab1();
void historico_monitoramento_lab2();
void ultima_captura_lab1();
void ultima_captura_lab2();
void ultima_captura_peso_lab1();
void ultima_captura_peso_lab2();
void caminho_especie_lab1();
void caminho_especie_lab2();
void busca_especie_descricao();

void indice_start(char *espec, char *indiv);
void indice_end(char *espec, char *indiv);
void indice_insere(char *op, int offset, int id);
void indice_deleta(char *op, int id);
void indice_fail(char *sfp);
int indice_busca(char *op, int id);

void indice_sec_start(char *indiv, char *captu);
void indice_sec_end(char *indiv, char *captu);
void indice_sec_insere(char *op, int idS, int idP);
void indice_sec_deleta(char *op, int idS, int idP);
int indice_sec_busca(char *op, int id);

void lista_inv_start(char *prim, char *sec);
void lista_inv_end();
void lista_inv_write();
void lista_inv_insere(char *s, int id);
int lista_inv_insere_(char *s, int id);
int lista_inv_Sec_busca(char *s);
int lista_inv_Prim_insere(int k, int id);
int lista_inv_Sec_insere(char *s, int ind1);
void lista_inv_Prim_deleta(int *k, int id);
void lista_inv_deleta_(char *s, int id);
void lista_inv_busca(char *s);
void lista_inv_deleta(char *s, int id);
void lista_inv_atualiza(char *velho, char *novo, int id);

#endif /*_DEFINICOES_H_*/
