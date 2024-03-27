#include "raylib.h"

int main(void) {

  InitWindow(800, 800, "raylib [core] example - basic window");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i<8; i++) {
      for (int j = 0; j<8; j++) {
        DrawRectangle(10*j, 10*i, 10, 10, i==j? WHITE : BLACK);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
