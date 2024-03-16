#include <raylib.h>

const int baseWidthResolution;
const int baseHeightResolution;

int main(void) {

  InitWindow(0,0,"Window Title");
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();
  
  Texture sprites = LoadTexture("milkman.png");
  SetTextureFilter(sprites, TEXTURE_FILTER_TRILINEAR);

  /* Texture frames */ 
  Vector2 position = {350,280};
  Rectangle frameRec = { 0.0f, 0.0f, (float)sprites.width/8, (float)sprites.height };
  int currentFrame = 0;
  int framesCounter = 0;
  int framesSpeed = 8;
  float scale = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    framesCounter++;

    if (framesCounter >= (60/framesSpeed)) {
      framesCounter = 0;
      currentFrame++;
      if (currentFrame > 5) currentFrame = 0;
      frameRec.x = (float)currentFrame*(float)sprites.width/4;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(sprites, frameRec, (Rectangle){0,0,frameRec.width*scale,frameRec.height*scale}, (Vector2){0}, 0, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
