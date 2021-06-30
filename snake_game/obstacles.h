#include <stdbool.h>


struct obstacle
{
  int upper_left_x;
  int upper_left_y;
  int width;
  int height;
  char draw_char;
  struct obstacle* next;
};

typedef struct obstacle Obstacle;

Obstacle* init_obstacle(int x, int y, int width, int height);

Obstacle* create_obs(int x, int y, int offset);

void draw_obstacle(Obstacle *);

bool obs_bound_exists(Obstacle* obs, int x, int y);

void add_new_obs(Obstacle* obs, Obstacle* new_obs);

bool all_bound(Obstacle* obs, int x, int y);

char* obstacle_information(Obstacle* obs);
