#include <stdio.h>
#include <unistd.h>
#include "draw.h"

#define COLS 100
#define ROWS 30
#define FPS 24

int main()
{
    printf("\033[2J\033[H");
    fflush(stdout);

    Buffer display = { 0 };
    buffer_init(&display, COLS, ROWS);
    
    Vector2i ball_position = { 15, 7 };
    Vector2i ball_dimensions = { 10, 5 };
    Vector2i ball_velocity = { 1, 2 };

    while (1)
    {
        ball_position.x += ball_velocity.x;
        ball_position.y += ball_velocity.y;

        if (ball_position.x - (ball_dimensions.x + 1) <= 0)
        {
            ball_position.x = ball_dimensions.x + 1;
            ball_velocity.x *= -1;
        }
        else if (ball_position.x + (ball_dimensions.x + 1) >= display.cols - 1)
        {
            ball_position.x = (display.cols - 1) - (ball_dimensions.x + 1);
            ball_velocity.x *= -1;
        }
        
        if (ball_position.y - (ball_dimensions.y + 1) <= 0)
        {
            ball_position.y = ball_dimensions.y + 1;
            ball_velocity.y *= -1;
        }
        else if (ball_position.y + (ball_dimensions.y + 1) >= display.rows - 1)
        {
            ball_position.y = (display.rows - 1) - (ball_dimensions.y + 1);
            ball_velocity.y *= -1;
        }

        buffer_clear(&display);
        draw_ellipse(&display, ball_position, ball_dimensions.x, ball_dimensions.y);
        draw_border(&display);
        buffer_display(&display);

        usleep((1 * 1000 * 1000) / FPS);
    }

    buffer_free(&display);

    return 0;
}
