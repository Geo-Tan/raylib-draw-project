#include <raylib.h>
#include <raymath.h>

struct Pen {
    Color color;
    int size;
    Vector2 pos;
    Vector2 prev;   // relative to canvas
};

bool penDraw(Image *canvas, struct Pen *pen);
