#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "snake.h"
#include "food.h"
#include "game_window.h"
#include "key.h"
#include "game.h"

#define SNAKE       1
#define ESNAKECOLOR 2
#define FOOD        3
#define OBSTACLES   4
#define MONE 5
#define MTWO 6
#define MTHREE 7
#define MFOUR 8
#define MFIVE 9
#define MTEN 10

#define positive 20
#define negative 10

// helper methods
void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset){
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}

int cmpfunc(const void *a, const void *b){
   return (*(int*)b - *(int*)a);
}

void food_collision(Food *foods, Snake* snake){
    // x/y vars
    int x = snake->x;
    int y = snake->y;

    int size = snake_size(snake);
    
    if(food_exists(foods, x, y)){
      // need type for shrink/grow
      int type = food_type(foods, x, y);
      // grow/shrink
      if(type == Increase){
          Snake* end = snake; // this is the last part of snake
          while(end->next)
              end = end->next;
          
          // increase based off direction
          Snake* tail = create_tail(end->x, end->y); // creates tail w/ proper points
          end->next = tail; // adds tail to the snake
      } 
      else if(type == Decrease){
          if(snake_size(snake) != 1){
              // remove the tail
              snake = remove_tail(snake);
          }
      }
    }
  }

void readSavedGame(FILE *savePtr, char* filename, Snake **snake, Food **foods, Obstacle **obs, gamewindow_t **window, int *score, int *direction){
    char *temp = malloc(25*sizeof(char));
    int mul = 0, i = 0;
    char objectData[9][3];
    savePtr = fopen(filename, "r");
    // booleans to choose what objects to create
    int fruitBool=0, obstacleBool=0;
    while(fgets(temp, 25, savePtr) != NULL){
        // process file here to create game objects -- process all data here
        
        // switch objects created in the if statements
        if(strncmp(temp, "Fruits:", 7) == 0){
            fruitBool = 1;
            // create first instance
            fgets(temp, 25, savePtr);
            vSeparateSringByComma(temp, objectData, 9, 3);
            *foods = create_food(strtol(objectData[0], NULL, 10), strtol(objectData[1], NULL, 10), (strtol(objectData[2], NULL, 10) % 2 == 0) ? Increase : Decrease);
        } 
        if(strncmp(temp, "Snake:", 6) == 0){
            // create snake of size next line
            Snake *s = malloc(sizeof(Snake));

            fgets(temp, 25, savePtr); // snake data
            vSeparateSringByComma(temp, objectData, 9, 3);
            s->x = strtol(objectData[0], NULL, 10);
            s->y = strtol(objectData[1], NULL, 10);;
            s->speed = strtol(objectData[2], NULL, 10);;
            s->symbol = objectData[3][0];
            s->color[0] = strtol(objectData[4], NULL, 10);;
            s->color[1] = strtol(objectData[5], NULL, 10);;
            s->color[2] = strtol(objectData[6], NULL, 10);;
            s->next = NULL;

            *snake = s;

            fgets(temp, 25, savePtr); // size data
            char *val = malloc(5 * sizeof(char));
            int size;
            strncpy(val, &temp[6], 2);
            size = strtol(val, NULL, 10);

            for(i=0; i<size-1; i++){
                // create and add the correct number of tails to the snake ref
                Snake* tail = create_tail((*snake)->x-(i+1), (*snake)->y);
                add_tail(*snake, tail);
            }

            free(s);
            free(val);
        }
        else if(strncmp(temp, "direction:", 10) == 0){
            // set initial direction of the loop
            char val;
            strncpy(&val, &temp[11], 1);
            *direction = strtol(&val, NULL, 10);
        }
        else if(strncmp(temp, "Obstacles:", 10) == 0){
            fruitBool = 0;
            obstacleBool = 1;
            // create first instance
            fgets(temp, 25, savePtr);
            vSeparateSringByComma(temp, objectData, 9, 3);
            *obs = create_obs(strtol(objectData[0], NULL, 10), strtol(objectData[1], NULL, 10), strtol(objectData[2], NULL, 10));
        }
        else if(strncmp(temp, "score:", 6) == 0){
            // set the initial score of the game loop
            obstacleBool = 0;
            char* val = malloc(5 * sizeof(char));
            strncpy(val, &temp[6], 5);
            *score = strtol(val, NULL, 10);
            free(val);
        }
        else if(strncmp(temp, "Gamewindow:", 11) == 0){
            // create snake of size next line
            gamewindow_t *w = malloc(sizeof(gamewindow_t));

            fgets(temp, 25, savePtr); // snake data
            vSeparateSringByComma(temp, objectData, 9, 3);
            w->upper_left_x = strtol(objectData[0], NULL, 10);
            w->upper_left_y = strtol(objectData[1], NULL, 10);
            w->width = strtol(objectData[2], NULL, 10);
            w->height = strtol(objectData[3], NULL, 10);
            w->draw_char = objectData[4][0];
            w->color[0] = strtol(objectData[5], NULL, 10);
            w->color[1] = strtol(objectData[6], NULL, 10);
            w->color[2] = strtol(objectData[6], NULL, 10);

            *window = w;
            free(w);
        }
        else {
            if(fruitBool){
                fgets(temp, 25, savePtr);
                vSeparateSringByComma(temp, objectData, 9, 3);
                Food* new_food = create_food(strtol(objectData[0], NULL, 10), strtol(objectData[1], NULL, 10), strtol(objectData[2], NULL, 10));
                add_new_food(*foods, new_food);
            }
            else if(obstacleBool){
                fgets(temp, 25, savePtr);
                vSeparateSringByComma(temp, objectData, 9, 3);
                Obstacle* new_obs = create_obs(strtol(objectData[0], NULL, 10), strtol(objectData[1], NULL, 10), strtol(objectData[2], NULL, 10));
                add_new_obs(*obs, new_obs);
            }
        }
        mul++;
    }
    fclose(savePtr);
    free(temp);
}

