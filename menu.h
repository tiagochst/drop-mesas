#include<stdio.h>

/*definicao de cores para menu*/
#define NO_COLOR 0
#define BRIGHT 1
#define BLINK_ON 5
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define BG_BLACK 40

void CLEAR_SCREEN();
void MENU_NO_COLOR();
void MENU_WALL_START();
void MENU_WALL_END();
void PRINT_YELLOW(char texto[]);
void PRINT_BLUE(char texto[]);
void BLINK_RED(char texto[]);
void PRINT_WALLS(char texto[]);
void PRINT_WALLS_BLUE(char texto[]);