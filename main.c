#include <stdio.h>
#include <unistd.h>
#include "draw.h"

#define COLS 100
#define ROWS 30

int main(int argc, char** argv)
{
    printf("\033[2J\033[H");
    fflush(stdout);

    Buffer display = { 0 };
    buffer_init(&display, COLS, ROWS);

    Vector2u pos1 = { 15, 10 };

    while (1)
    {
        buffer_clear(&display);

        draw_ellipse(&display, pos1, 10, 5);
        draw_border(&display);

        buffer_display(&display);

        usleep(50 * 1000);
    }

    buffer_free(&display);

    return 0;
}