// main game loop
void game(){
    srand(time(0));
    // time and space settings
    static int x_max, y_max; // Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999/4;

    // game objects
    gamewindow_t *window;
    Snake *snake, *one, *two;
    Food *foods, *new_food; 
    FILE* savePtr;
    FILE* bestFive;
    Obstacle *obs, *new_obs;

    // user input and game logic parameters vars
    int ch;
    int direction = 1;
    double speed = 1;

    int score = 0;
    int size_changes = 0;
    const int height = 30; 
    const int width = 70;
    int menu_pointer[2] = {20,19};
    int load_pointer[2] = {12,19};
    int snake_length = 3;
    int lives = 3;
    enum State state = CREATE;
    char* filename = malloc(25 * sizeof(char));

    // Difficulty settings
    int o_max = 3;
    int f_max = 7; 
    double speed_change = .005;

    while(state != EXIT){
        switch(state){
        case CREATE:
            initscr();

            if (has_colors() == FALSE) {
                endwin();
                printf("Your terminal does not support color\n");
                exit(1);
            }
            start_color();
            // INIT COLORS being used
            init_pair(SNAKE, COLOR_GREEN, COLOR_GREEN);
            init_pair(ESNAKECOLOR, COLOR_BLUE, COLOR_BLUE);
            init_pair(OBSTACLES, COLOR_WHITE, COLOR_WHITE);
            init_pair(FOOD, COLOR_BLACK, COLOR_MAGENTA);
            init_pair(MONE, COLOR_RED, COLOR_BLACK);
            init_pair(MTWO, COLOR_BLUE, COLOR_BLACK);
            init_pair(MTHREE, COLOR_CYAN, COLOR_BLACK);
            init_pair(MFOUR, COLOR_GREEN, COLOR_BLACK);
            init_pair(MFIVE, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(MTEN, COLOR_YELLOW, COLOR_BLACK);

            nodelay(stdscr, TRUE); //Dont wait for char
            noecho(); // Don't echo input chars
            getmaxyx(stdscr, y_max, x_max);
            keypad(stdscr, TRUE); // making keys work
            curs_set(0); // hide cursor
            timeout(100);

            // Setting height and width of the board
            x_offset = (x_max / 2) - (width / 2);
            y_offset = (y_max / 2) - (height / 2);

            state = WELCOME;

            break;
        case INIT:
            clear();

            int food_x, food_y, i;
            enum Type type;

            //Init game objects
            window = init_GameWindow(x_offset, y_offset, width, height);
            draw_Gamewindow(window);
            snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));

            // create enemy snakes
            one = init_snake(x_offset + (width / 2) + 5, y_offset + (height / 2));
            two = init_snake(x_offset + (width / 2), y_offset + (height / 2) - 5);

            //Generate foods
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            type = (rand() > RAND_MAX/2) ? Increase : Decrease; // Randomly deciding type of food
            foods = create_food(food_x, food_y, type);
            for(i = 1; i < f_max; i++){
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
            }

            // generate 3-10 random obstacles
            int o = rand()%5 + 1;

            while(food_exists(foods,food_x, food_y))
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            obs = init_obstacle(food_x, food_y, o, o);

            for(i = 1; i < o_max; i++){
                o = rand()%5 + 1;
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while(food_exists(foods,food_x, food_y || all_bound(obs, food_x, food_y))) 
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                new_obs = create_obs(food_x, food_y, o);
                add_new_obs(obs, new_obs);
            }

            state = ALIVE;
            break;
        case WELCOME:
            // display instruction and game info here
            ch = get_char();

            if(ch == EASY){
                clear();
                state = INIT;
            }
            else if(ch == HARD){
                o_max = 6;
                f_max = 14;
                clear();
                state = INIT;
            }
            else if(ch == ADV) {
                o_max = 6;
                f_max = 14;
                speed_change *= 2;
                clear();
                state = INIT;
            }

            // Display Menu
            attron(COLOR_PAIR(MONE));
            mvprintw(10,20,"Welcome to SNAKE, Recreated by Brady Anderson :)\n");
            mvprintw(14,20,"To start the game please choose a difficulty below:\n");
            attroff(COLOR_PAIR(MONE));
            attron(COLOR_PAIR(MTWO));
            mvprintw(15,20,"E/e - easy\tH/h - hard\tA/a - Advanced\n");
            attron(COLOR_PAIR(MTWO));
            attron(COLOR_PAIR(MTHREE));
            mvprintw(17,20,"Press L/l to Load a previous saved game.\n");
            attroff(COLOR_PAIR(MTHREE));
            attron(COLOR_PAIR(MFOUR));
            mvprintw(18,20,"______________________________\n");
            mvprintw(20,20,"Please consider reading the following instructions:\n");
            attroff(COLOR_PAIR(MFOUR));
            attron(COLOR_PAIR(MFIVE));
            mvprintw(22,20,"\tP/p to Pause, pressing P/p while paused will unpause the game\n");
            mvprintw(24,20,"\t(f) to save the current state of the game");
            mvprintw(26,20,"\tQ/q to quit\n");
            attroff(COLOR_PAIR(MFIVE));
            attron(COLOR_PAIR(MTEN));
            mvprintw(28,20, "\t+ to increase size\n");
            mvprintw(30,20, "\t- to decrease size\n");
            attroff(COLOR_PAIR(MTEN));
            attron(COLOR_PAIR(MONE));
            mvprintw(32,20,"\tThe game will gradually speed up. Additionally, Your score will go up\n");
            mvprintw(34,20, "\twith every increasing fruit and down 10 with every decreasing fruit.\n");
            attroff(COLOR_PAIR(MONE));
            
            // sub menu items
            if(ch == LOAD){
                clear();
                state = LOADGAME;
            }

            break;
        case LOADGAME:
            ch = get_char();
            // menu sub actions -- save loads etc
            int saveCount = getSaveCount(savePtr), z;
            mvprintw(10,20,"Press Q to quit or enter to select the save the icon is on then press ENTER\n");
            for(z = 0; z < saveCount; z++ ){
                mvprintw(12+(2*z),20,"Play Save %d\n", z+1);
            }
            mvprintw(load_pointer[0], load_pointer[1], "*");
            
            // movement control
            if(ch == QUIT){
                clear();
                state = WELCOME;
            }

            // navigate menu
            if(ch == DOWN){
                if(load_pointer[0] != 10 + (2* (saveCount))){
                    load_pointer[0] += 2;
                    clear();
                }
            }
            if(ch == UP){
                if(load_pointer[0] != 12){
                    load_pointer[0] -= 2;
                    clear();
                }
            }

            // selecting choice
            if(ch == 10){
                // get selected choice
                int choice = (load_pointer[0] - 10) / 2;
                sprintf(filename,"./saves/save_%d.game",choice);
                clear();
                state = LOADINIT;
            }
            
            break;
        case LOADINIT:
            readSavedGame(savePtr, filename, &snake, &foods, &obs, &window, &score, &direction);
            state = ALIVE;
            break;
        case ALIVE:
            // mvprintw(10,20,"%d %d %d %d %d %d\n", snake->x, foods->x, obs->upper_left_x, window->width, score, direction);
            ch = get_char();
            int j;

            // increase speed of snake over time upping the actual speed when the next threshold is reached
            speed += speed_change;
            snake->speed = (int) speed;

            // change the direction
            if(ch == LEFT && direction != RIGHT){
                direction = LEFT;
            } 
            else if(ch == RIGHT && direction != LEFT){
                direction = RIGHT;
            } 
            else if(ch == UP && direction != DOWN){
                // want up not down
                direction = UP;
            } 
            else if(ch == DOWN && direction != UP){
                // want down not up
                direction = DOWN;
            } 
            else if(ch == P){
                // pause game
                clear();
                state = PAUSE;
                break;
            } 
            else if(ch == QUIT){
                // quit
                clear();
                state = EXIT;
                break;
            } 
            else if(ch == PLUS){
                if(size_changes != 3){
                    // increase size
                    window->height += 5;
                    window->width += 5;
                    size_changes += 1;
                }
            } 
            else if(ch == SUBTRACT){
                if(size_changes != -3){
                    // decrease size
                    window->height -= 5;
                    window->width -= 5;
                    size_changes -= 1;
                }
            }

            // enemy snake logic
            one = move_randomly(one);
            two = move_randomly(two);

            // going to move up / down / left / right if too close to edge
            int x_space = .05*(window->upper_left_x+width), y_space = .05*(window->upper_left_y+height);

            // TODO: Fix the 5% code -- adjust it for only upper and lower bounds
            // movement_boundary(one, window->upper_left_x, window->upper_left_y, x_space, y_space, width, height);
            // movement_boundary(two, window->upper_left_x, window->upper_left_y, x_space, y_space, width, height);

            // food collision
            food_collision(foods, one);
            food_collision(foods, two);

            // movement collisions and obstacles
            for(j = 0; j < snake->speed; j++){
                snake = move_snake(snake, direction); // actually does the movement

                // slide condition -- wall
                // reverse condition -- obstacles
                // death condition -- itself, length less than 1
                if(window->upper_left_x == snake->x || window->upper_left_x + width == snake->x){
                    // slide -- change state -- hit left / right barrier -- go on the other side
                    if(direction == 1){
                        // going left
                        snake->x = window->upper_left_x+width;
                    }
                    else {
                        // going right
                        snake->x = window->upper_left_x;
                    }
                }
                if(window->upper_left_y == snake->y || window->upper_left_y + height == snake->y){
                    // slide -- change state -- hit top / bottom barrier -- go on the other side
                    if(direction == 3){
                        // going up
                        snake->y = window->upper_left_y+height;
                    }
                    else {
                        // going down
                        snake->y = window->upper_left_y;
                    }
                }
                // death by size is in the decrease food collision code 
                if(eat_itself(snake, snake->x, snake->y) && snake_length > 3){
                    // decrease size of snake
                    remove_tail(snake);
                    snake_length-=1;
                }

                // reverse the snake when it hits the obstacles
                if(all_bound(obs, snake->x, snake->y)){
                    // reverse the direction of the snake
                    if(direction == 1){
                        // go right when starting left
                        direction = 2;
                    } 
                    else if(direction == 2){
                        // go left not right
                        direction = 1;
                    } 
                    else if(direction == 3){
                        // go down not up
                        direction = 4;
                    } 
                    else {
                        // go up not down
                        direction = 3;
                    }
                }

                // food collisions -- eating food
                int x = snake->x;
                int y = snake->y;
                
                if(food_exists(foods, x, y)){
                // need type for shrink/grow
                int type = food_type(foods, x, y);
                // grow/shrink
                if(type == Increase){
                    snake_length += 1;
                    score += 20; // add 20 to score 
                    Snake* end = snake; // this is the last part of snake
                    while(end->next)
                        end = end->next;
                    
                    // set the values of the end of the snake position
                    int new_x = end->x;
                    int new_y = end->y;

                    // change x/y based on orientation
                    if(direction == LEFT){
                        new_x += 1; // add to the right side
                    }
                    else if(direction == RIGHT){
                        new_x -= 1; // add to the left side
                    } 
                    else if(direction == UP){
                        new_y += 1; // add to the bottom
                    } 
                    else if(direction == DOWN){
                        new_y -= 1; // add to the top
                    }
                    
                    // increase based off direction
                    Snake* tail = create_tail(end->x, end->y); // creates tail w/ proper points
                    end->next = tail; // adds tail to the snake
                } 
                else if(type == Decrease){
                    // decrease
                    snake_length -= 1;
                    score -= 10; // remove 10 from the score
                    if(snake_length <= 1){
                        // death -- snake length is less than 1
                        state = DEAD;
                    } else {
                        snake = remove_tail(snake); // overwrite the new snake without the tail
                    }
                } 
                
                // removing and creating a new fruit -- took this code from for loop above
                // remove 1 fruit
                remove_eaten_food(foods, x, y);
                // create 1 fruit
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
                }

                // enemy snake collision with main snake -- dead condition
                int col_one = snake_collision(snake, one), col_two = snake_collision(snake, two);
                if(col_one || col_two){
                    state = DEAD;
                }
            }
			
            // Draw everything on the screen
            clear();
            attron(COLOR_PAIR(OBSTACLES));
            draw_Gamewindow(window);
            attroff(COLOR_PAIR(OBSTACLES));
            attron(COLOR_PAIR(SNAKE));
            draw_snake(snake);
            attroff(COLOR_PAIR(SNAKE));
            attron(COLOR_PAIR(FOOD));
            draw_food(foods);
            attroff(COLOR_PAIR(FOOD));
            attron(COLOR_PAIR(ESNAKECOLOR));
            draw_snake(one);
            draw_snake(two);
            attroff(COLOR_PAIR(ESNAKECOLOR));
            attron(COLOR_PAIR(OBSTACLES));
            draw_obstacle(obs);
            attroff(COLOR_PAIR(OBSTACLES));  
            mvprintw(0,0, "Score: %d", score);
            mvprintw(2,0, "Lives: %d", lives);  
            mvprintw(4,0,"%d %d %d %d\n", one->x, one->y, (int)x_space, (int)y_space);
            break;
        case PAUSE:
            ch = get_char();
            int saved = 0;

            // Key input choice -- for when you aren't using enter
            if(ch == START){
                // resume
                state = ALIVE;
            }
            else if(ch == SAVE){
                // save
                saveGameState(savePtr, foods, snake, window, obs, direction, score);
                saved = 1;
            }
            else if(ch == QUIT){
                state = DEAD;
            }

            // navigate menu
            if(ch == DOWN){
                if(menu_pointer[0] == 20 || menu_pointer[0] == 22){
                    menu_pointer[0] += 2;
                    clear();
                }
            }
            if(ch == UP){
                if(menu_pointer[0] == 24 || menu_pointer[0] == 22){
                    menu_pointer[0] -= 2;
                    clear();
                }
            }

            // selecting choice
            if(ch == 10){
                if(menu_pointer[0] == 20){
                    // resume
                    state = ALIVE;
                    break;
                }
                else if(menu_pointer[0] == 25){
                    // save
                    saveGameState(savePtr, foods, snake, window, obs, direction, score);
                    saved = 1;
                }
                else if(menu_pointer[0] == 30){
                    // quit
                    state = DEAD;
                    break;
                }
            }

            // Display
            mvprintw(18,10,"Paused ಠ_ಠ\n");
            mvprintw(20,20,"(s) to start again\n");
            mvprintw(22,20,"(f) to save the current game\n");
            mvprintw(24,20,"(q) to quit\n");
            mvprintw(menu_pointer[0], menu_pointer[1], "*");
            if(saved == 1){
                mvprintw(26,20, "Game has been saved successfully\n");
            }
            break;
        case DEAD:
            clear();
            mvprintw(20,20,"GAME OVER\n");
            mvprintw(25,20, "POINTS: %d\n", score);
            endwin();
            writeTopScores(bestFive, score); // check the top 5 scores here
            state = EXIT;
            break;
        
        case EXIT:
            clear();
            mvprintw(20,20,"GAME OVER\n");
            mvprintw(25,20, "POINTS: %d\tLIVES: %d\n", score, lives);
            endwin();
            break;
        }

        refresh();
        nanosleep(&timeret, NULL);
    }
}

