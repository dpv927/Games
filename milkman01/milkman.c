#include <raylib.h>

typedef struct PlayerSprite PlayerSprite;
struct PlayerSprite {
  Rectangle rightEye;
  Rectangle leftEye;
  Rectangle body;
  Rectangle hat1;
  Rectangle hat2;
  Rectangle hat3;
} player;

/** General Enviroment Settings **/
#define WINDOW_COLOR (Color){230,224,224,0}
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800
#define CAMERA_SPEED  5

/** Player Display Settings **/
#define PLAYER_WIDTH  90
#define PLAYER_HEIGTH 75
#define EYE_WIDTH  15
#define EYE_HEIGHT 15 
#define EYE_OFFSET 20
#define HAT_HEIGHT 35
#define BODY_COLOR (Color){17,17,17,255}
#define EYES_COLOR (Color){239,239,239,255}
#define HAT1_COLOR (Color){130,90,90,255}
#define HAT2_COLOR (Color){159,98,98,255}
#define HAT3_COLOR (Color){152,120,120,255}

int main(void) {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Basic 2D Game");
  SetTargetFPS(60);

  Camera2D camera;
  int motionX, motionY;
  int operator;

  // We are not going to load the character sprite from an image,
  // we are going to draw it by hand with rectangles. Its better.
  // Isn't it?
  // 
  // Initialize the player body
  player.body.x = (WINDOW_WIDTH-PLAYER_WIDTH)/2.0f;
  player.body.y = (WINDOW_HEIGHT-PLAYER_HEIGTH)/2.0f;
  player.body.width = PLAYER_WIDTH;
  player.body.height = PLAYER_HEIGTH;

  // Initialize the player's left eye
  player.leftEye.x = player.body.x+EYE_OFFSET;
  player.leftEye.y = player.body.y+EYE_OFFSET;
  player.leftEye.width = EYE_WIDTH;
  player.leftEye.height = EYE_HEIGHT;

  // Initialize the player's right eye
  player.rightEye.x = player.body.x+(PLAYER_WIDTH-EYE_OFFSET-EYE_WIDTH);
  player.rightEye.y = player.leftEye.y;
  player.rightEye.width = EYE_WIDTH;
  player.rightEye.height = EYE_HEIGHT;

  // Initialize the player's hat crown
  player.hat1.x = player.body.x + PLAYER_WIDTH*0.1f;
  player.hat1.y = player.body.y - HAT_HEIGHT;
  player.hat1.width = PLAYER_WIDTH*0.8f;
  player.hat1.height = HAT_HEIGHT;

  // Initialize the player's hat brim
  player.hat2.width = PLAYER_WIDTH*1.3f;
  player.hat2.height = HAT_HEIGHT/4.0f;
  player.hat2.x = player.body.x - (PLAYER_WIDTH*0.15);
  player.hat2.y = player.body.y - player.hat2.height;

  // Initialize the player's hat ribbon
  player.hat3.width = player.hat1.width;
  player.hat3.height = player.hat2.height;
  player.hat3.x = player.hat1.x;
  player.hat3.y = player.hat1.y + player.hat3.height;

  // Initialize the game camera
  camera.zoom = 1.0f;
  camera.offset = (Vector2){0};
  camera.rotation = 0;
  camera.target = (Vector2){0,0};

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(WINDOW_COLOR);

    // Check player motion
    motionX = motionY = 0;
    operator = 0;
    
    if(IsKeyDown(KEY_W)){
      motionY = 1;
      operator = -1;
    } else if(IsKeyDown(KEY_S)){
      motionY = 1;
      operator = 1;
    } else if(IsKeyDown(KEY_A)){
      motionX = 1;
      operator = -1;
    } else if(IsKeyDown(KEY_D)){
      motionX = 1;
      operator = 1;
    }

    // Update the player and camera position
    operator *= CAMERA_SPEED;
    if(motionX) {  
      // Move player horizontally
      player.body.x += operator;
      player.rightEye.x += operator;
      player.leftEye.x += operator;
      player.hat1.x += operator;
      player.hat2.x += operator;
      player.hat3.x += operator;
      // Move the camera
      camera.target.x += operator;

    } else if(motionY) { 
      // Move player vertically
      player.body.y += operator;
      player.rightEye.y += operator;
      player.leftEye.y += operator;
      player.hat1.y += operator;
      player.hat2.y += operator;
      player.hat3.y += operator;
      // Move the camera
      camera.target.y += operator;
    }
    
    // Draw the player
    DrawRectangleRec(player.body, BODY_COLOR);
    DrawRectangleRec(player.leftEye, EYES_COLOR);
    DrawRectangleRec(player.rightEye, EYES_COLOR);
    DrawRectangleRec(player.hat1, HAT1_COLOR);
    DrawRectangleRec(player.hat2, HAT2_COLOR);
    DrawRectangleRec(player.hat3, HAT3_COLOR);

    DrawRectangle(800, 200, 800, 800, GRAY);
    
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
