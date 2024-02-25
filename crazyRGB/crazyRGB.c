#include <raylib.h>
#include <stdio.h>
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

int main(void) {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "basic window");
  SetTargetFPS(60);

  int r = 255, rOperand = 0;
  int g = 0,   gOperand = 0;
  int b = 0,   bOperand = 0;

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground((Color){r, g, b, 255});

    if(r == 255 && g < r) {
      if(b > 0) b--;
      g++; goto draw;
    }
    
    if(g == 255 && b < g) {
      b++; 
      r--;
      goto draw;
    }
    
    if(b == 255 && r < b) {
      r++;
      g--;
    }

    draw:
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
