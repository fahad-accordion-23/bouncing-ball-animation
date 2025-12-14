#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLS 50
#define ROWS 20

char **init_buffer(uint32_t cols, uint32_t rows);
void clear_buffer(char** buffer, uint32_t cols, uint32_t rows);
void display_buffer(char** buffer, uint32_t cols, uint32_t rows);

void draw_circle(char** buffer, uint32_t radius);
void draw_ellipse(char** buffer, uint32_t x_axis, uint32_t y_axis);

int main(int argc, char** argv)
{
    char** display = init_buffer(COLS, ROWS); 
    
    while (1)
    {
        clear_buffer(display, COLS, ROWS); 
        
        draw_ellipse(display, 10, 5);

        display_buffer(display, COLS, ROWS);
    }

    return 0;
}

char** init_buffer(uint32_t cols, uint32_t rows)
{
    char** buffer = malloc(ROWS * sizeof(char*));
    for (int i = 0; i < ROWS; i++)
    {
        buffer[i] = malloc(COLS * sizeof(char));
        memset(buffer[i], ' ', COLS * sizeof(char));
    }

    return buffer;
}

void clear_buffer(char** buffer, uint32_t cols, uint32_t rows)
{
    for (int i = 0; i < rows; i++)
    {
        memset(buffer[i], ' ', cols * sizeof(char));
    }
}

void display_buffer(char** buffer, uint32_t cols, uint32_t rows)
{
    printf("\033[H");

    for(int i = 0; i < ROWS; i++)
    {
        fwrite(buffer[i], 1, COLS, stdout);
        printf("\n");
    }

    fflush(stdout);
}

void draw_circle(char** buffer, uint32_t radius)
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
                buffer[j][i] = '*';
        }
    }
}

void draw_ellipse(char** buffer, uint32_t x_axis, uint32_t y_axis)
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
                buffer[j][i] = '*';
        }
    }
}
