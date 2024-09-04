#ifndef TINYKEEP_ROOM
#define TINYKEEP_ROOM

#include <cstddef>
#include<raylib.h>

namespace TinyKeep {

  struct Room {
    int x;
    int y;
    int width;
    int height;
    bool mainRoom;
    std::size_t id;

    bool isCollidingWidth(Room& other);
    void drawRoom(int tileSize);
  };
}
#endif
