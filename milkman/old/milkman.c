#include <raylib.h>
#include "player.h"
#include "constants.h"

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Milkman");
  SetTargetFPS(60);

  // Initialize players
  struct Player milkman;
  ApplyPropiertiesScale(0.8f);
  InitializePlayer(&milkman);

  while (!WindowShouldClose()) {
    MovePlayer(&milkman);
    BeginDrawing();
      ClearBackground(WINDOW_COLOR);
      DrawPlayer(milkman);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
