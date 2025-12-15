#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buffer_init(Buffer* buffer, int cols, int rows)
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

void draw_circle(Buffer* buffer, Vector2i position, int radius)
{
    Vector2i start = { position.x - radius, position.y - radius };
    Vector2i end = { position.x + radius, position.y + radius };

    int radius_squared = radius * radius;

    for (int j = start.y; j <= end.y; j++)
    {
        for (int i = start.x; i <= end.x; i++)
        {
            if (j < 0 || j >= buffer->rows || i < 0 || i >= buffer->cols)
                continue;

            int distance_x = i - position.x;
            int distance_y = j - position.y;
            int distance_squared = (distance_x * distance_x) + (distance_y * distance_y);

            if (distance_squared <= radius_squared)
                buffer->data[j][i] = '*';
        }
    }
}

void draw_ellipse(Buffer* buffer, Vector2i position, Vector2i dimensions)
{
    Vector2i start = { position.x - dimensions.x, position.y - dimensions.y };
    Vector2i end = { position.x + dimensions.x, position.y + dimensions.y };

    int x_length_squared = dimensions.x * dimensions.x;
    int y_length_squared = dimensions.y * dimensions.y;

    for (int j = start.y; j <= end.y; j++)
    {
        for (int i = start.x; i <= end.x; i++)
        {
            if (j < 0 || j >= buffer->rows || i < 0 || i >= buffer->cols)
                continue;

            int x_squared = (i - position.x) * (i - position.x);
            int y_squared = (j - position.y) * (j - position.y);

            if ((x_squared * y_length_squared) + (y_squared * x_length_squared) <= (x_length_squared * y_length_squared))
                buffer->data[j][i] = '*';
        }
    }
}

void draw_border(Buffer* buffer)
{
    for (int i = 0; i < buffer->cols; i++)
    {
        buffer->data[0][i] = '-';
        buffer->data[buffer->rows - 1][i] = '-';
    }

    for (int j = 0; j < buffer->rows; j++)
    {
        buffer->data[j][0] = '|';
        buffer->data[j][buffer->cols - 1] = '|';
    }

    buffer->data[0][0] = '+';
    buffer->data[0][buffer->cols - 1] = '+';
    buffer->data[buffer->rows - 1][0] = '+';
    buffer->data[buffer->rows - 1][buffer->cols - 1] = '+';
}
