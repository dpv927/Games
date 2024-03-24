#include "sys.hpp"
#include <chrono>
#include <cmath>
#include <memory>
#include <raylib.h>
#include "player.hpp"

Player::Player(char* texture, Vector2 position) { 
  this->sprites = LoadTexture(texture);
  SetTextureFilter(this->sprites, TEXTURE_FILTER_TRILINEAR);

  this->frame.x = this->frame.y = 0;
  this->frame.width = (float)this->sprites.width/PlayerNumSprites;
  this->frame.height = this->sprites.height-1;

  this->position.x = Sys::screenWidth/2.0f;
  this->position.y = Sys::screenHeight/2.0f;
  this->position.width = this->frame.width * Sys::scaleX;
  this->position.height = this->frame.height * Sys::scaleY;

  this->tPosition.x = this->position.x;
  this->tPosition.y = this->position.y;

  this->speed = PlayerBaseSpeed * Sys::scaleX;
  this->lerp = PlayerBaseLerp * Sys::scaleX;
  this->lastShot = high_resolution_clock::now();
} 

void Player::Move(void) {
  int moveX = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
  int moveY = (IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
  this->tPosition.x += moveX * this->speed;
  this->tPosition.x += moveY * this->speed;

  // Apply Interpolation for a smoother movement.
  this->position.x += this->lerp * (this->tPosition.x - this->position.x);
  this->position.y += this->lerp * (this->tPosition.y - this->position.y);

  // After changing the player position, we need to update the 
  // player direction frame.
  this->frame.x = (moveX==0 && moveY==0 || moveX==0 && moveY==1)? 0 :
      (moveX ==  0 && moveY == -1)? this->frame.width :
      (moveX == -1 && moveY ==  0)? 2*(float)this->frame.width :
      (moveX ==  1 && moveY ==  0)? 3*(float)this->frame.width :
      (moveX == -1 && moveY !=  0)? 4*(float)this->frame.width :
      (moveX ==  1 && moveY !=  0)? 5*(float)this->frame.width : 0;
}

void Player::Shoot(void) {
  time_point timeNow = high_resolution_clock::now();

  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && 
     duration_cast<milliseconds>(timeNow - lastShot).count()) {

    this->lastShot = timeNow;
    int mx = GetMouseX() - this->position.x;
    int my = GetMouseY() - this->position.y;
    float mod = sqrt(exp2(mx) + exp2(my));

    Vector2 projPos = {0};
    projPos.x = this->position.x + this->position.width/2.0f;
    projPos.y = this->position.y + this->position.height/2.0f;

    this->projectiles.push_back(make_unique<Projectile>(
      projPos, timeNow));
  }
}

void Player::Draw(void) {

  // Draw the player's projectiles
  for (auto it = this->projectiles.begin(); it != this->projectiles.end();) {
    auto& projectile = *it;

    if (duration_cast<milliseconds>(Sys::timeNow - projectile->spawnTime).count() >= 2000) {
      it = this->projectiles.erase(it);
    } else {
      projectile->ExecAi();
      projectile->Draw();
      ++it;
    }
  }

  // Draw only the player
  DrawTexturePro(this->sprites, this->frame, this->position,
    Vector2{0}, 0, WHITE);
}
