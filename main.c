#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLS 50
#define ROWS 20

typedef struct {
    char** data;
    uint32_t cols;
    uint32_t rows;
} Buffer;

void buffer_init(Buffer* buffer, uint32_t cols, uint32_t rows);
void buffer_clear(Buffer* buffer);
void buffer_display(Buffer* buffer);
void buffer_free(Buffer* buffer);

void draw_circle(Buffer* buffer, uint32_t radius);
void draw_ellipse(Buffer* buffer, uint32_t x_axis, uint32_t y_axis);

int main(int argc, char** argv)
{
    Buffer display = { 0 };
    buffer_init(&display, COLS, ROWS);

    while (1)
    {
        buffer_clear(&display);

        draw_ellipse(&display, 10, 5);

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

    for(int i = 0; i < buffer->rows; i++)
    {
        fwrite(buffer->data[i], 1, buffer->cols, stdout);
        printf("\n");
    }

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

void draw_circle(Buffer* buffer, uint32_t radius)
{
    uint32_t center_x = radius - 1;
    uint32_t center_y = radius - 1;
    uint32_t diameter = radius * 2;
    uint32_t radius_squared = radius * radius;

    for (int j = 0; j < diameter - 1; j++)
    {
        for (int i = 0; i < diameter - 1; i++)
        {
             uint32_t distance_squared = ((j - center_y) * (j - center_y)) 
                                       + ((i - center_x) * (i - center_x));

            if (distance_squared <= radius_squared)
                buffer->data[j][i] = '*';
        }
    }
}

void draw_ellipse(Buffer* buffer, uint32_t x_axis, uint32_t y_axis)
{
    uint32_t center_x = x_axis;
    uint32_t center_y = y_axis;
    uint32_t end_x = x_axis * 2;
    uint32_t end_y = y_axis * 2;
    uint32_t x_axis_squared = x_axis * x_axis;
    uint32_t y_axis_squared = y_axis * y_axis;

    for (int j = 0; j <= end_y; j++)
    {
        for (int i = 0; i <= end_x; i++)
        {
            /* 
             * Formula:
             * (x^2 / a^2) + (y^2 / b^2) <= 1
             * (x^2 * b^2) + (y^2 * a^2) <= a^2 * b^2
             */

            uint32_t x_squared = (i - center_x) * (i - center_x);
            uint32_t y_squared = (j - center_y) * (j - center_y);

            if ((x_squared * y_axis_squared) + (y_squared * x_axis_squared) <= (x_axis_squared * y_axis_squared))
                buffer->data[j][i] = '*';
        }
    }
}