char* getFilename(FILE *savePtr){
    char* filename = malloc(25 * sizeof(char));
    // dynamically assign the file save number
    int num = 0;
    while(true){
        sprintf(filename,"./saves/save_%d.game",num);
        if((savePtr = fopen(filename,"r")) == NULL){
            //file stuff here
            break;
        }
        num++;
    }
    return filename;
}

void writeTopScores(FILE *bestFive, int score){
    // init data structs for operation
    int top_five[6] = { 0 }, count = 0, i;
    char* temp = malloc(5 * sizeof(char));

    // initialize values
    bestFive = fopen("./saves/save_best_5.game","r");
    top_five[5] = score;
    
    // read file to init the top 10 scores 
    if(bestFive != NULL){
        while(fgets(temp, 4, bestFive) != NULL && count < 5){
            // convert file values to int
            top_five[count] = strtol(temp, NULL, 10);
            count++;
        }
    }

    
    // sort array using qsort built-in
    qsort(top_five, 6, sizeof(int), cmpfunc); // sort the array using the cmpfunc function defined above
    fclose(bestFive);

    // save the top 10 to the best scores file overwrite the file
    bestFive = fopen("./saves/save_best_5.game","w+");
    if(bestFive != NULL){
        for(i = 0; i < 5; i++){// process first 10 elements
            // print the number and then newline
            fprintf(bestFive, "%d\n", top_five[i]);
        }
    }

}

