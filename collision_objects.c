#include <stdlib.h>
#include <time.h>
#include "collisions_objects.h"
#include "raylib.h"

#define MAX_RADIUS 20

int init_environment(Environment* env){
	env = malloc(sizeof(Environment));
	if (!env) { return 1; }

	env->obj_num = 0;
	env->x[0] = 0;
	env->y[0] = 0;
	env->x[1] = GetScreenWidth();
	env->y[1] = GetScreenHeight();

	return 0;
}

int add_object(Environment* env) {
	if (!(env->obj_num < MAX_OBJECTS)) { return 1; }

	srand(time(NULL));
	
	env->obj_num++;

	Object* obj = &env->objects[obj_num-1];

	obj->radius = rand()%MAX_RADIUS;
	obj->color = colors[rand()%COLORS];
	obj->x = rand()%env->x[1];
	obj->y = rand()%env->y[1];
	obj->velx = rand()%5;
	obj->vely = rand()%5;

	return 0;

int remove_object(Environment* env) {
	if (env->obj_num == 0) { return 1; }

	env->obj_num--;

	return 0;


// TODO: - collision detection
// 	 - velocity update
// 	 - position update
void check_collision(Environment* env) {
	
	for ( int i = 0; i < env->obj_num; i++) {
		Object* one = &env->objects[i];
		for (int j = i+1; j < env->obj; j++) {
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
				printf("BANG\n");

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
