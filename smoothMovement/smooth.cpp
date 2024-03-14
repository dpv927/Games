
#include <raylib.h>
#define Lerp 0.06f
#define Speed 10


struct Player {
  float x;
  float y;
  int speed;

  Player(): x(0), y(0), speed(0) {};
  Player(float px, float py, int speed);
};


int main(void) {

    InitWindow(1000, 800, "basic window");
    SetTargetFPS(60);

    Player pepe;


    Vector2 pos = {100, 100};
    Vector2 targetPos = pos;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 input;
        input.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * Speed;
        input.y = (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * Speed;

        // Update player position
        targetPos.x += input.x;
        targetPos.y += input.y;

        // Interpolate position for smooth movement
        pos.x = pos.x + Lerp * (targetPos.x-pos.x);
        pos.y = pos.y + Lerp * (targetPos.y-pos.y);

        DrawRectangle(pos.x, pos.y, 100, 100, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
