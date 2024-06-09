#include "room.hpp"
#include "raylib.h"

namespace TinyKeep {

  bool Room::isCollidingWidth(Room& other) {
    return ((this->x < (other.x + other.width) && (this->x + this->width) > other.x) &&
        (this->y < (other.y + other.height) && (this->y + this->height) > other.y));
  }

  void Room::drawRoom(int tileSize) {
    for (int posx = this->x; posx< (this->x + this->width); posx+=tileSize)
      for (int posy = this->y; posy < (this->y + this->height); posy+=tileSize)
        DrawRectangleLines(posx, posy, tileSize, tileSize, BLUE);
    DrawRectangleLines(this->x, this->y, this->width, this->height, WHITE);
  }
}
