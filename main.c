#include <stdlib.h>
#include <stdio.h>
#include "collision_objects.h"
#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    Environment* env;

    SetTraceLogLevel(LOG_NONE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    if (!(env = init_environment())) { return 1; }
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

	// Check for collisions before making changed to the environment
	if (IsWindowResized()) { set_environment_boundaries(env); }

        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_EQUAL)) { add_object(env); }
        if (IsKeyPressed(KEY_MINUS)) { remove_object(env); }

	update_object_positions(env);

	check_collision(env);
	//----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

	    draw_environment(env);

            DrawText("Press '+' to add objects and '-' to remove them", 0, 0, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
