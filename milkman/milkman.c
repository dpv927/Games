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
    BeginDrawing();
      ClearBackground(WINDOW_COLOR);
      DrawFPS(10,10);
      MovePlayer(&milkman);
      DrawPlayer(milkman);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
