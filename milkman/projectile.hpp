#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <raylib.h>
#include "types.hpp"
#define BaseProjectileSpeed 8

struct Projectile {
  Vector2 position;
  float speedX;
  float speedY;
  float radius;
  long lifetime;
  sysTime spawnTime;

  Projectile(Vector2 pos, sysTime spawn):
  position(pos), spawnTime(spawn) {};

  void ExecAi(void);
  void Draw(void);
};
 
#endif // !_PROJECTILE_H
