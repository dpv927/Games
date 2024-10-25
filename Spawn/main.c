#include <math.h>
#include <raylib.h>

int window_width = 1000;
int window_height = 1000;

int main(void) {

  Vector2 triangle[] = { 
    { 100, -100 },
    { 0, -200 },
    { -100, -100 }
  };

  InitWindow(window_width, window_height, "Window Title");
  SetTargetFPS(20);

  for(int i = 0; i < 3; ++i) {
    triangle[i].x += window_width  >> 1;
    triangle[i].y += window_height >> 1;
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTriangle(triangle[0], triangle[1], triangle[2], BLACK);
    DrawCircleV(triangle[0], 10, PURPLE);
    DrawCircleV(triangle[1], 10, PURPLE);
    DrawCircleV(triangle[2], 10, PURPLE);
    DrawCircle(500, 500, 10, PURPLE);
    EndDrawing();

    for(int i = 0; i < 3; ++i) {
      float x = triangle[i].x - 500;
      float y = triangle[i].y - 500;

      triangle[i].x = (x * cosf(0.2) - y * sinf(0.2)) + 500;
      triangle[i].y = (y * cosf(0.2) + x * sinf(0.2)) + 500;
    }
  }

  CloseWindow();
  return 0;
}
