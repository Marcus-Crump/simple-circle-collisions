#include "raylib.h"

#define MAX_OBJECTS 1000
#define MinMax 2
#define COLORS 25

typedef struct {
	float radius;
	int x, y, velx, vely;
	Color color;
	// for later implementation
	// float mass;

} Object;


typedef struct {
	Object objects[MAX_OBJECTS];
	int obj_num;
	int x[MinMax],y[MinMax];

} Environment;

Environment* init_environment();

void set_environment_boundaries(Environment* env);

int add_object(Environment* env); 

int remove_object(Environment* env);

void update_object_positions(Environment* env);

void check_collision(Environment* env);

void draw_environment(Environment* env);
