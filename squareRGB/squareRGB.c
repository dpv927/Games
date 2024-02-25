#include <raylib.h>
#include <stdio.h>

const int WindowWidth  = 1000;
const int WindowHeight = 600;
const float SquareBorder = 3.0f;
const float SquareWidth  = 90.0f;
const float SquareInitX  = (WindowWidth/2.0f)  - (SquareWidth/2.0f);
const float SquareInitY  = (WindowHeight/2.0f) - (SquareWidth/2.0f);
const float InnerSquareWith = SquareWidth - (SquareBorder*2.0f);

void balanceRGB(Color* color) {
  unsigned char r = color->r;
  unsigned char g = color->g;
  unsigned char b = color->b;

  if(r == 255 && g < r) {
    if(b > 0) b--;
    g++;
    goto assign;
  }

  if(g == 255 && b < g) {
    b++; r--; 
    goto assign;
  }
  
  if(b == 255 && r < b) {
    r++; g--;
  }

  assign:
  color->r = r;
  color->g = g;
  color->b = b;
}

void manageSquareColisions(Rectangle square, Vector2* squareSpeed, Rectangle window) {
  if(square.x+square.width >= window.x || square.x <= 0)
    squareSpeed->x *= -1;
  if(square.y+square.width >= window.y || square.y <= 0)
    squareSpeed->y *= -1;
}

void moveRectangle(Rectangle* square, Vector2 squareSpeed, Rectangle* innerSquare) {
  square->x += squareSpeed.x;
  square->y += squareSpeed.y;
  innerSquare->x = square->x + SquareBorder;
  innerSquare->y = square->y + SquareBorder;
}

int main(void) {

  InitWindow(WindowWidth, WindowHeight, "basic window");
  ClearBackground(RAYWHITE);
  SetTargetFPS(60);

  Color innerSquareColor = {255, 0, 0, 255};
  Vector2 squareSpeed = { 7, 7 };
  
  Rectangle square = { 
    .x = SquareInitX,
    .y = SquareInitY,
    .width  = SquareWidth,
    .height = SquareWidth 
  };

  Rectangle innerSquare = {
    .x = square.x + SquareBorder,
    .y = square.y + SquareBorder,
    .width = InnerSquareWith,
    .height= InnerSquareWith, 
  };
  
  while(!WindowShouldClose()) {
    BeginDrawing();
    balanceRGB(&innerSquareColor);

    manageSquareColisions(square, &squareSpeed, (Rectangle){WindowWidth, WindowHeight});
    moveRectangle(&square, squareSpeed, &innerSquare);
    DrawRectangleRec(square, BLACK);
    DrawRectangleRec(innerSquare, innerSquareColor);
    
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
