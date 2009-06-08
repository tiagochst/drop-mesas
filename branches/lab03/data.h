#ifndef DATA_H_
#define DATA_H_

typedef struct {
	int dia, mes, ano;
} Data;

/* tamanho ocupado por uma estrutura de data
 * se escrita em arquivo texto */
#define SZ_DATA (8)

Data data_le(FILE *fp);
Data data_le_str(char *s);
void data_escreve(FILE *fp, Data X);
int data_cmp(Data d1, Data d2);

#endif /* DATA_H_ */
