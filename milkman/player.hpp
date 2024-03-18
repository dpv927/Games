#ifndef _PLAYER_H
#define _PLAYER_H

#include <raylib.h>
#include <vector>
#include "projectile.hpp"
#include "buff.hpp"

enum Direction {
  NORTH, 
  SOUTH,
  EAST,
  WEST,
  ANY_EAST,
  ANY_WEST,
};

struct Player {
  int maxLife;
  int life;
  int milk;
  Projectile shoot;
  Texture2D sprite;
  std::vector<Buff> buffs;
  std::vector<Projectile> projectiles;

  Player(Projectile, Texture2D);
  void Shoot();
  void Move();
  void Draw();
};

#endif // !_PLAYER_H
