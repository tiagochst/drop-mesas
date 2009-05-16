#include "definicoes.h"

Indice_Prim *IEspec;
Indice_Prim *IIndiv;

int N_IEspec;
int N_IIndiv;

void indice_start(char *espec, char *indiv) {
	int i, n;
	int flag;
	FIndEspec = fopen(espec, "rb");
	FIndIndiv = fopen(indiv, "rb");

	IEspec = NULL;
	IIndiv = NULL;

	n = 0;
	if (FIndEspec != NULL) {
		fread(&n, sizeof(int), 1, FIndEspec);
		fread(&flag, sizeof(int), 1, FIndEspec);
		if (flag == FAIL) {
			/*reconstroi_indice();*/
		} else {
			IEspec = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
			fread(IEspec, sizeof(Indice_Prim), n, FIndEspec);

			N_IEspec = n;
		}
	} else
		N_IEspec = 0;

	n = 0;
	if (FIndIndiv != NULL) {
		fread(&n, sizeof(int), 1, FIndIndiv);
		fread(&flag, sizeof(int), 1, FIndIndiv);
		if (flag == FAIL) {
			/*reconstroi_indice();*/
		} else {
			IIndiv = (Indice_Prim *) malloc(n*sizeof(Indice_Prim));
			fread(IIndiv, sizeof(Indice_Prim), n, FIndIndiv);

			N_IIndiv = n;
		}
	} else
		N_IIndiv = 0;

	for (i=0; i<n; i++)
		printf("%d %d\n", IEspec[i].id, IEspec[i].offset);

	printf("%d\n", N_IEspec);
}

void indice_end(char *s) {
	int i;
	int n;
	int flag= OK;
	FIndEspec = fopen(s, "wb");

	n = N_IEspec;

	for (i=0; i<n; i++)
		printf("%d %d\n", IEspec[i].id, IEspec[i].offset);

	fwrite(&n, sizeof(int), 1, FIndEspec);
	fwrite(&flag, sizeof(int), 1, FIndEspec);
	fwrite(IEspec, sizeof(Indice_Prim), n, FIndEspec);

	free(IEspec);
	fclose(FIndEspec);
}

void indice_insere(int id, int offset) {
	int i;

	N_IEspec++;
	IEspec = (Indice_Prim *)realloc(IEspec, (N_IEspec)*sizeof(Indice_Prim));
	i = N_IEspec-1;
	while (i>0 && (id < IEspec[i-1].id)) {
		IEspec[i] = IEspec[i-1];
		i--;
	}

	IEspec[i].id = id;
	IEspec[i].offset = offset;
}

void indice_deleta(int id) {
	int i;
	int pos = indice_busca(id);
	printf("%d\n", pos);
	if (pos == -1) {
		printf("Nao existe arquivo com esse indice!\n");
	} else {
		for (i=pos; i<N_IEspec; i++)
			IEspec[i] = IEspec[i+1];
		N_IEspec--;
		IEspec = (Indice_Prim *)realloc(IEspec, (N_IEspec)*sizeof(Indice_Prim));
		printf("Registro removido com sucesso!\n");
	}
}

int indice_busca(int id) {
	int ini = 0, fim = N_IEspec-1, meio;

	if (IEspec[ini].id > id || IEspec[fim].id < id)
		return -1;

	if (IEspec[ini].id == id)
		return ini;
	if (IEspec[fim].id == id)
		return fim;

	while (fim - ini >= 2) {
		meio = (ini + fim)/2;
		if (IEspec[meio].id > id)
			fim = meio;
		else if (IEspec[meio].id < id)
			ini = meio;
		else
			return meio;
	}

	return -1;
}

