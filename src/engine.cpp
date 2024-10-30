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
    float scale;
    Texture2D texture;
    bool isTilemap;
    int tileWidth;
    int tileHeight;
} Asset;

Asset load_asset(char *file_path, int x, int y, float scale) {
    Asset new_asset;
    new_asset.file_path = file_path;
    new_asset.x = x;
    new_asset.y = y;
    new_asset.scale = scale;
    new_asset.texture = LoadTexture(file_path);
    new_asset.isTilemap = false; // Not a tilemap
    new_asset.tileWidth = new_asset.texture.width;
    new_asset.tileHeight = new_asset.texture.height;
    return new_asset;
}

Asset load_asset_tilemap(char *file_path, int x, int y, int tileWidth, int tileHeight, float scale) {
    Asset new_asset;
    new_asset.file_path = file_path;
    new_asset.x = x;
    new_asset.y = y;
    new_asset.scale = scale;
    new_asset.texture = LoadTexture(file_path);
    new_asset.isTilemap = true;
    new_asset.tileWidth = tileWidth;
    new_asset.tileHeight = tileHeight;
    return new_asset;
}

void render_asset(Asset new_asset, int tileX, int tileY) {
    Rectangle src, dst;
    if (new_asset.isTilemap) {
        src = (Rectangle){tileX * new_asset.tileWidth, tileY * new_asset.tileHeight, new_asset.tileWidth, new_asset.tileHeight};
        dst = (Rectangle){new_asset.x, new_asset.y, new_asset.tileWidth * new_asset.scale, new_asset.tileHeight * new_asset.scale};
    } else {
        src = (Rectangle){0, 0, new_asset.texture.width, new_asset.texture.height};
        dst = (Rectangle){new_asset.x, new_asset.y, new_asset.texture.width * new_asset.scale, new_asset.texture.height * new_asset.scale};
    }

    Vector2 origin = {0, 0};
    DrawTexturePro(new_asset.texture, src, dst, origin, 0.0f, WHITE);
}

int main() {
    init();
    Asset table = load_asset("Assets/table.png", 50, 50, 0.5f);
    Asset tilemap = load_asset_tilemap("Assets/tilemap.png", 100, 100, 32, 32, 1.0f);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        render_asset(table, 0, 0);        // Renders a regular asset
        render_asset(tilemap, 2, 1);      // Renders a specific tile from the tilemap (3rd column, 2nd row)

        EndDrawing();
    }

    quit(table);
    quit(tilemap);
    return 0;
}

void init() {
    InitWindow(width, height, "8ball pool game");
    SetTargetFPS(60);
}

void quit(Asset asset) {
    UnloadTexture(asset.texture);
    CloseWindow();
}
