#include "menu.h"

void CLEAR_SCREEN(){
  system("clear");
}

void PRINT_YELLOW(){
  printf("%c[%d;%dm", 0x1B, BRIGHT,YELLOW);	
}

void PRINT_BLUE(){
  printf("%c[%d;%dm", 0x1B, BRIGHT,BLUE);	
}

void MENU_NO_COLOR(){
  printf("%c[%dm", 0x1B, NO_COLOR);
}
void MENU_WALL_START(){
  PRINT_YELLOW();
  printf("*");
  PRINT_BLUE();
}
void MENU_WALL_END(){
  PRINT_YELLOW();
  printf("*\n");
  PRINT_BLUE();
}
