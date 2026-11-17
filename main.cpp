#include <iostream>
#include "raylib.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

int start_screen = 0;
int window_w = 1250;
int window_h = 810;
struct struct_stars
{
    float star_x;
    float star_y;
    float rad;
    float col;
};
float player_one_old_x;
float player_one_old_y;

struct Shot
{
    Vector2 position;
    Vector2 velocity;
    float angle;
};
int main()
{
    struct_stars sh;
    std::vector<Shot> shots;
    std::vector<struct_stars> vector_stars = {};
    srand(time(nullptr));
    float player_one_x = rand() % 1100;
    float player_one_y = rand() % 600;
    float player_one_ang = rand() % 360;
    float player_two_x = rand() % 1100;
    float player_two_y = rand() % 600;
    float player_two_ang = rand() % 360;
    Vector2 player_one_position = {player_one_x, player_one_y};
    float player_one_speed = 250.0f;
    float player_one_turn_speed = 150.0f;
    Vector2 player_two_position = {player_two_x, player_two_y};
    float player_two_speed = 250.0f;
    float player_two_turn_speed = 150.0f;
    while (player_one_x < 30)
    {
        player_one_x = rand() % 1100;
    }
    while (player_one_y < 30)
    {
        player_one_y = rand() % 1100;
    }
    while (player_one_x < 30)
    {
        player_two_x = rand() % 1100;
    }
    while (player_one_y < 30)
    {
        player_two_y = rand() % 1100;
    }
    for (int i = 0; i < 61; i++)
    {
        float starX = rand() % 1240;
        float starY = rand() % 800;
        float sz = rand() % 4;
        vector_stars.push_back({starX, starY, sz});
    };

    InitWindow(window_w, window_h, "Game");
    Texture2D ship = LoadTexture("ship.png");
    Texture2D ship2 = LoadTexture("ship2.png");
    Texture2D shot = LoadTexture("shot.png");
    while (!WindowShouldClose())
    {
        if (start_screen == 0)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Press Space to Play", 370, 420, 55, WHITE);

            EndDrawing();
            if (IsKeyPressed(KEY_SPACE))
            {
                start_screen = 1;
            }
        }
        if (start_screen == 1)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Player:", 30, 60, 50, WHITE);
            DrawText("Player 1", 470, 60, 50, WHITE);
            DrawText("Player 2", 805, 60, 50, WHITE);
            DrawText("Ship:", 30, 190, 50, WHITE);
            DrawTextureEx(ship, {470, 150}, 0, 0.1f, WHITE);
            DrawTextureEx(ship2, {815, 120}, 0, 0.24f, WHITE);
            DrawText("Controls:", 30, 320, 50, WHITE);
            DrawText("W,A,S,D", 470, 320, 50, WHITE);
            DrawText("ARROWS", 805, 320, 50, WHITE);
            DrawText("Press Enter to Start", 200, 500, 80, YELLOW);
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER))
            {
                start_screen = 2;
            }
        }
        if (start_screen == 2)
        {
            if (IsKeyDown(KEY_D))
            {
                player_two_ang += player_two_turn_speed * GetFrameTime();
            }

            if (IsKeyDown(KEY_A))
            {
                player_two_ang -= player_two_turn_speed * GetFrameTime();
            }
            float player_two_radian = player_two_ang * DEG2RAD;
            if (IsKeyDown(KEY_W))
            {
                player_two_position.x += sinf(player_two_radian) * player_two_speed * GetFrameTime();
                player_two_position.y -= cosf(player_two_radian) * player_two_speed * GetFrameTime();
                if (player_two_position.x > window_w - 38)
                {
                    player_two_position.x = window_w - 38;
                }
                if (player_two_position.x < 38)
                {
                    player_two_position.x = 38;
                }
                if (player_two_position.y < 38)
                {
                    player_two_position.y = 38;
                }
                if (player_two_position.y > 772)
                {
                    player_two_position.y = 772;
                }
            }
            if (IsKeyDown(KEY_S))
            {
                player_two_position.x -= sinf(player_two_radian) * player_two_speed * GetFrameTime();
                player_two_position.y += cosf(player_two_radian) * player_two_speed * GetFrameTime();
                if (player_two_position.x > window_w - 51)
                {
                    player_two_position.x = window_w - 51;
                }
                if (player_two_position.x < 51)
                {
                    player_two_position.x = 51;
                }
                if (player_two_position.y < 51)
                {
                    player_two_position.y = 51;
                }
                if (player_two_position.y > 759)
                {
                    player_two_position.y = 759;
                }
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                player_one_ang += player_one_turn_speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_LEFT))
            {
                player_one_ang -= player_one_turn_speed * GetFrameTime();
            }
            float player_one_radian = player_one_ang * DEG2RAD;
            if (IsKeyDown(KEY_UP))
            {

                player_one_position.x += sinf(player_one_radian) * player_one_speed * GetFrameTime();
                player_one_position.y -= cosf(player_one_radian) * player_one_speed * GetFrameTime();

                if (player_one_position.x > window_w - 38)
                {
                    player_one_position.x = window_w - 38;
                }
                if (player_one_position.x < 38)
                {
                    player_one_position.x = 38;
                }
                if (player_one_position.y < 38)
                {
                    player_one_position.y = 38;
                }
                if (player_one_position.y > 772)
                {
                    player_one_position.y = 772;
                }
            }
            if (IsKeyDown(KEY_DOWN))
            {

                player_one_position.x -= sinf(player_one_radian) * player_one_speed * GetFrameTime();
                player_one_position.y += cosf(player_one_radian) * player_one_speed * GetFrameTime();
                if (player_one_position.x > window_w - 51)
                {
                    player_one_position.x = window_w - 51;
                }
                if (player_one_position.x < 51)
                {
                    player_one_position.x = 51;
                }
                if (player_one_position.y < 51)
                {
                    player_one_position.y = 51;
                }
                if (player_one_position.y > 759)
                {
                    player_one_position.y = 759;
                }
            }
            float dt = GetFrameTime();
            float bullet_speed = 780.0f;

            // Player 1: Right Shift
            if (IsKeyPressed(KEY_RIGHT_SHIFT))
            {
                float rad = player_one_ang * DEG2RAD;

                Vector2 direction = {
                    sinf(rad),
                    -cosf(rad)};

                Vector2 spawn = {
                    player_one_position.x + direction.x * 55,
                    player_one_position.y + direction.y * 55};

                shots.push_back({spawn,
                                 {direction.x * bullet_speed,
                                  direction.y * bullet_speed},
                                 player_one_ang});
            }

            // Player 2: Left Shift
            if (IsKeyPressed(KEY_LEFT_SHIFT))
            {
                float rad = player_two_ang * DEG2RAD;

                Vector2 direction = {
                    sinf(rad),
                    -cosf(rad)};

                Vector2 spawn = {
                    player_two_position.x + direction.x * 65,
                    player_two_position.y + direction.y * 65};

                shots.push_back({spawn,
                                 {direction.x * bullet_speed,
                                  direction.y * bullet_speed},
                                 player_two_ang});
            }
            for (int i = (int)shots.size() - 1; i >= 0; i--)
            {
                shots[i].position.x += shots[i].velocity.x * dt;
                shots[i].position.y += shots[i].velocity.y * dt;

                // Remove shots that leave the screen
                if (shots[i].position.x < -100 ||
                    shots[i].position.x > window_w + 100 ||
                    shots[i].position.y < -100 ||
                    shots[i].position.y > window_h + 100)
                {
                    shots.erase(shots.begin() + i);
                }
            }
            // destruction code!
            for (int s = 0; s < shots.size(); s++)
            {
                if (CheckCollisionCircles({shots[s].position.x, shots[s].position.y}, 30, {player_one_position.x, player_one_position.y}, 30))
                {
                    BeginDrawing();
                    DrawCircle(player_one_position.x, player_one_position.y, 60, BLUE);
                    EndDrawing();
                }
            }
            // destruction code ends.....pew-pew!
            BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < vector_stars.size(); i++)
            {

                DrawCircle(vector_stars[i].star_x, vector_stars[i].star_y, vector_stars[i].rad, WHITE);
            }
            DrawTexturePro(
                ship,
                {0, 0, (float)ship.width, (float)ship.height},
                {player_one_position.x, player_one_position.y, 100, 100},
                {40, 40},
                player_one_ang,
                WHITE);
            DrawTexturePro(
                ship2,
                {0, 0, (float)ship2.width, (float)ship2.height},
                {player_two_position.x, player_two_position.y, 120, 120},
                {40, 40},
                player_two_ang,
                WHITE);

            for (int i = 0; i < (int)shots.size(); i++)
            {
                DrawTexturePro(
                    shot,
                    {0, 0, (float)shot.width, (float)shot.height},
                    {shots[i].position.x,
                     shots[i].position.y,
                     shot.width * 0.2f,
                     shot.height * 0.2f},
                    {shot.width * 0.15f,
                     shot.height * 0.15f},
                    shots[i].angle + 180.0f,
                    WHITE);
            }
            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}
