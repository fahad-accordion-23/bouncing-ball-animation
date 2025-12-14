#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** data;
    uint32_t cols;
    uint32_t rows;
} Buffer;

typedef struct {
    uint32_t x; 
    uint32_t y;
} Vector2u;

typedef struct {
    int32_t x;
    int32_t y;
} Vector2i;


void buffer_init(Buffer* buffer, uint32_t cols, uint32_t rows);
void buffer_clear(Buffer* buffer);
void buffer_display(Buffer* buffer);
void buffer_free(Buffer* buffer);

void draw_circle(Buffer* buffer, Vector2u position, uint32_t radius);
void draw_ellipse(Buffer* buffer, Vector2u position, uint32_t x_length, uint32_t y_length);
void draw_border(Buffer* buffer);

#endif // !DRAW_H
