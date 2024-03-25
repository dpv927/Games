
#include <chrono>
#include <raylib.h>
#include "player.hpp"
#include "sys.hpp"


int Sys::screenWidth;
int Sys::screenHeight;
float Sys::scaleX;
float Sys::scaleY;
sysTime Sys::timeNow;


int main(void) {

  InitWindow(0,0,"Milkman");
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();
  SetTargetFPS(60);

  Sys::screenWidth  = GetScreenWidth();
  Sys::screenHeight = GetScreenHeight();
  Sys::scaleX = (float)Sys::screenWidth/BaseWidthPx;
  Sys::scaleY = (float)Sys::screenHeight/BaseHeightPx;
  
  Player milkman((char*)"milkman.png", Vector2{Sys::screenWidth/2.0f, Sys::screenHeight/2.0f});

  while(!WindowShouldClose()) {
    Sys::timeNow = high_resolution_clock::now();
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
