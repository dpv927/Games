#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <raylib.h>
#include <vector>
#include "projectile.hpp"

namespace Milkman {

  struct Entity {
    Texture2D sprites;
    Rectangle frame;
    float speed;
    float lerp;
    Rectangle position;
    Vector2 tPosition;
    vector<unique_ptr<Projectile>> projectiles;
    sysTime lastShot;

    virtual void Move(void){};
    virtual void Shoot(void){};
    virtual void Draw(void){};
    virtual ~Entity() = default;
  };
}

#endif // !_PLAYER_H
