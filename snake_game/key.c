/* key.c -------
 *
 * Filename: key.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 20:29:30 2020
 * Last-Updated: September 13 22:39 2020
 *           By: Rishabh Agrawal
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *  added support for pause and the save game options
 *
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */



#include <ncurses.h>
#include <stdlib.h>
#include "key.h"
#include "snake.h"

int get_char(){
  int ch = getch();
  switch(ch){
    case KEY_LEFT:
      return LEFT;
      break;
    case KEY_RIGHT:
      return RIGHT;
      break;
    case KEY_UP:
      return UP;
      break;
    case KEY_DOWN:
      return DOWN;
      break;
    case 10:
      return 10;
      break;
    case 'P':
      return P;
      break;
    case 'p':
      return P;
      break;
    case 'Q':
      return QUIT;
      break;
    case 'q':
      return QUIT;
      break;
    case '+':
      return PLUS;
      break;
    case '-':
      return SUBTRACT;
      break;
    case 'S':
      return START;
      break;
    case 's':
      return START;
      break;
    case 'f':
      return SAVE;
      break;
    case 'F':
      return SAVE;
      break;
    case 'E':
      return EASY;
      break;
    case 'e':
      return EASY;
      break;
    case 'H':
      return HARD;
      break;
    case 'h':
      return HARD;
      break;
    case 'A':
      return ADV;
      break;
    case 'a':
      return ADV;
      break;
    case 'L':
      return LOAD;
      break;
    case 'l':
      return LOAD;
      break;
    default:
      return(NOCHAR);
      break;
  }
}

