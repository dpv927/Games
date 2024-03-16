#include <raylib.h>
#define TEXPATH "milkman.png"
#define ZERO (Vector2){0}

/* Base screen resoltion 
 *   Using 1366x768px */
#define BASEWRES 1366;
#define BASEHRES 768;
float scaleX = 1.0f;
float scaleY = 1.0f;

void ConfigureScreen(void) {
  InitWindow(0,0,"Window Title");
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();
  SetTargetFPS(60);
 
  // Calculate objects scale
  scaleX = (float)GetScreenWidth()/BASEWRES;
  scaleY = (float)GetScreenHeight()/BASEHRES;
}

int main(void) {
  ConfigureScreen();

  Texture sprites = LoadTexture(TEXPATH);
  SetTextureFilter(sprites, TEXTURE_FILTER_TRILINEAR);

  int currentFrame = 0;
  int framesCounter = 0;
  int framesSpeed = 8;
  
  Rectangle frame = {0};
  frame.width  = (float)sprites.width/8;
  frame.height = (float)sprites.height;
  
  Rectangle position = {0};
  position.width  = frame.width*scaleX;
  position.height = frame.height*scaleY; 

  while (!WindowShouldClose()) {
    framesCounter++;

    if (framesCounter >= (60/framesSpeed)) {
      framesCounter = 0;
      currentFrame++;
      if (currentFrame > 5) currentFrame = 0;
      frame.x = (float)currentFrame*(float)sprites.width/4;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(sprites, frame, position, ZERO, 0, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
