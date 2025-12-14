#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define COLS 50
#define ROWS 20

void draw_circle(char** buffer, uint32_t radius);
void draw_ellipse(char** buffer, uint32_t x_axis, uint32_t y_axis);

int main(int argc, char** argv)
{
    char** display = malloc(ROWS * sizeof(char*));
    for (int i = 0; i < ROWS; i++)
    {
        display[i] = malloc(COLS * sizeof(char));
        memset(display[i], ' ', COLS * sizeof(char));
    }


    //draw_circle(display, 10);
    //printf("\n");
    draw_ellipse(display, 10, 5);

    for(int i = 0; i < ROWS; i++)
    {
        fwrite(display[i], 1, COLS, stdout);
        printf("\n");
    }

    fflush(stdout);

    return 0;
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
