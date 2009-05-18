#include <stdio.h>
#include "data.h"

Data data_le(FILE *fp) {
	Data X;
	fscanf(fp, "%2d%2d%4d", &X.dia, &X.mes, &X.ano);
	return X;
}

void data_escreve(FILE *fp, Data X) {
	fprintf(fp, "%02d%02d%04d\n", X.dia, X.mes, X.ano);
}

int data_cmp(Data d1, Data d2) {
	if (d1.ano == d2.ano) {
		if (d1.mes == d2.mes) {
			return d1.dia - d2.dia;
		}
		else return d1.mes - d2.mes;
	}
	else return d1.ano - d2.ano;
}
