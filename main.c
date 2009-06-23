#include "definicoes.h"
const char *print_double = "%.6lf ";

int NFile;
char** FileNames;
FILE** File;
Conjunto **FileWords;

int main() {
  int menu;

  files_start();
  while ((menu = print_menu())) {
    if (menu == 1) opcao1();
    if (menu == 2) opcao2();
    if (menu == 3) opcao3();
  }
  files_end();

  return 0;
}
