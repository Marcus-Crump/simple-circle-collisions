#include <stdlib.h>
#include <time.h>
#include "collision_objects.h"
#include "raylib.h"

#define MAX_RADIUS 20

const Color los_colores[] = { LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK,
			RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE,
			DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN,
			DARKBROWN, WHITE, BLACK, MAGENTA, RAYWHITE };

Environment* init_environment(){
	Environment* env = malloc(sizeof(Environment));
	if (!env) { return NULL; }

	env->obj_num = 0;
	env->x[0] = 0;
	env->y[0] = 0;
	set_environment_boundaries(env);
	return env;
}

void set_environment_boundaries(Environment* env) {
	env->x[1] = GetScreenWidth();
	env->y[1] = GetScreenHeight();
}

int add_object(Environment* env) {
	if (!(env->obj_num < MAX_OBJECTS)) { return 1; }

	srand(time(NULL));
	
	env->obj_num++;

	Object* obj = &env->objects[env->obj_num-1];

	while (!(obj->radius = rand()%MAX_RADIUS)) {}
	obj->color = los_colores[rand()%COLORS];
	obj->x = rand()%env->x[1];
	obj->y = rand()%env->y[1];
	obj->velx = rand()%5;
	obj->vely = rand()%5;

	return 0;
}

int remove_object(Environment* env) {
	if (env->obj_num == 0) { return 1; }

	env->obj_num--;

	return 0;
}

void update_object_positions(Environment* env) {

	for (int i = 0; i < env->obj_num; i++) {
		Object* cur = &env->objects[i];
		cur->x += cur->velx;
		cur->y += cur->vely;
	}

}

// TODO: - collision detection
// 	 - velocity update
// 	 - position update
void check_collision(Environment* env) {
	
	for ( int i = 0; i < env->obj_num; i++) {
		Object* one = &env->objects[i];
		
		if ((one->x + one->radius) > env->x[1]) {
			one->x = env->x[1] - one->radius;
		} else if ((one->x - one->radius) < env->x[0]) {
			one->x = env->x[0] + one->radius;
		}


		if ((one->y + one->radius) > env->y[1]) {
			one->y= env->y[1] - one->radius;
		} else if ((one->y - one->radius) < env->y[0]) {
			one->y = env->y[0] + one->radius;
		}

		for (int j = i+1; j < env->obj_num; j++) {
			Object* two = &env->objects[j];

			int dtotalsq = ((two->x - one->x)*(two->x - one->x));
			dtotalsq += ((two->y - one->y)*(two->y - one->y));

			int radsum = one->radius + two->radius;

			// IMPORTANT PART TO STUDY AND UNDERSTAND FOR MECHANICAL PHYSICS
			if ( dtotalsq < (radsum*radsum) ) {
				// NEEDS FIXING DUE TO VELOCITY BEING GENERATED WHEN HITTING SLOWER
				// OBJECTS MOVING IN THE SAME DIRECTION
				// Collision occured
				// Set the velocity of either object to go in opposite x*=-1 y*=-1

				// variables to store the inital velocity of obj one
				int one_vx = one->velx;
				int one_vy = one->vely;
				
				one->velx += two->velx;
				one->vely += two->vely;
				two->velx += one_vx;
				two->vely += one_vy;
			}
		}
	}
}

void draw_environment(Environment* env) {
	//DrawCircle(int centerX, int centerY, float radius, Color color);
	for (int i = 0; i < env->obj_num; i++) {
		Object obj = env->objects[i];

		DrawCircle(obj.x, obj.y, obj.radius, obj.color);
	}
}
