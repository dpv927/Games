#ifndef TINYKEEP_ROOM
#define TINYKEEP_ROOM

#include<raylib.h>

namespace TinyKeep {

  struct Room {
  public:
    float x;
    float y;
    float width;
    float height;
    int area;

    bool isCollidingWidth(Room& other);
    void drawRoom(int tileSize);
  };
}
#endif
