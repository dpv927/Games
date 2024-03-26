#include <raylib.h>
#include "../projectile.hpp"
#include "../sys.hpp"

#define MB_RADIUS 10 
#define MB_LIFE 1300
#define MP_SPEED 8

namespace Milkman::Projectiles {

  struct MilkBullet : public Projectile {
    
    MilkBullet(Vector2 position, Vector2 direction): 
    Projectile(position, direction) {
      this->lifeTime = MB_LIFE;
      this->speedX *= MP_SPEED * Window::scaleX;
      this->speedY *= MP_SPEED * Window::scaleY;
    }

    void ExecAi() override {
      this->position.x += this->speedX;
      this->position.y += this->speedY;
    }

    void Draw() override {
      DrawCircleV(this->position, MB_RADIUS*Window::scaleX, BLACK);
      DrawCircleV(this->position, MB_RADIUS*Window::scaleX*0.85f, WHITE);
    }
  };
}
