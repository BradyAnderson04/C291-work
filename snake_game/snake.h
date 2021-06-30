/* snake.h -------
 *
 * Filename: snake.h
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 21:01:02 2020
 * Last-Updated: September 13 22:43 2020
 *           By: Rishabh Agrawal
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include <stdbool.h>

struct Snake {
  int x;
  int y;
  int speed;
  char color[3];
  char symbol;
  struct Snake* next;
};

typedef struct Snake Snake;

Snake* init_snake(int x, int y);
Snake* create_tail(int x, int y);
Snake* move_snake(Snake* snake, int direction);
void draw_snake(Snake* snake);
bool eat_itself(Snake* snake, int x, int y);
Snake* remove_tail(Snake* snake);
void add_tail(Snake* snake, Snake* tail);
int len(Snake* snake);
char* snake_information(Snake* snake);
int snake_size(Snake* snake);
void reverse_snake(Snake* snake);
Snake* move_randomly(Snake* snake);
void movement_boundary(Snake* s, int upper_x, int upper_y, int x_space, int y_space, int width, int height);
int snake_collision(Snake *player, Snake *enemy);
