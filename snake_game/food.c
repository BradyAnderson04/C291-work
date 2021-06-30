/*food.c -------
*
* Filename: food.c
* Description:
* Author: Manisha Suresh Kumar
* Maintainer:
* Created: Sat Sep 12 13:16:12 2020
* Last-Updated: September 12 16:51 2020
*	  By: Manisha Suresh Kumar
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

/*Copyright (c) 2016 The Trustees of Indiana University and
* Indiana University Research and Technology Corporation.
*
* All rights reserved.
*
* Additional copyrights may follow
*/

#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "food.h"


//Create new food
Food* create_food(int x, int y, enum Type type){
    Food* new_food = malloc(sizeof(Food));
    // define the x/y vals
    new_food->x = x;
    new_food->y = y;
    // given a type assign a type and symbol to struct
    if (type == Increase){
        new_food->type = Increase;
        new_food->symbol = (rand() > RAND_MAX/2) ? '+' : 'O';
    }
    else if(type == Decrease){
        new_food->type = Decrease;
        new_food->symbol = (rand() > RAND_MAX/2) ? '-' : 'X';
    }
    // make the next item in linkedlist null
    new_food->next = NULL;
    // return new object
    return new_food;
}

//Check if food exists at coordinates
bool food_exists(Food* foods, int x, int y){
    Food* temp = foods;
    while(temp){
        // we found the fruit looking for
        if(temp->x == x && temp->y == y)
            return true;
        // go onto the next one
        temp = temp->next;
    }
    return false;
}

//Add new food to end of food list
void add_new_food(Food* foods, Food* new_food){
    // get to the last food in linkedlist
    Food* temp = foods;
    while(temp->next) {
        temp = temp->next;
    }
    // add new food at the end
    temp->next = malloc(sizeof(Food));
    temp->next = new_food;
}

// id the fruit type
enum Type food_type(Food* foods, int x, int y){
    //Implement the code to return the type of the food 
    //present at position (x, y)
    Food* temp = foods;
    while(temp->next) {
        // when fruit is at the position specified return the type
        if(temp->x == x && temp->y == y){
            return temp->type;
        }
        // go onto the next fruit bc the one we want not found
        temp = temp->next;
    }
    return 0;
}

// remove the fruit collided with
Food* remove_eaten_food(Food* foods, int x, int y){
	//Implement the code to remove food at position (x,y).
	//Create a new linked list of type Food containing only the
    Food* temp = foods;
    while(temp->next) {
        //needed food and return this new list
        if(food_exists(foods, x, y)){
            // code to id the fruit being eaten - this fruit is the fruit
            if(temp->next->x == x && temp->next->y == y){
                // remove from linked list
                if(temp->next->next != NULL){
                    temp->next = temp->next->next;
                }
                else
                {
                    temp->next = NULL;
                }
                // replace the food
                break; // terminate loop fruit has been found
            }
        }
        temp = temp->next;
    }
    return temp->next;
}

// Display all the food
void draw_food (Food *foods)
{   
    // create a temp to process each individual food
    Food* temp = foods;
    // iterate through food recursively
    while(temp) {
        // print and move on to the next one
        mvprintw(temp->y, temp->x, "%c", temp->symbol);
        temp = temp->next;
    }
}

char* food_information(Food* foods){
    char* output = malloc(150 * sizeof(char)); // init an array to fit 10 strings
    Food* temp = foods;
    while(temp->next) {
        char * tempstr = malloc(13 * sizeof(char));
        sprintf(tempstr, "%d,%d,%d,%c\n", temp->x, temp->y, temp->type, temp->symbol);
        strcat(output, tempstr);
        temp = temp->next;
    }
    return output;
}