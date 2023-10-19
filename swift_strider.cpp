#include "raylib.h"

int main()
{

    // window dimensions
    int windowHeight{1080};
    int windowWidth{1920};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // defining nebula and loading it's texture
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); 

    // nebula source's dimensions and coordinates
    Rectangle nebRec;
    nebRec.x = 0;
    nebRec.y = 0;
    nebRec.width = nebula.width / 8;
    nebRec.height = nebula.height / 8;

    // position of the nebula's sprite
    Vector2 nebPos;
    nebPos.x = windowWidth;
    nebPos.y = windowHeight - nebRec.height;

    // defining scarfy and loading it's texture
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    // scarfy source's dimensions and coordinates
    Rectangle scarfyRec;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;

    // position of the scarfy's sprite
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 2) - (scarfyRec.width / 2);
    scarfyPos.y = windowHeight - scarfyRec.height;

    const int gravity{1600};
    const int jumpVel{-750};
    const int nebVel{-600};
    int velocity{};

    int frame{};

    // amount of time before we update the animation frame
    const float updateFrame(1.0 / 12.0);
    float runningTime{};

    bool isInAir{};

    // setting the target FPS to 60
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // begin drawing
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{GetFrameTime()};

        // game logic begins

        // performing ground check
        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // scarfy is on the ground so reset the velocity
            velocity = 0;
            isInAir = false;
        }

        else
        {
            // scarfy is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // implementing jump
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // updating nebula's position
        nebPos.x += nebVel * dT;

        // updating scarfy's position
        scarfyPos.y += velocity * dT;

        runningTime += dT;

        // updating each frame  
        if(!isInAir)
        {
            if(runningTime >= updateFrame)
            {
                runningTime = 0;

                scarfyRec.x = frame * scarfyRec.width;
                frame++;

                if(frame > 5)
                {
                    frame = 0;
                }

            }
        }

        // drawing scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // drawing nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // game logic ends
        // end drawing
        EndDrawing();
    }

    // unloading textures if scarfy and nebula 
    // closing the window
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}