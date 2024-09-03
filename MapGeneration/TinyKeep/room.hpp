#ifndef TINYKEEP_ROOM
#define TINYKEEP_ROOM

#include <cstddef>
#include<raylib.h>

namespace TinyKeep {

  struct Room {
    float x;
    float y;
    float width;
    float height;
    bool mainRoom;
    std::size_t id;

    bool isCollidingWidth(Room& other);
    void drawRoom(int tileSize);
  };
}
#endif
