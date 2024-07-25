#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int winWidth = 384;
    const int winHeight = 384;
    InitWindow(winWidth, winHeight, "Top Down Knight");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos;

    Character knight;
    knight.setScreenPos(winWidth, winHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        
        //draw map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow(); 
}