#include "definicoes.h"
#include "menu.h"


int print_menu() {
        int in;

	CLEAR_SCREEN();
	PRINT_YELLOW();
        puts("***********************************");
	puts("*     Entre com sua opção:        *");
        puts("***********************************");
	MENU_NO_COLOR();
	MENU_WALL_START();
       	printf(" 1. gerar representação vetorial ");
	MENU_WALL_END();
      	MENU_WALL_START();
	printf(" 2. gerar matriz de distâncias   ");
	MENU_WALL_END();
      	MENU_WALL_START();
	printf(" 3. consultar                    ");
	MENU_WALL_END();
	PRINT_YELLOW();
	puts("*                                 *");
      	MENU_WALL_START();
	PRINT_BLUE();
        printf(" 0. sair do programa             ");
	MENU_WALL_END();
	PRINT_YELLOW();
        printf("***********************************\n");
	MENU_NO_COLOR();

        while (scanf(" %d", &in) != 1 || in < 0 || in > 3) {
	  printf("%c[%d;%d;%dm", 0x1B,RED,BRIGHT,BLINK_ON);
	  puts("Entrada incorreta. Digite novamente");
	  printf("%c[%dm", 0x1B, NO_COLOR);
                __fpurge(stdin);
        }
        return in;
}

void Pause() {
        char c;
        puts("Pressione (q) para continuar. . .");
        while (scanf("%c", &c) == 1 && tolower(c) != 'q');
}
