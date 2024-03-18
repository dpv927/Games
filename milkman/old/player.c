#include <raylib.h>
#include "player.h"
#include "constants.h"

static float PlayerWidth  = 90;
static float PlayerHeight = 75;
static float EyeWidth  = 15;
static float EyeHeight = 15;
static float EyeOffset = 20;
static float HatHeight = 35;
static float Hat1Offset = 90*0.1f;
static float Hat2Offset = 90*0.15f;

void ApplyPropiertiesScale(float scale) {
  PlayerWidth  *= scale;
  PlayerHeight *= scale;
  EyeWidth  *= scale;
  EyeHeight *= scale;
  EyeOffset *= scale;
  HatHeight *= scale;
  Hat1Offset *= scale;
  Hat2Offset *= scale;
}

void InitializePlayer(struct Player* player) {
  // Initialize the player body
  // The default sprite is IDLE_FRONT,
  // so we can define the behavior for that
  // sprite
  player->animation = IDLE_FRONT;
  player->body.x = (WINDOW_WIDTH-PlayerWidth)/2.0f;
  player->body.y = (WINDOW_HEIGHT-PlayerHeight)/2.0f;
  player->body.width = PlayerWidth;
  player->body.height = PlayerHeight;

  player->tPosx = player->body.x;
  player->tPosy = player->body.y;
  player->leftEye.width = EyeWidth;
  player->leftEye.height = EyeHeight;
  player->rightEye.width = EyeWidth;
  player->rightEye.height = EyeHeight;
  player->hat1.width = PlayerWidth*0.8f;
  player->hat1.height = HatHeight;
  player->hat2.width = PlayerWidth*1.3f;
  player->hat2.height = HatHeight/4.0f;
  player->hat3.width = player->hat1.width;
  player->hat3.height = player->hat2.height;
  ApplyPlayerPosition(player);
}

void ApplyPlayerPosition(struct Player* player) {
  // Knowing where the body is located, now we
  // can draw the rest of the sprite
  Rectangle body = player->body;
  Rectangle leftEye = player->leftEye;
  Rectangle rightEye = player->rightEye;
  Rectangle hat1 = player->hat1;
  Rectangle hat2 = player->hat2;
  Rectangle hat3 = player->hat3;

  // Set (x,y) for the parts
  leftEye.x  = body.x + EyeOffset;
  leftEye.y  = body.y + EyeOffset;
  rightEye.x = body.x + (PlayerWidth-EyeOffset-EyeWidth);
  rightEye.y = leftEye.y;
  hat1.x = body.x + Hat1Offset;
  hat1.y = body.y - HatHeight;
  hat2.x = body.x - Hat2Offset;
  hat2.y = body.y - hat2.height;
  hat3.x = hat1.x;
  hat3.y = hat1.y + hat3.height;

  // Apply changes
  player->body = body;
  player->leftEye = leftEye;
  player->rightEye = rightEye;
  player->hat1 = hat1;
  player->hat2 = hat2;
  player->hat3 = hat3;
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
  ApplyPlayerPosition(player);
}

void DrawPlayer(struct Player player) {
  DrawRectangleRec(player.body, BODY_COLOR);
  DrawRectangleRec(player.leftEye, EYES_COLOR);
  DrawRectangleRec(player.rightEye, EYES_COLOR);
  DrawRectangleRec(player.hat1, HAT1_COLOR);
  DrawRectangleRec(player.hat2, HAT2_COLOR);
  DrawRectangleRec(player.hat3, HAT3_COLOR);
}
