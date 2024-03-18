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
  InitWindow(0,0,"Milkman");
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();
  SetTargetFPS(60);
 
  // Calculate objects scale
  scaleX = (float)GetScreenWidth()/BASEWRES;
  scaleY = (float)GetScreenHeight()/BASEHRES;
}

enum {
  DOWN,
  UP,
  LEFT,
  RIGHT,
  DIAG_LEFT,
  DIAG_RIGHT,
} direction;

int main(void) {
  ConfigureScreen();

  Texture sprites = LoadTexture(TEXPATH);
  SetTextureFilter(sprites, TEXTURE_FILTER_TRILINEAR);

  Rectangle frame = {0};
  frame.width  = (float)sprites.width/6;
  frame.height = (float)sprites.height-1;
  
  Rectangle position;
  position.x = GetScreenWidth()/2.0f;
  position.y = GetScreenHeight()/2.0f;
  position.width  = frame.width*scaleX;
  position.height = frame.height*scaleY; 

  Vector2 targetPosition;
  targetPosition.x = position.x;
  targetPosition.y = position.y;

  int moveX;
  int moveY;

  while (!WindowShouldClose()) {
    moveX = (IsKeyDown(KEY_D)-IsKeyDown(KEY_A));
    moveY = (IsKeyDown(KEY_S)-IsKeyDown(KEY_W));
    targetPosition.x += moveX * 10;
    targetPosition.y += moveY * 10;

    position.x += 0.08f * (targetPosition.x - position.x);
    position.y += 0.08f * (targetPosition.y - position.y);
    
    // Get the indicated sprite for the selected 
    // player movement.
    if(moveX==0 && moveY==0 || moveX==0 && moveY==1) 
      frame.x = DOWN;
    if(moveX == 0 && moveY == -1)
      frame.x = UP*(float)frame.width;
    if(moveX == -1 && moveY == 0)
      frame.x = LEFT*(float)frame.width;
    if(moveX == 1 && moveY == 0)
      frame.x = RIGHT*(float)frame.width;
    if(moveX == -1 && moveY != 0)
      frame.x = DIAG_LEFT*(float)frame.width;
    if(moveX == 1 && moveY != 0)
      frame.x = DIAG_RIGHT*(float)frame.width;
  
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(sprites, frame, position, ZERO, 0, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
