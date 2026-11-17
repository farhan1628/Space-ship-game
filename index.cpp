
#include <iostream>
#include "raylib.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

// Game settings
int start_screen = 0;
int window_w = 1250;
int window_h = 810;
int disp = 0;
struct struct_stars
{
    float star_x;
    float star_y;
    float rad;
    float col;
};

// Each shot stores its position, velocity, and angle
struct Shot
{
    Vector2 position;
    Vector2 velocity;
    float angle;
};

int main()
{
    // Separate vectors for each player's bullets
    std::vector<Shot> shots;
    std::vector<Shot> shots2;

    std::vector<struct_stars> vector_stars;

    srand(time(nullptr));

    float player_one_x = rand() % 1100;
    float player_one_y = rand() % 600;
    float player_one_ang = rand() % 360;

    float player_two_x = rand() % 1100;
    float player_two_y = rand() % 600;
    float player_two_ang = rand() % 360;

    while (player_one_x < 30)
        player_one_x = rand() % 1100;

    while (player_one_y < 30)
        player_one_y = rand() % 600;

    while (player_two_x < 30)
        player_two_x = rand() % 1100;

    while (player_two_y < 30)
        player_two_y = rand() % 600;

    Vector2 player_one_position = {player_one_x, player_one_y};
    Vector2 player_two_position = {player_two_x, player_two_y};

    float player_one_speed = 250.0f;
    float player_one_turn_speed = 150.0f;

    float player_two_speed = 250.0f;
    float player_two_turn_speed = 150.0f;

    // Generate stars
    for (int i = 0; i < 61; i++)
    {
        float starX = rand() % 1240;
        float starY = rand() % 800;
        float sz = rand() % 4;

        vector_stars.push_back({starX, starY, sz, 0});
    }

    // Initialize window and textures
    InitWindow(window_w, window_h, "Game");

    Texture2D ship = LoadTexture("ship.png");
    Texture2D ship2 = LoadTexture("ship2.png");
    Texture2D exp = LoadTexture("explosion.png");
    Texture2D shot = LoadTexture("shot.png");
    Texture2D shot2 = LoadTexture("shot2.png");

    if (shot.id == 0)
        TraceLog(LOG_ERROR, "Failed to load shot.png");

    if (shot2.id == 0)
        TraceLog(LOG_ERROR, "Failed to load shot2.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // =========================
        // START SCREEN
        // =========================
        if (start_screen == 0)
        {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Press Space to Play",
                     370, 420, 55, WHITE);

            EndDrawing();

            if (IsKeyPressed(KEY_SPACE))
                start_screen = 1;
        }

        // =========================
        // PLAYER SELECTION SCREEN
        // =========================
        else if (start_screen == 1)
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
            DrawText("ARROWS", 470, 320, 50, WHITE);
            DrawText("W,A,S,D", 805, 320, 50, WHITE);

            DrawText("Shoot:", 30, 400, 50, WHITE);
            DrawText("Right shift", 470, 400, 50, WHITE);
            DrawText("Left shift", 805, 400, 50, WHITE);

            DrawText("Press Enter to Start",
                     200, 500, 80, YELLOW);

            EndDrawing();

            if (IsKeyPressed(KEY_ENTER))
                start_screen = 2;
        }

        // =========================
        // MAIN GAME
        // =========================
        else if (start_screen == 2)
        {
            float dt = GetFrameTime();

            // -------------------------
            // PLAYER 2 MOVEMENT (WASD)
            // -------------------------
            if (IsKeyDown(KEY_D))
                player_two_ang += player_two_turn_speed * dt;

            if (IsKeyDown(KEY_A))
                player_two_ang -= player_two_turn_speed * dt;

            float player_two_radian = player_two_ang * DEG2RAD;

            if (IsKeyDown(KEY_W))
            {
                player_two_position.x +=
                    sinf(player_two_radian) * player_two_speed * dt;

                player_two_position.y -=
                    cosf(player_two_radian) * player_two_speed * dt;
            }

            if (IsKeyDown(KEY_S))
            {
                player_two_position.x -=
                    sinf(player_two_radian) * player_two_speed * dt;

                player_two_position.y +=
                    cosf(player_two_radian) * player_two_speed * dt;
            }

            // Keep Player 2 inside the window
            if (player_two_position.x > window_w - 38)
                player_two_position.x = window_w - 38;

            if (player_two_position.x < 38)
                player_two_position.x = 38;

            if (player_two_position.y < 38)
                player_two_position.y = 38;

            if (player_two_position.y > window_h - 38)
                player_two_position.y = window_h - 38;

            // -------------------------
            // PLAYER 1 MOVEMENT (ARROWS)
            // -------------------------
            if (IsKeyDown(KEY_RIGHT))
                player_one_ang += player_one_turn_speed * dt;

            if (IsKeyDown(KEY_LEFT))
                player_one_ang -= player_one_turn_speed * dt;

            float player_one_radian = player_one_ang * DEG2RAD;

            if (IsKeyDown(KEY_UP))
            {
                player_one_position.x +=
                    sinf(player_one_radian) * player_one_speed * dt;

                player_one_position.y -=
                    cosf(player_one_radian) * player_one_speed * dt;
            }

            if (IsKeyDown(KEY_DOWN))
            {
                player_one_position.x -=
                    sinf(player_one_radian) * player_one_speed * dt;

                player_one_position.y +=
                    cosf(player_one_radian) * player_one_speed * dt;
            }

            // Keep Player 1 inside the window
            if (player_one_position.x > window_w - 38)
                player_one_position.x = window_w - 38;

            if (player_one_position.x < 38)
                player_one_position.x = 38;

            if (player_one_position.y < 38)
                player_one_position.y = 38;

            if (player_one_position.y > window_h - 38)
                player_one_position.y = window_h - 38;

            // =========================
            // SHOOTING
            // =========================
            float bullet_speed = 750.0f;

            // Player 1 fires with RIGHT SHIFT
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

            // Player 2 fires with LEFT SHIFT
            if (IsKeyPressed(KEY_LEFT_SHIFT))
            {
                float rad = player_two_ang * DEG2RAD;

                Vector2 direction = {
                    sinf(rad),
                    -cosf(rad)};

                Vector2 spawn = {
                    player_two_position.x + direction.x * 65,
                    player_two_position.y + direction.y * 65};

                shots2.push_back({spawn,
                                  {direction.x * bullet_speed,
                                   direction.y * bullet_speed},
                                  player_two_ang});
            }

            // =========================
            // MOVE AND REMOVE PLAYER 1 BULLETS
            // =========================
            for (int i = (int)shots.size() - 1; i >= 0; i--)
            {
                shots[i].position.x += shots[i].velocity.x * dt;
                shots[i].position.y += shots[i].velocity.y * dt;

                if (shots[i].position.x < -100 ||
                    shots[i].position.x > window_w + 100 ||
                    shots[i].position.y < -100 ||
                    shots[i].position.y > window_h + 100)
                {
                    shots.erase(shots.begin() + i);
                }
            }

            // =========================
            // MOVE AND REMOVE PLAYER 2 BULLETS
            // =========================
            for (int i = (int)shots2.size() - 1; i >= 0; i--)
            {
                shots2[i].position.x += shots2[i].velocity.x * dt;
                shots2[i].position.y += shots2[i].velocity.y * dt;

                if (shots2[i].position.x < -100 ||
                    shots2[i].position.x > window_w + 100 ||
                    shots2[i].position.y < -100 ||
                    shots2[i].position.y > window_h + 100)
                {
                    shots2.erase(shots2.begin() + i);
                }
            }

            // =========================
            // DRAW EVERYTHING
            // =========================
            for (int i = 0; i < shots.size(); i++)
            {
                if (CheckCollisionCircles({shots[i].position.x, shots[i].position.y}, 30, {player_two_position.x, player_two_position.y}, 30))
                {
                    for (int r = 0; r < 100; r++)
                    {
                        BeginDrawing();
                        DrawTextureEx(exp, {player_two_position.x - 140, player_two_position.y - 180}, 0, 0.3f, WHITE);

                        EndDrawing();
                    }
                    shots[i].position.x = 1700;
                    start_screen = 4;
                }
            }
            for (int i = 0; i < shots2.size(); i++)
            {
                if (CheckCollisionCircles({shots2[i].position.x, shots2[i].position.y}, 30, {player_one_position.x, player_one_position.y}, 30))
                {
                    // for (int r = 0; r < 100; r++)
                    // {
                    BeginDrawing();
                    DrawTextureEx(exp, {player_one_position.x - 140, player_one_position.y - 180}, 0, 0.3f, WHITE);

                    EndDrawing();
                    // }
                    shots2[i].position.x = 1700;
                    start_screen = 5;
                }
            }

            BeginDrawing();
            ClearBackground(BLACK);

            // Draw stars
            for (int i = 0; i < (int)vector_stars.size(); i++)
            {
                DrawCircle(
                    (int)vector_stars[i].star_x,
                    (int)vector_stars[i].star_y,
                    vector_stars[i].rad,
                    WHITE);
            }

            // Draw Player 1
            DrawTexturePro(
                ship,
                {0, 0, (float)ship.width, (float)ship.height},
                {player_one_position.x, player_one_position.y, 100, 100},
                {40, 40},
                player_one_ang,
                WHITE);

            // Draw Player 2
            DrawTexturePro(
                ship2,
                {0, 0, (float)ship2.width, (float)ship2.height},
                {player_two_position.x, player_two_position.y, 120, 120},
                {40, 40},
                player_two_ang,
                WHITE);

            // Draw Player 1 bullets using shot.png
            for (int i = 0; i < (int)shots.size(); i++)
            {
                DrawTexturePro(
                    shot,
                    {0, 0, (float)shot.width, (float)shot.height},
                    {shots[i].position.x,
                     shots[i].position.y,
                     shot.width * 0.3f,
                     shot.height * 0.3f},
                    {shot.width * 0.15f,
                     shot.height * 0.15f},
                    shots[i].angle + 180.0f,
                    WHITE);
            }

            // Draw Player 2 bullets using shot2.png
            for (int i = 0; i < (int)shots2.size(); i++)
            {
                DrawTexturePro(
                    shot2,
                    {0, 0, (float)shot2.width, (float)shot2.height},
                    {shots2[i].position.x,
                     shots2[i].position.y,
                     shot2.width * 0.3f,
                     shot2.height * 0.3f},
                    {shot2.width * 0.15f,
                     shot2.height * 0.15f},
                    shots2[i].angle + 90.0f,
                    WHITE);
            }

            EndDrawing();
        }
        else if (start_screen == 4)
        {
            BeginDrawing();
            DrawRectangle(370, 200, 600, 300, WHITE);
            DrawText("Player one wins!", 480, 230, 40, BLACK);
            DrawText("Press Q to play again.", 440, 340, 35, BLACK);
            EndDrawing();
            if (IsKeyPressed(KEY_Q))
            {
                start_screen = 0;
            }
        }
        else if (start_screen == 5)
        {
            BeginDrawing();
            DrawRectangle(370, 200, 600, 300, WHITE);
            DrawText("Player two wins!", 480, 230, 40, BLACK);
            DrawText("Press Q to play again.", 440, 340, 35, BLACK);
            EndDrawing();
            if (IsKeyPressed(KEY_Q))
            {
                start_screen = 0;
            }
        }
    }

    // Clean up textures and window
    UnloadTexture(ship);
    UnloadTexture(ship2);
    UnloadTexture(shot);
    UnloadTexture(shot2);

    CloseWindow();

    return 0;
}

// & "C:\msys64\ucrt64\bin\g++.exe" .\index.cpp -o .\index.exe -lraylib -lopengl32 -lgdi32 -lwinmm