#include "definicoes.h"

int print_menu() {
        int in;

        puts("***********************************");
        puts("* Entre com sua opção:            *");
        puts("*                                 *");
        puts("* 1. gerar representação vetorial *");
        puts("* 2. gerar matriz de distâncias   *");
        puts("* 3. consultar                    *");
        puts("*                                 *");
        puts("* 0. sair do programa             *");
        puts("***********************************");

        while (scanf(" %d", &in) != 1 || in < 0 || in > 3) {
                puts("Entrada incorreta. Digite novamente");
                __fpurge(stdin);
        }
        return in;
}

void Pause() {
        char c;
        puts("Pressione (q) para continuar. . .");
        while (scanf("%c", &c) == 1 && tolower(c) != 'q');
}
