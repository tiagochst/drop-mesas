#include <stdio.h>

/*definicao de cores para menu*/
#define NO_COLOR 0
#define BRIGHT 1
#define BLINK_ON 5
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define BG_BLACK 40

void clear_screen();
void menu_no_color();
void menu_wall_start();
void menu_wall_end();
void print_yellow(char texto[]);
void print_blue(char texto[]);
void blink_red(char texto[]);
void print_walls(char texto[]);
void print_walls_blue(char texto[]);
