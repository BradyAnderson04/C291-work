/* snake.c -------
 *
 * Filename: snake.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 9:12:30 2020
 * Last-Updated: September 13 22:40 2020
 *           By: Rishabh Agrawal
 *
 */

/* Commentary:
 * 
 * This file is for code that a snake can do and can have happen to it
 * All logic for actions with the snake is defined modularly with the functions
 * 
 */

/* Change log:
 * Changes a lot with the loops to make it so that the seg faults weren't caused any more 
 * 
 * Also implemented a variable to impact the speed of movement for the snake in the move function
 * 
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */


#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "snake.h"
#include "food.h"
#include "key.h"
#include <ncurses.h>


// Initialize snake
Snake* init_snake(int x, int y){
  // create the head and subsequent 2 sections
  Snake* head = create_tail(x, y);
  Snake* tail1 = create_tail(x-1, y);
  Snake* tail2 = create_tail(x-2, y);
  tail1->next = tail2;
  head->next = tail1;
  return head;
}

// Creates one tail
Snake* create_tail(int x, int y){
  // allow space for object
  Snake* snake = malloc(sizeof(Snake));
  // define properties of new subsection
  snake->color[0] = 0;
  snake->color[1] = 0;
  snake->color[2] = 0;
  /* snake->color = {0, 0, 255}; */
  snake->symbol = '#';
  snake->next = NULL;
  snake->x = x;
  snake->y = y;
  snake->speed = 1;
  return snake;
}

void add_tail(Snake* snake, Snake* tail){
  // find the last node of the snake recursively -- similar to remove tail
  Snake* end = snake; // var to hold the end of a snake
  while(end->next) // iterate through to find the last element
      end = end->next;
  // add the tail
  end->next = malloc(sizeof(Snake));
  end->next = tail;
}

// Moves the snake in the input direction
Snake* move_snake(Snake* snake, int direction){
  Snake* new_head = malloc(sizeof(Snake));

  // Set the new head to have the x and y coordinates as the existing head of the snake
  new_head->x = snake->x;
  new_head->y = snake->y;
  
  switch(direction) { 
    case UP:
      // Write code to make the new head go up by 1 cell
      new_head->y -= 1;
      break;
    case DOWN:
      // Write code to make the new head go down by 1 cell
      new_head->y += 1;
      break;
    case RIGHT:
      // Write code to make the new head go right by 1 cell
      new_head->x += 1;
      break;
    case LEFT:
      // Write code to make the new head go left by 1 cell
      new_head->x -= 1;
      break;
  }
  
  // Set new head as the new head of the entire snake
  new_head->next = snake;
  // Add all the features (color and symbol) to the new cell
  new_head->speed = snake->speed;
  new_head->symbol = snake->symbol;
  new_head->color[0] = snake->color[0];
  new_head->color[1] = snake->color[1];
  new_head->color[2] = snake->color[2];
  // Delete the tail from the snake: HINT - there is a remove tail function below
  remove_tail(new_head);

  // return the new snake
  return new_head;
}

Snake* move_randomly(Snake* snake){
  int direction = (rand()%4) + 1;
  // int direction = 2;
  Snake* new_head = malloc(sizeof(Snake));

  // Set the new head to have the x and y coordinates as the existing head of the snake
  new_head->x = snake->x;
  new_head->y = snake->y;

  switch(direction) { 
    case UP:
      // Write code to make the new head go up by 1 cell
      new_head->y -= 1;
      break;
    case DOWN:
      // Write code to make the new head go down by 1 cell
      new_head->y += 1;
      break;
    case RIGHT:
      // Write code to make the new head go right by 1 cell
      new_head->x += 1;
      break;
    case LEFT:
      // Write code to make the new head go left by 1 cell
      new_head->x -= 1;
      break;
  }

  // Set new head as the new head of the entire snake
  new_head->next = malloc(sizeof(Snake)); // not sure if this line is necessary but maybe good practice?
  new_head->next = snake;
  // Add all the features (color and symbol) to the new cell
  new_head->speed = snake->speed;
  new_head->symbol = snake->symbol;
  new_head->color[0] = snake->color[0];
  new_head->color[1] = snake->color[1];
  new_head->color[2] = snake->color[2];
  // Delete the tail from the snake: HINT - there is a remove tail function below
  remove_tail(new_head);

  // return the new snake
  return new_head;
}

void movement_boundary(Snake *s, int upper_x, int upper_y, int x_space, int y_space, int width, int height){
      if(s->x <= upper_x + (int)x_space){
        s = move_snake(s, RIGHT);
      }
      else if(s->x >= upper_x + width - (int)x_space){
        s = move_snake(s, LEFT);
      }
      else if(s->y <= upper_y + (int) y_space){
        s = move_snake(s, DOWN);
      }
      else if(s->y >= upper_y + height - (int)y_space){
        s = move_snake(s, UP);
      }
  }

Snake* remove_tail(Snake* snake){
    Snake* end = snake; // var to hold the desired value
    while(end->next->next) // iterate while there is a child node of the child node
        end = end->next;
    free(end->next); // free memory space bc we used malloc to create
    end->next = NULL; // reset to null
    return snake; // return the updated snake
}

// draws the snake on the board
void draw_snake(Snake* snake){
  // iterate over snake and print the symbol at the location of the snake part
  while(snake){
    mvprintw(snake->y, snake->x, "%c", snake->symbol);
    snake = snake->next;
  }
}

// checks if it eats itself, if it does, then return true
bool eat_itself(Snake* snake, int x, int y){
  // TODO for Milestone 2 only
  snake = snake->next;
  while(snake){
    if(y == snake->y && x == snake->x){
      return true;
    }
    snake = snake->next;
  }
  return false;
}

char* snake_information(Snake* snake){
  char* output = malloc(30 * sizeof(char)); // init an array to fit 10 strings
  Snake* temp = snake;

  // get snake information and add to the output
  char * tempstr = malloc(13 * sizeof(char));
  sprintf(tempstr, "%d,%d,%d,%c,%d,%d,%d\n", temp->x, temp->y, temp->speed, temp->symbol, temp->color[0], temp->color[1], temp->color[2]);
  strcat(output, tempstr);
  
  return output;
}

int snake_size(Snake* snake){
  Snake* temp = snake;
  int count = 1;
  while(temp->next){
    count++;
    temp = temp->next;
  }
  return count;
}

void reverse_snake(Snake* snake){
  Snake *prev = NULL;
  Snake *curr = snake;
  Snake *next = NULL;

  while(curr != NULL){
    // reset the next value to be the next item in Linked list
    next = curr->next;
    // assign the value to be process to the last value
    curr->next=prev;
    // swap nodes to reverse order
    prev = curr;
    curr = next;
  }

  snake = prev;
}

int snake_collision(Snake *player, Snake *enemy){
  Snake* end = player; // var to hold the end of a snake
  while(end->next){ // check every part of the snake for a collision with the enemy
      int x = end->x, y = end->y;
      Snake *temp = enemy;
      while(temp->next){
          // check for collisions here
          if(x == temp->x && y == temp->y){
            return 1;
          }
          temp = temp->next;
      }
      end = end->next;
  }
  return 0;
}
