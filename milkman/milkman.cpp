#include <chrono>
#include <raylib.h>
#include "player.hpp"
#include "sys.hpp"

using namespace Milkman;

int main(void) {

  InitWindow(0,0,"Milkman");
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();
  SetTargetFPS(60);

  Window::width  = GetScreenWidth();
  Window::height = GetScreenHeight();
  Window::scaleX = (float)Window::width/BaseWidthPx;
  Window::scaleY = (float)Window::height/BaseHeightPx;
  
  Player milkman(
    (char*)"milkman.png",
    Vector2{Window::width/2.0f, Window::height/2.0f}
  );

  while(!WindowShouldClose()) {
    Window::timeNow = high_resolution_clock::now();
    milkman.Move();
    milkman.Shoot();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);
    milkman.Draw();
    EndDrawing();
  }

  CloseWindow();
}
