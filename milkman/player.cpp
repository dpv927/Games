#include "projectile.hpp"
#include "sys.hpp"
#include <cmath>
#include <raylib.h>
#include "player.hpp"
#include "Projectiles/milkBullet.hpp"

using namespace Milkman::Projectiles;

namespace Milkman {

  Player::Player(char* texture, Vector2 position) { 
    this->sprites = LoadTexture(texture);
    SetTextureFilter(this->sprites, TEXTURE_FILTER_TRILINEAR);

    this->frame.x = this->frame.y = 0;
    this->frame.width = (float)this->sprites.width/PlayerNumSprites;
    this->frame.height = this->sprites.height-1;

    this->position.x = position.x;
    this->position.y = position.y;
    this->position.width = this->frame.width * Window::scaleX;
    this->position.height = this->frame.height * Window::scaleY;

    this->tPosition.x = this->position.x;
    this->tPosition.y = this->position.y;

    this->speed = PlayerBaseSpeed * Window::scaleX;
    this->lerp = PlayerBaseLerp;
    this->lastShot = Window::timeNow;
  } 

  void Player::Move(void) {
    double moveX = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    double moveY = (IsKeyDown(KEY_S) - IsKeyDown(KEY_W));

    if(moveX && moveY) {
      moveX /= 2.0f;
      moveY /= 2.0f; 
    }
    
    this->tPosition.x += moveX * this->speed;
    this->tPosition.y += moveY * this->speed;

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
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && 
      duration_cast<milliseconds>(Window::timeNow - lastShot).count() > 300) {
      this->lastShot = Window::timeNow;

      Vector2 projPos;
      projPos.x = this->position.x + this->position.width/2.0f;
      projPos.y = this->position.y + this->position.height/2.0f;

      const int mx = GetMouseX() - projPos.x;
      const int my = GetMouseY() - projPos.y;
      const float mod = sqrt(mx*mx + my*my);

      Vector2 projDirec;
      projDirec.x = (mx/mod);
      projDirec.y = (my/mod);

      this->projectiles.push_back(make_unique<MilkBullet>(
        projPos, projDirec));
    }
  }

  void Player::Draw(void) {

    // Draw the player's projectiles
    for (auto it = this->projectiles.begin(); it != this->projectiles.end();) {
      auto& projectile = *it;
      Vector2 pos = projectile->position;

      if(!Window::isOutside(projectile->position) || duration_cast<milliseconds>
        (Window::timeNow - projectile->spawnTime).count() >= projectile->lifeTime) {
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
}
