#ifndef TINYKEEP_ENGINE
#include <raylib.h>
#include "room.hpp"

namespace TinyKeep {

  struct Engine {
    
    Vector2 origin;
    int tileWidth;
    int numRooms;
    int SpawnRadius;

    void setOrigin(int x, int y);
    void setTileWidth(int x);
    void setNumRooms(int rooms);
    void setSpawnRadius(int radius);

    void generateRooms(Room rooms[]);
    bool separateRooms(Rectangle rooms[]);
    void selectRooms(Rectangle rooms[]);
  };
}
#endif
