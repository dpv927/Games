#ifndef _BUFF_H
#define _BUFF_H

#include<raylib.h>
#include <string>

struct Buff {
  std::string name;
  bool temporal;
  float lifeTime;
  Texture2D texture;

  Buff(std::string, bool, float, Texture2D);
  void ApplyBuff(struct Player&);
  void Draw();
};

#endif // !_BUFF_H
