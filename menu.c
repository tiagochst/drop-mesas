#include "menu.h"

void clear_screen(){
  printf("\e[H\e[2J"); /* printf() para limpar a tela */
}

void menu_no_color(){
  printf("%c[%dm", 0x1B, NO_COLOR);
}
void print_yellow(char texto[]){
  printf("%c[%d;%dm", 0x1B, BRIGHT,YELLOW);	
  printf("%s",texto);
  menu_no_color();
}

void print_blue(char texto[]){
  printf("%c[%dm", 0x1B,BLUE);	
  printf("%s",texto);
  menu_no_color();
}

void menu_wall_start(){
  print_yellow("*");
 
}
void menu_wall_end(){
  print_yellow("*\n");
 }

void blink_red(char texto[]){
  printf("%c[%d;%d;%dm", 0x1B,RED,BRIGHT,BLINK_ON);
  printf("%s\n",texto);
  menu_no_color();
  
}

void print_walls(char texto[]){
	menu_wall_start();
	printf("%s",texto);
      	menu_wall_end();
}

void print_walls_blue(char texto[]){
	menu_wall_start();
	print_blue(texto);
      	menu_wall_end();
}
