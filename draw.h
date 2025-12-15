#ifndef DRAW_H
#define DRAW_H

typedef struct {
    char** data;
    int cols;
    int rows;
} Buffer;

typedef struct {
    int x;
    int y;
} Vector2i;

typedef struct {
    float x;
    float y;
} Vector2f;

void buffer_init(Buffer* buffer, int cols, int rows);
void buffer_clear(Buffer* buffer);
void buffer_display(Buffer* buffer);
void buffer_free(Buffer* buffer);

void draw_circle(Buffer* buffer, Vector2i position, int radius);
void draw_ellipse(Buffer* buffer, Vector2i position, Vector2i dimensions);
void draw_border(Buffer* buffer);

#endif // !DRAW_H
