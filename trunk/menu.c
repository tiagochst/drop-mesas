#include "menu.h"

void CLEAR_SCREEN(){
  printf("\e[H\e[2J"); /* printf() para limpar a tela */
}

void MENU_NO_COLOR(){
  printf("%c[%dm", 0x1B, NO_COLOR);
}
void PRINT_YELLOW(char texto[]){
  printf("%c[%d;%dm", 0x1B, BRIGHT,YELLOW);	
  printf("%s",texto);
  MENU_NO_COLOR();
}

void PRINT_BLUE(char texto[]){
  printf("%c[%dm", 0x1B,BLUE);	
  printf("%s",texto);
  MENU_NO_COLOR();
}

void MENU_WALL_START(){
  PRINT_YELLOW("*");
 
}
void MENU_WALL_END(){
  PRINT_YELLOW("*\n");
 }

void BLINK_RED(char texto[]){
  printf("%c[%d;%d;%dm", 0x1B,RED,BRIGHT,BLINK_ON);
  printf("%s\n",texto);
  MENU_NO_COLOR();
  
}

void PRINT_WALLS(char texto[]){
	MENU_WALL_START();
	printf("%s",texto);
      	MENU_WALL_END();
}

void PRINT_WALLS_BLUE(char texto[]){
	MENU_WALL_START();
	PRINT_BLUE(texto);
      	MENU_WALL_END();
}
