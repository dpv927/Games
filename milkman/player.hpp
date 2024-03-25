#ifndef _PLAYER_H
#define _PLAYER_H

#include <memory>
#include <raylib.h>
#include <vector>
#include "projectile.hpp"

#define PlayerBaseSpeed 10
#define PlayerNumSprites 6
#define PlayerBaseLerp 0.08f

namespace Milkman {

  struct Player {
    Texture2D sprites;
    Rectangle frame;
    float speed;
    float lerp;
    Rectangle position;
    Vector2 tPosition;
    vector<unique_ptr<Projectile>> projectiles;
    sysTime lastShot;

    Player(char*, Vector2);
    void Move(void);
    void Shoot(void);
    void Draw(void);
  };
}

#endif // !_PLAYER_H
