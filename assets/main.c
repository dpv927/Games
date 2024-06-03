#include <raylib.h>

int main(void) {

  InitWindow(1920, 1080, "Window Title");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
