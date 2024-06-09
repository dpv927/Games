#ifndef TINYKEEP_ROOM
#include<raylib.h>

namespace TinyKeep {

  struct Room {
    Rectangle shape;
    Vector2 center;
    int area;

    Room(int x, int y, int width, int height);
    void drawRoom(int tileSize);
  };
}
#endif
