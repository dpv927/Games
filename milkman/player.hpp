#ifndef _PLAYER_H
#define _PLAYER_H

#include <raylib.h>
#include "entity.hpp"

#define PlayerBaseSpeed 10
#define PlayerNumSprites 6
#define PlayerBaseLerp 0.08f

namespace Milkman {

  enum PlayerAnimations {
    DOWN=0,
    UP,
    LEFT ,
    RIGHT,
    DIG_LEFT,
    DIG_RIGHT
  };

  struct Player : public Entity {
    Player(char*, Vector2);
    void Move(void)  override;
    void Shoot(void) override;
    void Draw(void)  override;
  };
}

#endif // !_PLAYER_H
