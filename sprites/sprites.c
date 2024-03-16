#include <raylib.h>

// 768x128

int main(void) {

  InitWindow(800, 800, "Window Title");
  
  Texture2D sprites = LoadTexture("scarfy.png");
  Vector2 position = {350,280};
  Rectangle frameRec = { 0.0f, 0.0f, (float)sprites.width/6, (float)sprites.height };
  int currentFrame = 0;
  int framesCounter = 0;
  int framesSpeed = 8;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    framesCounter++;

    if (framesCounter >= (60/framesSpeed)) {
      framesCounter = 0;
      currentFrame++;
      if (currentFrame > 5) currentFrame = 0;
      frameRec.x = (float)currentFrame*(float)sprites.width/6;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureRec(sprites, frameRec, position, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
