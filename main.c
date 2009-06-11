#include "definicoes.h"

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
		if (menu == 3);
	}
	files_end();

	return 0;
}
