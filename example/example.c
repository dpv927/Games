#include <raylib.h>

int main(void) {

  InitWindow(800, 800, "Window Title");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
