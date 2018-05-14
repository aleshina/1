#include <ncurses.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

#define MAXWIDTH 79
#define MAXHEIGHT 23

int main() {

  int snakeArray[100][2];
  snakeArray[0][0] = 3;
  snakeArray[0][1] = 3;
  int keyPressed = 0;   /* который нажал ключевой пользователь */
  int dirX = 1;        /* направление xy */
  int dirY = 0;
  int speed = 20;       /* контролирует скорость змеи*/
  int appleX = 0;       /* текущая позиция Apple xy */
  int appleY = 0;
  int appleEaten = 1;   /* яблоко съедено? */
  int snakeLength = 3;  /* игрок длина змейки */

  initscr();			/* начало режима ncurses */
  curs_set(false);
  noecho();
