#include <raylib.h>
#include "player.hpp"
#include "projectile.hpp"

int main(void) {
  
  Projectile milk = Projectile(12, 12, LoadTexture("images/milkProjectile.png"));
  Player milkman = Player(milk, LoadTexture("images/milkman.png"));

  InitWindow(1000, 800, "Milkman");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(GRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
