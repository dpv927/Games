#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include<raylib.h>

struct Projectile {
  int damage;
  float velocity;
  Vector2 target;
  Texture2D sprite;

  Projectile(int,float,Vector2,Texture2D);
  Projectile(int,float,Texture2D);
  void SetTarget(Vector2);
  void Ai();
  void Draw();
};

#endif // !_PROJECTILE_H
