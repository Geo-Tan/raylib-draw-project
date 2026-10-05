#include <stdio.h>
#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "def.h"
#include "pen.h"

// TODO:
// - add relative to where image is (not 0,0)
// - set up multiple canvas
// - undo feature
// - add a simple ui

int main(void) {
    printf("init window\n");
    InitWindow(WIDTH, HEIGHT, "Alpha 0");
    // EnableEventWaiting();
    Image canvas = GenImageColor(GRIDC, GRIDR, RAYWHITE);
    Texture texture = LoadTextureFromImage(canvas);

    struct Pen pen = {
        .color = BLACK,
        .pos = 0,
        .prev = 0, // relative
        .size = 1
    };

    SetTargetFPS(60);
    Vector2 prev;
    Color save; // bad way to remember color
    while (!WindowShouldClose()) {
// ---
        pen.pos = GetMousePosition();
        bool update = penDraw(&canvas, &pen);
// ---
        if (IsKeyPressed(KEY_SPACE)) {
            ImageClearBackground(&canvas, RAYWHITE);
            update = true;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            bool success = ExportImage(canvas, "saved_image.png");
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
            if (ColorIsEqual(pen.color, RAYWHITE)) {
                pen.color = save;
            }
            else {
                save = pen.color;
                pen.color = RAYWHITE;
            }
        }

        pen.size += GetMouseWheelMove();
        if (pen.size < PEN_MIN) pen.size = PEN_MIN;
        else if (pen.size > PEN_MAX) pen.size = PEN_MAX;
// ---
        if (update) UpdateTexture(texture, canvas.data);

        BeginDrawing();
            DrawTextureEx(texture, (Vector2){0.0f * 4, 0.0f}, 0.0f, UNIT, WHITE);
            int x = pen.pos.x / UNIT;
            int y = pen.pos.y / UNIT;
            if(ColorIsEqual(pen.color, RAYWHITE)) {
                DrawRectangleLines((x - pen.size) * UNIT, (y - pen.size) * UNIT, UNIT * pen.size, UNIT * pen.size, BLACK);
            }
            else {
                DrawRectangle((x - pen.size) * UNIT, (y - pen.size) * UNIT, UNIT * pen.size, UNIT * pen.size, pen.color);
            }
            DrawFPS(10, 10);
        EndDrawing();
    }
    UnloadImage(canvas);
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}

