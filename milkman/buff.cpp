#include "buff.hpp"
#include "player.hpp"
#include <raylib.h>
#include <string>

/*
struct Buff {
  std::string name;
  bool temporal;
  float lifeTime;
  Texture2D texture;

  Buff(std::string, bool, float, Texture2D);
  void ApplyBuff(struct Player&);
  void Draw();
};
*/

Buff::Buff(std::string name, bool isTemporal, float lifeTime, Texture2D texture) {
  this->name = name;
  this->isTemporal = isTemporal;
  this->lifeTime = lifeTime;
  this->texture = texture;
}

void Buff::Draw() {
  DrawTexturePro(
    this->texture,
    (Rectangle){this->texture.width, this->texture.height},
    , Vector2 origin, float rotation, Color tint)
}
