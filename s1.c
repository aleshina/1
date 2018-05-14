#include <ncurses.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>

#define MAXWIDTH 79
#define MAXHEIGHT 23

int colliding(int *snakeArray) {
  /* проверяет сталкивается ли змея со стенами */
  int x = *snakeArray;
  int y = *(snakeArray+1);
  if (x < 0 || x > MAXWIDTH) {
    return 1;
  }
  else if (y < 0 || y > MAXHEIGHT) {
    return 1;
  }
  return 0;
}

void moveSnake(int *snakeArray, int dirX, int dirY, int speed, int snakeLength) {
  /*перемещает змею на одно положение в указанное направление, также контролирует скорость
     игры с использованием функции usleep*/
  int oldX = 0;
  int oldY = 0;
  int curX = *snakeArray;
  int curY = *(snakeArray+1);
  int newX = curX + dirX;
  int newY = curY + dirY;

  *(snakeArray) = newX;
  *(snakeArray+1) = newY;
  mvprintw(newY, newX, "S");
for (size_t i = 2; i < snakeLength*2; i += 2)
 {
    oldX = curX;
    oldY = curY;
    curX = *(snakeArray+i);
    curY = *(snakeArray+i+1);
    newX = oldX;
    newY = oldY;
    *(snakeArray+i) = newX;
    *(snakeArray+i+1) = newY;
    mvprintw(newY, newX, "S");
  }

  if (dirY != 0) {
    usleep(1000000/speed);
  }

  usleep(1000000/speed);
}

void letThereBeApple(int* appleX, int* appleY, int *appleEaten) {
  /* новое случайное расположение яблока, если яблоко съедено, а если нет, то печатает яблоко в
     предыдущее местоположение */
  if (*appleEaten) {
    srand(time(0)); //использовать текущее время для случайного генератора
    *appleX = (rand() % MAXWIDTH)+1;
    *appleY = (rand() % MAXHEIGHT)+1;
    *appleEaten = 0;
  }

  mvprintw(*appleY, *appleX,"A");
}

void eatApple(int *snakeArray, int appleX, int appleY,
              int *appleEaten, int *snakeLength) {  
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


