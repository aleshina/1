#include <ncurses.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

#define MAXWIDTH 79
#define MAXHEIGHT 23

  /*Если змея находит яблоко, получите одно очко, также установите appleEaten в true и
печатает данные snakeLength и отладки */
  int x = *snakeArray;
  int y = *(snakeArray+1);
  if (x == appleX && y == appleY) {
    *appleEaten = 1;
    *snakeLength += 1;
    int snakeLen = *snakeLength;
    int lastX = *(snakeArray + snakeLen*2-2);
    int lastY = *(snakeArray + snakeLen*2-2+1);
    *(snakeArray + snakeLen*2) = lastX;
    *(snakeArray + snakeLen*2+1) = lastY;
  }

  mvprintw(0,0,"snakeLength: %d", *snakeLength);
}

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
/* основной круг  */
  while (!colliding(&snakeArray[0][0])) {
    erase();

    letThereBeApple(&appleX, &appleY, &appleEaten);
    moveSnake(&snakeArray[0][0], dirX, dirY, speed, snakeLength);
    eatApple(&snakeArray[0][0], appleX, appleY, &appleEaten, &snakeLength);


    refresh();
/* изменить направление с помощью wasd */
    if (kbhit()) {
      keyPressed = getch();

      if (keyPressed == 'w') {
        dirY = -1;
        dirX = 0;
      }
      if (keyPressed == 's') {
        dirY = 1;
        dirX = 0;
      }
      if (keyPressed == 'a') {
        dirX = -1;
        dirY = 0;
      }
      if (keyPressed == 'd') {
        dirX = 1;
        dirY = 0;
      }
    }


