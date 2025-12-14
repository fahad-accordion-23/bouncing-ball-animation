#include <stdio.h>
#include <stdint.h>

void draw_circle(uint32_t radius)
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
                printf("*");
            else
                printf(" ");
        }

        printf("\n");
    }
}

int main(int argc, char** argv)
{
    uint32_t radius = 10;
    draw_circle(radius);

    return 0;
}
