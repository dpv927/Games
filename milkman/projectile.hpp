#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <raylib.h>
#include "types.hpp"
#include "sys.hpp"

namespace Milkman {
  
  struct Projectile {
    Vector2 position;
    float speedX;
    float speedY;
    long lifeTime;
    sysTime spawnTime;

    Projectile(Vector2 position, Vector2 direction) {
      this->position = position;
      this->speedX = direction.x;
      this->speedY = direction.y;
      this->spawnTime = Window::timeNow; 
    }
    
    virtual void ExecAi(void){};
    virtual void Draw(void){};
  };
}

#endif // !_PROJECTILE_H
