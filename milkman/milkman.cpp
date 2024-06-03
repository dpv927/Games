#include <chrono>
#include <raylib.h>
#include "player.hpp"
#include "sys.hpp"

using namespace Milkman;

int main(void) {

  InitWindow(1890, 1050,"Milkman");
  //SetConfigFlags(FLAG_FULLSCREEN_MODE);
  //ToggleFullscreen();
  SetTargetFPS(60);
  //105

  Window::width  = GetScreenWidth();
  Window::height = GetScreenHeight();
  Window::scaleX = (float)Window::width/BaseWidthPx;
  Window::scaleY = (float)Window::height/BaseHeightPx;
  
  Player milkman(
    (char*)"Player/milkman.png",
    Vector2{Window::width/2.0f, Window::height/2.0f}
  );

  Texture2D tex = LoadTexture("Biomes/floor2.png");

  while(!WindowShouldClose()) {
    Window::timeNow = high_resolution_clock::now();
    milkman.Move();
    milkman.Shoot();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int x = 0; x < 1800; x+=105) {
      for (int y = 0; y < 1000; y+=105) {
        DrawTexturePro(tex, Rectangle{0,0,105,105}, Rectangle{(float)x,(float)y,105,105},
      Vector2{0}, 0, WHITE);
        DrawRectangleLines(x, y, 105, 105, BLACK);
      }
    }

    milkman.Draw();
    EndDrawing();
  }
  CloseWindow();
}
