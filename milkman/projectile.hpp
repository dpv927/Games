#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <raylib.h>
#include "types.hpp"

#define PROJ_SPEED 8
#define PROJ_LIFE  1500
#define PROJ_RAD   10

namespace Milkman {
  
  struct Projectile {
    Vector2 position;
    float speedX;
    float speedY;
    float radius;
    long lifetime;
    sysTime spawnTime;

    Projectile(void);
    Projectile(Vector2 pos, float sX, float sY);

    void ExecAi(void);
    void Draw(void);
  };
}
#endif // !_PROJECTILE_H
