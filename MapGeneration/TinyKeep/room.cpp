#include "room.hpp"

namespace TinyKeep {

  Room::Room(int x, int y, int width, int height) {
    this->shape.x = x;
    this->shape.y = y;
    this->shape.width  = width;
    this->shape.height = height;
    this->area = width * height;
    this->center.x = x + width/2.0f;
    this->center.y = y + height/2.0f;
  }

  void Room::drawRoom(int tileSize) {
    
  }
}
