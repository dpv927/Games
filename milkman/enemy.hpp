#ifndef _ENEMY_H
#define _ENEMY_H

#include <raylib.h>
#include <vector>
#include <utility>
#include "buff.hpp"
#include "projectile.hpp"

struct Enemy {
  int maxLife;
  int life;
  bool melee;
  int milk;
  Projectile shoot;
  Texture2D sprite;
  std::vector<std::pair<Buff,float>>buffs;
};

#endif // !_ENEMY_H
