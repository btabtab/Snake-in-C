#include <stdlib.h>
#include <memory.h>
#include "raylib.h"
typedef struct BodySegment
{
    Vector2 position, old_position, direction, prev_segment_position;
    int size;
} BodySegment;
typedef BodySegment Fruit;
int main(void)
{
    Fruit food;
    food.position = (Vector2){(rand() % 300 + 0), (rand() % 300 + 0)};
    int segment_count = 2, old_segment_count = 0;
    BodySegment snake_head = { 0 }; snake_head.size = 5;
    BodySegment* segments[100];
    segments[0] = malloc(sizeof(BodySegment));
    segments[1] = malloc(sizeof(BodySegment));
    snake_head.position = (Vector2){150.f, 150.f};
    InitWindow(300, 300, "C-snake - JME");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        {
            BeginDrawing();
            ClearBackground(GREEN);
            for(int i = 0; i != segment_count; i++){DrawCircle(segments[i]->old_position.x, segments[i]->old_position.y, 7 - (i / i+1), RED);}
            DrawCircle(food.position.x, food.position.y, snake_head.size, YELLOW);
            DrawCircle(snake_head.position.x, snake_head.position.y, snake_head.size, ORANGE);
            DrawGrid(20, 30.f);
            EndDrawing();
        }
        if(IsKeyPressed(KEY_W)){snake_head.direction.x = 0.0f; snake_head.direction.y = -4.f;}
        if(IsKeyPressed(KEY_S)){snake_head.direction.x = 0.0f; snake_head.direction.y = +4.f;}
        if(IsKeyPressed(KEY_D)){snake_head.direction.y = 0.0f; snake_head.direction.x = +4.f;}
        if(IsKeyPressed(KEY_A)){snake_head.direction.y = 0.0f; snake_head.direction.x = -4.f;}
        for(int i = 0; i != segment_count-2; i++)
        {
            if(CheckCollisionCircles(snake_head.position, 0.5f, segments[i+2]->position, 0.5f))
            {printf("You lost!!!!\n");exit(0);}
        }
        if(CheckCollisionCircles(snake_head.position, snake_head.size + 3.f, food.position, snake_head.size + 3.f))
        {
            float rand_x = (rand() % 300 + 0), rand_y = (rand() % 300 + 0);
            food.position = (Vector2){rand_x, rand_y};
            segment_count++;
        }
        snake_head.position.x += snake_head.direction.x;
        snake_head.position.y += snake_head.direction.y;
        if(segment_count != old_segment_count)
        {
            old_segment_count = segment_count;
            segments[segment_count] = malloc(sizeof(BodySegment));
        }
        segments[0]->position = snake_head.old_position;
        for(int i = 0; i != segment_count - 1; i++)
        {
            segments[i+1]->old_position = segments[i+1]->position = segments[i]->old_position;
            segments[i]->old_position = segments[i]->position;
        }
        snake_head.old_position = snake_head.position;
     }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}