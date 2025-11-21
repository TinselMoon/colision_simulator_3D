#ifndef PARTICLE_H
#define PARTICLE_H
#include "particles.h"
#endif

int main(int argc, char **argv){
    if(argc < 3){
        printf("Error, not enough information\nRun: %s [width] [height] [num of particles]\n", argv[0]);
        exit(0);
    }
    srand(time(NULL));
    const int screenWidth = atoi(argv[1]);
    const int screenHeight = atoi(argv[2]);
    System *s = create();
    int num_particles = atoi(argv[3]);

    // Creating camera
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 100.0f, 100.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    int cameraMode = CAMERA_FREE;
    
    Box caixa = {100, 100, 100};
    for(int i = 0; i < num_particles; i++)
        insert_particle(s, screenWidth, screenHeight);

    InitWindow(screenWidth, screenHeight, "colisions simulator");
    SetTargetFPS(TARGET_FPS);               // Set our game to run at 60 frames-per-second
    double fps;
    ClearBackground(RAYWHITE);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateCamera(&camera, cameraMode);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        update_pos(s);
        for(int i = 0; i < 4; i++)fix_contacts(s, caixa);
        draw_particles(s);
        DrawCubeWires((Vector3){caixa.x/2,caixa.y/2,caixa.z/2}, caixa.x, caixa.y, caixa.z, DARKPURPLE);
        EndMode3D();
        EndDrawing();
        /*if (IsKeyPressed(KEY_I)){
            insert_particle(s, screenWidth, screenHeight);
            num_particles++;
        }
        BeginDrawing();
        if(!is_empty(s)){
            ClearBackground(RAYWHITE);
            if (IsKeyPressed(KEY_R)){
                remove_particle(s);
                num_particles--;
            }
            update_pos(s, screenWidth, screenHeight);
            for(int i = 0; i < 4; i++)fix_contacts(s, screenWidth, screenHeight);
            draw_particles(s);
        }
        fps = 1/GetFrameTime();
        DrawText(TextFormat("Number of Particles: %d\n"
                            "Press I to insert a particle\n"
                            "Press R to remove a particle\n"
                            "FPS: %.2f", num_particles, fps), 10, 10, 30, DARKGRAY);
        */
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    destroy(s);
    return 0;
}
