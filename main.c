#include <stdlib.h>
#include "collision_objects.h"
#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    Environment env;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
	
    if (init_environment(&env)) { return 1; }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

	// Check for collisions before making changed to the environment
	if (IsWindowResized()) { set_environment_boundaries(&env); }

        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_EQUAL)) { add_object(&env); }
        if (IsKeyPressed(KEY_MINUS)) { remove_object(&env); }

	check_collision(&env);
	//----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

	    draw_environment(&env);

            DrawText("Congrats! You created your first window!", 0, 0, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
