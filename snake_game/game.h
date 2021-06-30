#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
void game();
void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset);
int compare(void *a, void *b);
// custom methods to clean up the code base
void writeTopScores(FILE *bestFive, int score);
void saveGameState();
char* getFilename(FILE *savePtr);
int getSaveCount(FILE *savePtr);
size_t vSeparateSringByComma (char* string, char output[9][3], int row, int col);

enum State{INIT, ALIVE, DEAD, PAUSE, EXIT, WELCOME, CREATE, LOADGAME, LOADINIT };

