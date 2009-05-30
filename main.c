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

int main(int argc, char **argv) {
  int menu, m2, i;
  FILE *file_input[3];

  FEspec = open_file(SEspec);
  FIndiv = open_file(SIndiv);
  FCaptu = open_file_bin(SCaptu);

  indice_start(SIPrimEspec, SIPrimIndiv);
  indice_sec_start(SISecIndiv, SISecCaptu);
  lista_inv_start(SInvPrim, SInvSec);

  if(argc == 1) {
    m2 = 0;
    while (1) {
      if ((m2 == 0) && (!(menu = print_menu(0))))
	break;

      m2 = print_menu(menu);
      if (m2 == 0) continue;

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
	if (m2 == 1) historico_monitoramento_lab2();
	if (m2 == 2) ultima_captura_lab2();
	if (m2 == 3) ultima_captura_peso_lab2();
	if (m2 == 4) caminho_especie_lab2();
	if (m2 == 5) busca_especie_descricao();
      }
    }
  }
  else if(argc == 4) {
    while ((m2 = print_menu_lab3())) {
            
      if(m2 == 1){
	if (m2 == 0) continue;
	for(i=0 ; i<3 ; i++) {
	  
	  file_input[i] = fopen(argv[i+1], "r");
	  
	  if(file_input[i] == NULL) {
	    fprintf(stderr, "ERRO [main]: Nao foi possivel abrir um dos arquivos de input.");
	    return 1;
	  }
	}
	especie_insere_lab3(file_input[0]);
	individuo_insere_lab3(file_input[1]);
	captura_insere_lab3(file_input[2]);
	 
	for(i=0 ; i<3 ; i++)
	  fclose(file_input[i]);

	printf("Leitura efetuada com sucesso!\n");
	Pause();
      }
      if(m2 == 2){
	
      }
    }
  }
  else return 1;
  
  lista_inv_end();
  indice_end(SIPrimEspec, SIPrimIndiv);
  indice_sec_end(SISecIndiv, SISecCaptu);

  fclose(FCaptu);
  fclose(FEspec);
  fclose(FIndiv);

  return 0;
}
