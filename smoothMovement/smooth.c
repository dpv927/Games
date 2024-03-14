#include <raylib.h>
#define Lerp 0.06f
#define Speed 10

int main(void) {

  InitWindow(1000, 800, "basic window");
  SetTargetFPS(60);

  Vector2 input;     // Keyboard input
  Vector2 pPosition; // Player position
  Vector2 tPosition; // Target player position

  pPosition.x = 100;
  pPosition.y = 100;
  tPosition = pPosition;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Vector2 input;
    input.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * Speed;
    input.y = (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * Speed;
  
    // Update player position
    tPosition.x += input.x;
    tPosition.y += input.y;

    // Interpolate position for smooth movement
    pPosition.x = pPosition.x + Lerp * (tPosition.x-pPosition.x);
    pPosition.y = pPosition.y + Lerp * (tPosition.y-pPosition.y);

    DrawRectangle(pPosition.x, pPosition.y, 100, 100, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
