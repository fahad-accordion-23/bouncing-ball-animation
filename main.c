#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLS 132
#define ROWS 43

typedef struct {
    char** data;
    uint32_t cols;
    uint32_t rows;
} Buffer;

void buffer_init(Buffer* buffer, uint32_t cols, uint32_t rows);
void buffer_clear(Buffer* buffer);
void buffer_display(Buffer* buffer);
void buffer_free(Buffer* buffer);

typedef struct {
    uint32_t x; 
    uint32_t y;
} Vector2u;

typedef struct {
    int32_t x;
    int32_t y;
} Vector2i;

void draw_circle(Buffer* buffer, Vector2u position, uint32_t radius);
void draw_ellipse(Buffer* buffer, Vector2u position, uint32_t x_length, uint32_t y_length);

int main(int argc, char** argv)
{
    Buffer display = { 0 };
    buffer_init(&display, COLS, ROWS);

    Vector2u pos1 = { 30, 20 };
    Vector2u pos2 = { 60, 30 };

    while (1)
    {
        buffer_clear(&display);

        draw_ellipse(&display, pos1, 25, 12);
        draw_ellipse(&display, pos2, 30, 15);

        buffer_display(&display);

        usleep(50 * 1000);
    }

    buffer_free(&display);

    return 0;
}

void buffer_init(Buffer* buffer, uint32_t cols, uint32_t rows)
{
    buffer->data = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++)
    {
        buffer->data[i] = malloc(cols * sizeof(char));
        memset(buffer->data[i], ' ', cols * sizeof(char));
    }

    buffer->cols = cols;
    buffer->rows = rows;
}

void buffer_clear(Buffer* buffer)
{
    for (int i = 0; i < buffer->rows; i++)
    {
        memset(buffer->data[i], ' ', buffer->cols * sizeof(char));
    }
}

void buffer_display(Buffer* buffer)
{
    printf("\033[H");

    for(int i = 0; i < buffer->rows - 1; i++)
    {
        fwrite(buffer->data[i], 1, buffer->cols, stdout);
        printf("\n");
    }

    fwrite(buffer->data[buffer->rows - 1], 1, buffer->cols, stdout);

    fflush(stdout);
}

void buffer_free(Buffer* buffer)
{
    for (int i = 0; i < buffer->rows; i++)
        free(buffer->data[i]);
    free(buffer->data);

    buffer->data = NULL;
    buffer->cols = 0;
    buffer->rows = 0;
}

void draw_circle(Buffer* buffer, Vector2u position, uint32_t radius)
{
    Vector2i start = { position.x - radius, position.y - radius };
    Vector2i end = { position.x + radius, position.y + radius };

    uint32_t radius_squared = radius * radius;

    for (int j = start.y; j <= end.y; j++)
    {
        for (int i = start.x; i <= end.x; i++)
        {
            if (j < 0 || j >= buffer->rows || i < 0 || i >= buffer->cols)
                continue;

            int32_t distance_x = i - position.x;
            int32_t distance_y = j - position.y;
            uint32_t distance_squared = (distance_x * distance_x) + (distance_y * distance_y);

            if (distance_squared <= radius_squared)
                buffer->data[j][i] = '*';
        }
    }
}

void draw_ellipse(Buffer* buffer, Vector2u position, uint32_t x_length, uint32_t y_length)
{
    Vector2i start = { position.x - x_length, position.y - y_length };
    Vector2i end = { position.x + x_length, position.y + y_length };

    uint32_t x_length_squared = x_length * x_length;
    uint32_t y_length_squared = y_length * y_length;

    for (int j = start.y; j <= end.y; j++)
    {
        for (int i = start.x; i <= end.x; i++)
        {
            if (j < 0 || j >= buffer->rows || i < 0 || i >= buffer->cols)
                continue;

            /* 
             * Formula:
             *
             * x := i
             * y := j
             * h := position.x
             * k := position.y
             * a := x_length
             * b := y_length
             * 
             *
             * ((x - h)^2 / a^2) + ((y - k)^2 / b^2) <= 1
             * ((x - h)^2 * b^2) + ((y - k)^2 * a^2) <= a^2 * b^2
             *
             * (x - h) ^ 2 := x_squared
             * (x - k) ^ 2 := y_squared
             */

            uint32_t x_squared = (i - position.x) * (i - position.x);
            uint32_t y_squared = (j - position.y) * (j - position.y);

            if ((x_squared * y_length_squared) + (y_squared * x_length_squared) <= (x_length_squared * y_length_squared))
                buffer->data[j][i] = '*';
        }
    }
}
