#include <stdio.h>
#include <unistd.h>
#include "draw.h"

#define COLS 100
#define ROWS 30
#define FPS 24
#define LOSS 0.50f
#define GRAVITY 0.25f

void decelerate(Vector2f* velocity)
{
    if (velocity->x > 0)
        velocity->x -= LOSS;
    else if (velocity->x < 0)
        velocity->x += LOSS;

    if (velocity->y > 0)
        velocity->y -= LOSS;
    else if (velocity->y < 0)
        velocity->y += LOSS;
}

int main()
{
    printf("\033[2J\033[H");
    fflush(stdout);

    Buffer display = { 0 };
    buffer_init(&display, COLS, ROWS);
    
    Vector2f f_ball_position = { 15.0, 7.0 };
    Vector2i i_ball_position = { 15, 7 };

    Vector2i ball_dimensions = { 10, 5 };
    Vector2f ball_velocity = { 3.0, 0.0 };
    
    while (1)
    {
        ball_velocity.y += GRAVITY;

        f_ball_position.x += ball_velocity.x;
        f_ball_position.y += ball_velocity.y;

        if (f_ball_position.x - (ball_dimensions.x + 1) <= 0)
        {
            f_ball_position.x = ball_dimensions.x + 1;
            decelerate(&ball_velocity);
            ball_velocity.x *= -1;
        }
        else if (f_ball_position.x + (ball_dimensions.x + 1) >= display.cols - 1)
        {
            f_ball_position.x = (display.cols - 1) - (ball_dimensions.x + 1);
            decelerate(&ball_velocity);
            ball_velocity.x *= -1;
        }
        
        if (f_ball_position.y - (ball_dimensions.y + 1) <= 0)
        {
            f_ball_position.y = ball_dimensions.y + 1;
            decelerate(&ball_velocity);
            ball_velocity.y *= -1;
        }
        else if (f_ball_position.y + (ball_dimensions.y + 1) >= display.rows - 1)
        {
            f_ball_position.y = (display.rows - 1) - (ball_dimensions.y + 1);
            decelerate(&ball_velocity);
            ball_velocity.y *= -1;
        }

        i_ball_position.x = (int)f_ball_position.x;
        i_ball_position.y = (int)f_ball_position.y;

        buffer_clear(&display);
        draw_ellipse(&display, i_ball_position, ball_dimensions);
        draw_border(&display);
        buffer_display(&display);

        usleep((1 * 1000 * 1000) / FPS);
    }

    buffer_free(&display);

    return 0;
}
