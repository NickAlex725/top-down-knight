#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return WorldPos; }+
    
private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 ScreenPos;
    Vector2 WorldPos;
    // 1 : facing right, -1 : facing left                    
    float rightLeft = 1.f;
    // animation variables
    float runningTime;
    int frame;
    const int maxFrames = 6;
    const float updateTime = 1.f/12.f;
};

int main()
{
    const int winWidth = 384;
    const int winHeight = 384;
    InitWindow(winWidth, winHeight, "Top Down Knight");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos;
    float speed = 4.0;

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = knight_idle;
    Vector2 knightPos = {(float)winWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
                        (float)winHeight/2.0f - 4.0f * (0.5f * (float)knight.height)};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }
        
        //draw map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //update animation frame
        runningTime += GetFrameTime();
        if ( runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        //draw character
        Rectangle source = {frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle dest = {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    CloseWindow(); 
}