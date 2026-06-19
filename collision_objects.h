#include "raylib.h"

#define MAX_OBJECTS 1000
#define MinMax 2
#define NumColors 25

const Color colors[] = { LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK,
			RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE,
			DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN,
			DARKBROWN, WHITE, BLACK, MAGENTA, RAYWHITE };

typedef struct {
	float radius;
	int x, y;
	double float velx, vely;
	Color color;

} Object;


typedef struct {
	Object objects[MAX_OBJECTS];
	int obj_num;
	float x[MinMax],y[MinMax];

} Environment;

int init_environment(Environment* env);

int add_object(); 

int remove_object();

void check_collision();


