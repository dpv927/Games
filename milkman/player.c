#include <raylib.h>
#include "player.h"
#include "constants.h"

/* Player movement settings */
#define PLAYER_LERP   0.1f
#define PLAYER_SPEED  6
        
/** Player Display Settings **/
#define BODY_COLOR (Color){17,17,17,255}
#define EYES_COLOR (Color){239,239,239,255}
#define HAT1_COLOR (Color){130,90,90,255}
#define HAT2_COLOR (Color){159,98,98,255}
#define HAT3_COLOR (Color){152,120,120,255}
static float PlayerWidth  = 90;
static float PlayerHeight = 75;
static float EyeWidth  = 15;
static float EyeHeight = 15;
static float EyeOffset = 20;
static float HatHeight = 35;

void ApplyConstantsScale(float scale) {
  PlayerWidth  *= scale;
  PlayerHeight *= scale;
  EyeWidth  *= scale;
  EyeHeight *= scale;
  EyeOffset *= scale;
  HatHeight *= scale;
}

void InitializePlayer(struct Player* player) {
  // Initialize the player body
  player->body.x = (WINDOW_WIDTH-PlayerWidth)/2.0f;
  player->body.y = (WINDOW_HEIGHT-PlayerHeight)/2.0f;
  player->body.width = PlayerWidth;
  player->body.height = PlayerHeight;

  // Initialize target position: interpolation
  player->tPosx = player->body.x;
  player->tPosy = player->body.y;

  // Initialize the player's left eye
  player->leftEye.x = player->body.x+EyeOffset;
  player->leftEye.y = player->body.y+EyeOffset;
  player->leftEye.width = EyeWidth;
  player->leftEye.height = EyeHeight;

  // Initialize the player's right eye
  player->rightEye.x = player->body.x+(PlayerWidth-EyeOffset-EyeWidth);
  player->rightEye.y = player->leftEye.y;
  player->rightEye.width = EyeWidth;
  player->rightEye.height = EyeHeight;

  // Initialize the player's hat crown
  player->hat1.x = player->body.x+PlayerWidth*0.1f;
  player->hat1.y = player->body.y-HatHeight;
  player->hat1.width = PlayerWidth*0.8f;
  player->hat1.height = HatHeight;

  // Initialize the player's hat brim
  player->hat2.width = PlayerWidth*1.3f;
  player->hat2.height = HatHeight/4.0f;
  player->hat2.x = player->body.x-(PlayerWidth*0.15f);
  player->hat2.y = player->body.y-player->hat2.height;

  // Initialize the player's hat ribbon
  player->hat3.width = player->hat1.width;
  player->hat3.height = player->hat2.height;
  player->hat3.x = player->hat1.x;
  player->hat3.y = player->hat1.y+player->hat3.height;
}

void MovePlayer(struct Player* player) {
  float directionX;
  float directionY;

  // Get the user movement directions (-1,0,1)*speed
  directionX = (IsKeyDown(KEY_D)-IsKeyDown(KEY_A)) * PLAYER_SPEED;
  directionY = (IsKeyDown(KEY_S)-IsKeyDown(KEY_W)) * PLAYER_SPEED;
  player->tPosx += directionX;
  player->tPosy += directionY;

  // Initerpolate player position (smooth)
  player->body.x += PLAYER_LERP * (player->tPosx - player->body.x);
  player->body.y += PLAYER_LERP * (player->tPosy - player->body.y);

  // Update the rest of the player sprite parts
  player->leftEye.x = player->body.x+EyeOffset;
  player->leftEye.y = player->body.y+EyeOffset;
  player->rightEye.x = player->body.x+(PlayerWidth-EyeOffset-EyeWidth);
  player->rightEye.y = player->leftEye.y;
  player->hat1.x = player->body.x+PlayerWidth*0.1f;
  player->hat1.y = player->body.y-HatHeight;
  player->hat2.x = player->body.x-(PlayerWidth*0.15f);
  player->hat2.y = player->body.y-player->hat2.height;
  player->hat3.x = player->hat1.x;
  player->hat3.y = player->hat1.y+player->hat3.height;
}

void DrawPlayer(struct Player player) {
  DrawRectangleRec(player.body, BODY_COLOR);
  DrawRectangleRec(player.leftEye, EYES_COLOR);
  DrawRectangleRec(player.rightEye, EYES_COLOR);
  DrawRectangleRec(player.hat1, HAT1_COLOR);
  DrawRectangleRec(player.hat2, HAT2_COLOR);
  DrawRectangleRec(player.hat3, HAT3_COLOR);
}
