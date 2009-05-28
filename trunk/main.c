#include "definicoes.h"

char *SIndiv = "individuos.txt";
char *SEspec = "especies.txt";
char *SCaptu = "capturas.dat";
char *SInvPrim = "inv_primario.dat";
char *SInvSec = "inv_secundario.dat";
char *SIPrimEspec = "ind_prim_especie.dat";
char *SIPrimIndiv = "ind_prim_individuo.dat";
char *SISecIndiv = "ind_sec_individuo.dat";
char *SISecCaptu = "ind_sec_captura.dat";

FILE *FIndiv;
FILE *FEspec;
FILE *FCaptu;
FILE *FInvPrim;
FILE *FInvSec;
FILE *FIPrimEspec;
FILE *FIPrimIndiv;
FILE *FISecIndiv;
FILE *FISecCaptu;

int main(int argc, char *argv[]) {
	int menu, i;
	FILE *file_input[3];

	if(argc <= 3) {
	  /*** instrucoes de uso ***/
	  return 1;
	}

	for(i=0 ; i<3 ; i++) {
	  file_input[i] = fopen(argv[i+1], "r");

	  if(file_input[i] == NULL) {
	    fprintf(stderr, "ERRO [main]: Nao foi possivel abrir um dos arquivos de input.");
	    return 1;
	  }
	}

	FEspec = open_file(SEspec);
	FIndiv = open_file(SIndiv);
	FCaptu = open_file_bin(SCaptu);

	indice_start(SIPrimEspec, SIPrimIndiv);
	indice_sec_start(SISecIndiv, SISecCaptu);
	lista_inv_start(SInvPrim, SInvSec);

	if( (menu = print_menu(0)) ) {
		if (menu == 1) {
			especie_insere(file_input[0]);
			individuo_insere(file_input[1]);
			captura_insere(file_input[2]);
		} else if (menu == 2) {
		}
	}

	lista_inv_end();
	indice_end(SIPrimEspec, SIPrimIndiv);
	indice_sec_end(SISecIndiv, SISecCaptu);

	fclose(FCaptu);
	fclose(FEspec);
	fclose(FIndiv);
	system("clear");

	return 0;
}
