#ifndef TINYKEEP_ENGINE
#define TINYKEEP_ENGINE

#include <raylib.h>
#include "room.hpp"

#define DEF_MIN_TILESW 2
#define DEF_MAX_TILESW 11
#define DEF_MIN_TILESH 2
#define DEF_MAX_TILESH 11

namespace TinyKeep {

  struct Engine {
  private:
    static int rminTilesW;
    static int rmaxTilesW;
    static int rminTilesH;
    static int rmaxTilesH;
    
    Vector2 origin;
    int tileWidth;
    int numRooms;
    int SpawnRadius;

  public:
    static int setRoomMinTilesWidth(int n);
    static int setRoomMaxTilesWidth(int n);
    static int setRoomMinTilesHeight(int n);
    static int setRoomMaxTilesHeight(int n);

    void setOrigin(int x, int y);
    void setTileWidth(int x);
    void setNumRooms(int rooms);
    void setSpawnRadius(int radius);

    void generateRooms(Room rooms[]);
    bool separateRooms(Room rooms[]);
    void selectRooms(Room rooms[]);
  };
}
#endif
