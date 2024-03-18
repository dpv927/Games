#ifndef _BUFF_H
#define _BUFF_H

#include<raylib.h>
#include <string>

struct Buff {
  std::string name;
  bool isTemporal;
  bool isVisible;
  float lifeTime;
  Texture2D texture;
  
  Buff(std::string, bool, float, Texture2D);
  virtual void UpdateBuff(struct Player&); 
  virtual void Draw();
};

#endif // !_BUFF_H
