#include "raylib.h"

void movePaddle(int keyPressed, Rectangle* paddle, int windowHeight, int speedY) {
  int newY = paddle->y + speedY;

  if(IsKeyDown(keyPressed) && (newY+paddle->height < windowHeight) 
    && (newY > 0)) {
    paddle->y += speedY;
  } 
}

int main(void) {
  
  Vector2 window = { 800, 450 };
  Vector2 paddleSpeed = { 0, 12 };  
  Vector2 ballSpeed = { 5, 5 };
  int ballRadius = 10;

  Vector2 ballCircle;
  ballCircle.x = (int)window.x>>1;
  ballCircle.y = (int)window.y>>1;

  Rectangle recPad1;
  recPad1.x = 50;
  recPad1.y = 175;
  recPad1.width = 25,
  recPad1.height = 100;
  
  Rectangle recPad2;
  recPad2.x = window.x - (recPad1.x+recPad1.width);
  recPad2.y = recPad1.y;
  recPad2.width = recPad1.width;
  recPad2.height = recPad1.height;
  
  InitWindow(window.x, window.y, "basic window");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);

    // Check Pad1 movement
    movePaddle(KEY_DOWN, &recPad1, window.y, paddleSpeed.y);
    movePaddle(KEY_UP,   &recPad1, window.y, paddleSpeed.y*(-1));
    
    // Check Pad2 movement
    movePaddle(KEY_S, &recPad2, window.y, paddleSpeed.y);
    movePaddle(KEY_W, &recPad2, window.y, paddleSpeed.y*(-1));
  
    // Draw all the elements
    DrawRectangleRec(recPad1, BLUE);
    DrawRectangleRec(recPad2, RED);
    DrawCircleV(ballCircle, ballRadius, RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

