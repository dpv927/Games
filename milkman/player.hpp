#ifndef _PLAYER_H
#define _PLAYER_H

#include <memory>
#include <raylib.h>
#include <vector>
#include "projectile.hpp"

#define PlayerBaseSpeed 10
#define PlayerNumSprites 6
#define PlayerBaseLerp 0.08f

using namespace std;
using namespace std::chrono; 


struct Player {
  Texture2D sprites;
  Rectangle frame;
  float speed;
  float lerp;
  Rectangle position;
  Vector2 tPosition;
  //Projectile projectile;
  vector<unique_ptr<Projectile>> projectiles;
  sysTime lastShot;

  // Constructor:
  // - Texture & position
  Player(char*, Vector2);
  
  void Move(void);
  void Shoot(void);
  void Draw(void);
};

#endif // !_PLAYER_H
