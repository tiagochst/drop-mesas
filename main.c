#include "definicoes.h"

char *SIndiv = "individuos.txt";
char *SEspec = "especies.txt";
char *SCaptu = "capturas.dat";
char *SInvPrim = "inv_primario.dat";
char *SInvSec = "inv_secundario.dat";
char *SIndEspec = "ind_especie.dat";
char *SIndIndiv = "ind_individuo.dat";

FILE *FIndiv;
FILE *FEspec;
FILE *FCaptu;
FILE *FInvPrim;
FILE *FInvSec;
FILE *FIndEspec;
FILE *FIndIndiv;

int main() {
	int menu, m2;

	FEspec = open_file(SEspec);
	FIndiv = open_file(SIndiv);
	FCaptu = open_file_bin(SCaptu);

	lista_inv_start(SInvPrim, SInvSec);
	indice_start(SIndEspec);

	m2 = 0;
	while (1) {
		if ((m2 == 0) && (!(menu = print_menu(0) )))
			break;

		m2=print_menu(menu);
		if (m2 == 0)
			continue;

		if (menu == 1) {
			if (m2 == 1) especie_insere();
			if (m2 == 2) especie_le();
			if (m2 == 3) especie_atualiza();
			if (m2 == 4) especie_deleta();
		}

		if (menu == 2) {
			if (m2 == 1) individuo_insere();
			if (m2 == 2) individuo_le();
			if (m2 == 3) individuo_atualiza();
			if (m2 == 4) individuo_deleta();
		}
		if (menu == 3) {
			if (m2 == 1) captura_insere();
			if (m2 == 2) captura_le();
			if (m2 == 3) captura_atualiza();
			if (m2 == 4) captura_deleta();
		}
		if (menu == 4) {
			if (m2 == 1) historico_monitoramento();
			if (m2 == 2) ultima_captura();
			if (m2 == 3) ultima_captura_peso();
			if (m2 == 4) caminho_especie();
			if (m2 == 5) busca_especie_descricao();
		}
	}

	lista_inv_end(SInvPrim, SInvSec);
	indice_end(SIndEspec);
	fclose(FCaptu);
	fclose(FEspec);
	fclose(FIndiv);
	system("clear");

	return 0;
}
