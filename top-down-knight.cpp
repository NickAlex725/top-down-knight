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
    const float mapScale = 4.0f;

    Character knight(winWidth, winHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        
        //draw map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());
        // check map bounds
        if(knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + winWidth > map.width * mapScale || 
            knight.getWorldPos().y + winHeight > map.height * mapScale)
            {
                knight.undoMovement();
            }

        EndDrawing();
    }
    CloseWindow(); 
}