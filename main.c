#include "definicoes.h"

char *SIndiv = "individuos.txt";
char *SEspec = "especies.txt";
char *SCaptu = "capturas.dat";
char *SListSec = "lista_inv_sec.dat";
char *SListPrim = "lista_inv_prim.dat";

FILE *FIndiv;
FILE *FEspec;
FILE *FCaptu;
FILE *FListSec;
FILE *FListPrim;

int main() {
  int menu, m2;

  FEspec = open_file(SEspec);
  FIndiv = open_file(SIndiv);
  FCaptu = open_file_bin(SCaptu, 0);

  m2 = 0;
  while(1) {
    if(m2 == 0)
      if(!( menu = print_menu(0) ))
	break;

    m2=print_menu(menu);
    if(m2 == 0) continue;

    if(menu == 1) {
      if(m2 == 1) especie_insere();
      if(m2 == 2) especie_le();
      if(m2 == 3) especie_atualiza();
      if(m2 == 4) especie_deleta();
    }
    
    if(menu == 2) {
      if(m2 == 1) individuo_insere();
      if(m2 == 2) individuo_le();
      if(m2 == 3) individuo_atualiza();
      if(m2 == 4) individuo_deleta();
    }
    if(menu == 3){      
      if(m2 == 1) captura_insere();
      if(m2 == 2) captura_le();      
      if(m2 == 3) captura_atualiza();       
      if(m2 == 4) captura_deleta();
    }
    if(menu == 4){
      if(m2 == 1) historico_monitoramento();
      if(m2 == 2) ultima_captura();
      if(m2 == 3) ultima_captura_peso();
      if(m2 == 4) caminho_especie();
    }
  }
  
  fclose(FCaptu);
  fclose(FEspec);
  fclose(FIndiv);
  system("clear");

  return 0;
}
