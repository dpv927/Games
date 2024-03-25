#include "projectile.hpp"
#include <iostream>
#include <raylib.h>

void Projectile::ExecAi(void) {
  cout << "(" << this->speedX << "," << this->speedY << ")" <<endl;
  this->position.x += this->speedX;
  this->position.y += this->speedY;
}

void Projectile::Draw(void) {
  DrawCircleV(this->position, this->radius, BLACK);
  DrawCircleV(this->position, this->radius*0.85f, WHITE);
}
