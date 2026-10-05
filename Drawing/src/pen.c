#include "def.h"
#include <raylib.h>
#include "pen.h"

bool penDraw(Image *canvas, struct Pen *pen) {
    Vector2 rel = Vector2Scale(pen->pos, 1/UNIT);

    if (rel.y > canvas->height || rel.y < 0) {
        if (rel.x > canvas->width || rel.x < 0) {
            return false;
        }
    }

    bool update;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        for (int i = 1; i < pen->size + 1; i++) {
            for (int j = 1; j < pen->size + 1; j++) {
                ImageDrawPixel(canvas, rel.x - i, rel.y - j, pen->color);
                int x = (int)rel.x - (int)pen->prev.x;
                int y = (int)rel.y - (int)pen->prev.y;
                // if jumps a pixel, fill with line
                if (x > 1 || x < -1 || y > 1 || y < -1) {
                    ImageDrawLine(canvas, pen->prev.x - i, pen->prev.y - j, rel.x - i, rel.y - j, pen->color);
                }

            }
        }

        pen->prev = rel;
        update = true;
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        // index++;
        // if (index >= 9) {
        //     index = 0;
        // }
        // pen = palette[index];
        if (ColorIsEqual(pen->color, RAYWHITE)) return update;

        if (ColorIsEqual(pen->color,BLACK)) {
            pen->color = RED;
        }
        else {
            pen->color = BLACK;
        }
    }
    else {
        pen->prev = rel;
    }

    return update;
}
