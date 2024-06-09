#include "engine.hpp"

namespace TinyKeep {

  void Engine::setOrigin(int x, int y) {
    this->origin.x = x;
    this->origin.y = y;
  }

  void Engine::setTileWidth(int width) {
    this->tileWidth = width;
  }

  void Engine::setNumRooms(int rooms) {
    this->numRooms = rooms;
  }

  void Engine::setSpawnRadius(int radius) {
    this->SpawnRadius = radius;
  }

  void Engine::generateRooms(Room rooms[]) {

  }

  bool Engine::separateRooms(Rectangle rooms[]) {
    return false;
  }

  void Engine::selectRooms(Rectangle rooms[]) {
  
  }
}
