#include "projectile.hpp"
#include "sys.hpp"
#include <raylib.h>

namespace Milkman {

  Projectile::Projectile() {}
  
  Projectile::Projectile(Vector2 pos, float speedX, float speedY) {
    this->position = pos;
    this->speedX = speedX * Window::scaleX;
    this->speedY = speedY * Window::scaleX;
    this->radius = PROJ_RAD * Window::scaleX;
    this->spawnTime = Window::timeNow;
    this->lifetime = PROJ_LIFE;
  }

  void Projectile::ExecAi(void) {
    this->position.x += this->speedX;
    this->position.y += this->speedY;
  }

  void Projectile::Draw(void) {
    DrawCircleV(this->position, this->radius, BLACK);
    DrawCircleV(this->position, this->radius*0.85f, WHITE);
  }
}
