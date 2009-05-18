#ifndef DATA_H_
#define DATA_H_

typedef struct {
	int dia, mes, ano;
} Data;

#define SZ_DATA (8)

Data data_le(FILE *fp);
void data_escreve(FILE *fp, Data X);
int data_cmp(Data d1, Data d2);

#endif /* DATA_H_ */
