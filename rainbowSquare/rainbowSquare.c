#include <raylib.h>
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 400

int main(void) {
  

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "basic window");
  SetTargetFPS(120);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);

      

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
