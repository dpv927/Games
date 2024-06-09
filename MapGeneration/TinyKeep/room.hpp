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
    bool mainRoom;

    bool isCollidingWidth(Room& other);
    void drawRoom(int tileSize);
  };
}
#endif
