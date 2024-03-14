#include <raylib.h>
#include "player.h"
#include "constants.h"

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Milkman");
  SetTargetFPS(60);

  // Initialize players
  struct Player milkman;
  ApplyConstantsScale(0.6f);
  InitializePlayer(&milkman);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(WINDOW_COLOR);
      MovePlayer(&milkman);
      DrawPlayer(milkman);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
