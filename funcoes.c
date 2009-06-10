#include "definicoes.h"
#include "menu.h"


int print_menu() {
        int in;

	CLEAR_SCREEN();

	PRINT_YELLOW("***********************************\n");
	PRINT_YELLOW("*     Entre com sua opção:        *\n");
	PRINT_YELLOW("***********************************\n");
       	PRINT_WALLS(" 1. gerar representação vetorial ");
	PRINT_WALLS(" 2. gerar matriz de distâncias   ");
	PRINT_WALLS(" 3. consultar                    ");
	PRINT_YELLOW("*                                 *\n");
	PRINT_WALLS_BLUE(" 0. sair do programa             ");
	PRINT_YELLOW("***********************************\n");
     

        while (scanf(" %d", &in) != 1 || in < 0 || in > 3) {
	  BLINK_RED("Entrada incorreta. Digite novamente");
	  __fpurge(stdin);
        }
        return in;
}

void Pause() {
        char c;
        puts("Pressione (q) para continuar. . .");
        while (scanf("%c", &c) == 1 && tolower(c) != 'q');
}
