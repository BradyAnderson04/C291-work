#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "obstacles.h"

Obstacle* init_obstacle(int upper_left_x, int upper_left_y, int width, int height){
	Obstacle *g;
	g = malloc(sizeof(Obstacle));
	g->upper_left_x = upper_left_x;
	g->upper_left_y = upper_left_y;
	g->width = width;
	g->height = height;
	g->draw_char = '*';
	g->next = NULL;
	return (g);
}

Obstacle* create_obs(int x, int y, int offset){
    Obstacle* new_obs = malloc(sizeof(Obstacle));
    new_obs->draw_char = '*';
    new_obs->height = offset;
    new_obs->width = offset;
    new_obs->upper_left_x = x;
    new_obs->upper_left_y = y;
    new_obs->next = NULL;
    return new_obs;
}

void draw_obstacle(Obstacle *obs){
    Obstacle* r = obs;
    while(r->next) {

        int row_counter, column_counter,of;

        // Draw Top of room
        for (row_counter = r->upper_left_x;
            row_counter <= (r->upper_left_x + r->width);
            row_counter++) {
            mvprintw(r->upper_left_y, row_counter, "%c", r->draw_char);
        }

        // Draw left side of room
        for (column_counter = r->upper_left_y;
            column_counter <= (r->upper_left_y + r->height);
            column_counter++) {
                //mvprintw(column_counter, r->upper_left_x, "%c", r->draw_char);
                for(of = 0; of < r->width; of++){ 
                    mvprintw(column_counter, r->upper_left_x + of, "%c", r->draw_char);
                }
        }

        // Draw right side of room
        for (column_counter = r->upper_left_y;
            column_counter <= (r->upper_left_y + r->height);
            column_counter++) {
            mvprintw(column_counter, (r->upper_left_x + r->width), "%c", r->draw_char);
        }

        // Draw Bottom of room
        for (row_counter = r->upper_left_x;
            row_counter <= (r->upper_left_x + r->width);
            row_counter++) {
            mvprintw(r->upper_left_y + r->height, row_counter, "%c", r->draw_char);
        }
        r = r->next;
    }
}

void add_new_obs(Obstacle* obs, Obstacle* new_obs){
    // add an obstacle to the end of a linked list 
    Obstacle* temp = obs;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = malloc(sizeof(Obstacle));
    temp->next = new_obs;
}

bool all_bound(Obstacle* obs, int x, int y){
    Obstacle* temp = obs;
    while(temp->next) {
        //needed food and return this new list
        if(obs_bound_exists(temp, x, y)){
            // code to id the fruit being eaten - this fruit is the fruit
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool obs_bound_exists(Obstacle *obs,int x,int y){
	int row_counter, column_counter,of;
    Obstacle* r = obs;
	// Draw Top of room
	for (row_counter = r->upper_left_x;
		 row_counter <= (r->upper_left_x + r->width);
		 row_counter++) {
        if(r->upper_left_y == y && (row_counter + of) == x){
            return true;
        }
	}

	// Draw left side of room
	for (column_counter = r->upper_left_y;
		 column_counter <= (r->upper_left_y + r->height);
		 column_counter++) {
        for(of = 0; of < r->width; of++){ //this for loop checks the inside of the obstacle square
            if(column_counter == y && (r->upper_left_x + of) == x){
                return true;
            }
        }
	}

	// Draw right side of room
	for (column_counter = r->upper_left_y;
		 column_counter <= (r->upper_left_y + r->height);
		 column_counter++) {
		if(column_counter == y && (r->upper_left_x + r->width) == x){
			return true;
		}
	}

	// Draw Bottom of room
	for (row_counter = r->upper_left_x;
		 row_counter <= (r->upper_left_x + r->width);
		 row_counter++) {
		if((r->upper_left_y + r->height) == y && row_counter == x){
			return true;
		}
	}
	return false;
}

char* obstacle_information(Obstacle* obs){
    char* output = malloc(200 * sizeof(char)); // init an array to fit 10 strings
    Obstacle* temp = obs;
    while(temp->next) {
        char * tempstr = malloc(13 * sizeof(char));
        sprintf(tempstr, "%d,%d,%d,%d,%c\n", temp->upper_left_x, temp->upper_left_y, temp->width, temp->height, temp->draw_char);
        strcat(output, tempstr);
        temp = temp->next;
    }
    return output;
}
