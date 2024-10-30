#include "raylib.h"
#include <stdio.h>

void init();
void quit();

const int width = 800;
const int height = 600;

typedef struct {
    char* file_path;
    int x;
    int y;
    Texture2D texture; // Store texture in Asset struct
} Asset;

Asset load_asset(char *file_path, int x, int y) {
    Asset new_asset;
    new_asset.file_path = file_path;
    new_asset.x = x;
    new_asset.y = y;
    new_asset.texture = LoadTexture(file_path); // Load texture here
    return new_asset;
}

void render_asset(Asset new_asset) {
    float scale = 0.5f; // Scale down to 50% of the original size
    Rectangle src = {0, 0, new_asset.texture.width, new_asset.texture.height}; // Use full texture
    Rectangle dst = {new_asset.x, new_asset.y, new_asset.texture.width * scale, new_asset.texture.height * scale}; // Scale down size
    Vector2 origin = {0, 0};
    double rotation = 0.0f;
    DrawTexturePro(new_asset.texture, src, dst, origin, rotation, WHITE);
}


int main() {
    init();
    Asset table = load_asset("Assets/table.png", 50, 50);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_asset(table);
        // TODO GAME LOGIC
        EndDrawing();
    }

    quit(table); // Pass table to unload texture
    return 0;
}

void init() {
    InitWindow(width, height, "8ball pool game");
    SetTargetFPS(60);
}

void quit(Asset asset) {
    UnloadTexture(asset.texture); // Unload texture here
    CloseWindow();
}
