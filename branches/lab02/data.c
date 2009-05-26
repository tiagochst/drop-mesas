#include <stdio.h>
#include "data.h"

/* LÊ DATA
 * lê do arquivo fp uma data e a devolve */
Data data_le(FILE *fp) {
	Data X;
	fscanf(fp, "%2d%2d%4d", &X.dia, &X.mes, &X.ano);
	return X;
}

/* ESCREVE DATA
 * escreve a data X no arquivo fp */
void data_escreve(FILE *fp, Data X) {
	fprintf(fp, "%02d%02d%04d\n", X.dia, X.mes, X.ano);
}

/* COMPARA DATA
 * faz comparação entre duas datas
 * devolve número menor que 0 se d1 < d2;
 * número maior que 0 se d1 > d2
 * e 0 caso d1 = d2 */
int data_cmp(Data d1, Data d2) {
	if (d1.ano == d2.ano) {
		if (d1.mes == d2.mes) {
			return d1.dia - d2.dia;
		}
		else return d1.mes - d2.mes;
	}
	else return d1.ano - d2.ano;
}