int getSaveCount(FILE *savePtr){
    // read file to init the top 10 scores 
    char* filename = malloc(25 * sizeof(char));
    int num = 0;
    while(true){
        sprintf(filename,"./saves/save_%d.game",num);
        if((savePtr = fopen(filename,"r")) == NULL){
            //file stuff here
            break;
        }
        num++;
    }
    return num;
}

void saveGameState(FILE *savePtr, Food *foods, Snake *snake, gamewindow_t *window, Obstacle *obs, int direction, int score){
    // malloc and init vars
    char* filename = getFilename(savePtr);
    char* fruit_info = malloc(150*sizeof(char));
    char* snake_info = malloc(30 * sizeof(char));
    char* game_info = malloc(30*sizeof(char));
    char* obs_info = malloc(200*sizeof(char));

    fruit_info = food_information(foods);
    snake_info =  snake_information(snake);
    game_info = gamewindow_information(window);
    obs_info = obstacle_information(obs);

    // saving data
    savePtr = fopen(filename, "w+");
    fprintf(savePtr, "Fruits:\n");
    fprintf(savePtr, "%s", fruit_info);
    fprintf(savePtr, "Snake:\n");
    fprintf(savePtr, "%s", snake_info);
    fprintf(savePtr, "size: %d\n", snake_size(snake));
    fprintf(savePtr, "direction: %d\n", direction);
    fprintf(savePtr, "Gamewindow:\n");
    fprintf(savePtr, "%s", game_info);
    fprintf(savePtr, "Obstacles:\n");
    fprintf(savePtr, "%s", obs_info);
    fprintf(savePtr, "score: %d\n", score);
    fclose(savePtr);
}

size_t vSeparateSringByComma (char* string, char output[9][3], int row, int col)
{
    const char *delims = ",";
    char *s = string;
    size_t n = 0, len;

    for (s = strtok (s, delims); s && n < row; s = strtok(NULL, delims))
        if ((len = strlen(s)) < col)
            strcpy(output[n++], s);

    return n;
}
