#include <chrono>
#include <raylib.h>
#include "player.hpp"
#include "sys.hpp"

using namespace Milkman;

int main(void) {

  InitWindow(1890, 1050, "Milkman");
  SetTargetFPS(60);

  Window::width  = GetScreenWidth();
  Window::height = GetScreenHeight();
  Window::scaleX = (float)Window::width/BaseWidthPx;
  Window::scaleY = (float)Window::height/BaseHeightPx;
  
  Player milkman(
    (char*)"Player/milkman.png",
    Vector2{Window::width/2.0f, Window::height/2.0f}
  );

  while(!WindowShouldClose()) {
    Window::timeNow = high_resolution_clock::now();
    milkman.Move();
    milkman.Shoot();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    milkman.Draw();
    EndDrawing();
  }
  CloseWindow();
}
