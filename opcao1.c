#include "definicoes.h"

void opcao1() {
	int i;

	for (i=0; i<NFile; i++) {
		gera_vetor(File[i], muda_ext(FileNames[i], "vet"));
	}
}

void gera_vetor(FILE *fp, char *arq_vet) {
}
