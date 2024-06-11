#ifndef TINYKEEP_ENGINE
#define TINYKEEP_ENGINE

#include <raylib.h>
#include <vector>
#include "room.hpp"

#define DEF_MIN_TILESW 2
#define DEF_MAX_TILESW 11
#define DEF_MIN_TILESH 2
#define DEF_MAX_TILESH 11

#define DEF_ORIGINXY 0
#define DEF_TILEW    10
#define DEF_NUMROOMS 100
#define DEF_SPAWNRAD 20

namespace TinyKeep {

  struct Engine {
  private:
    int rminTilesW;
    int rmaxTilesW;
    int rminTilesH;
    int rmaxTilesH;
    
    Vector2 origin;
    int tileWidth;
    int numRooms;
    int spawnRadius;
    
    static Engine* instance;
    Engine(void);

  public:
    static Engine* getInstance();
    Engine* setRoomMinTilesWidth(const int n);
    Engine* setRoomMaxTilesWidth(const int n);
    Engine* setRoomMinTilesHeight(const int n);
    Engine* setRoomMaxTilesHeight(const int n);

    Engine* setOrigin(const int x, const int y);
    Engine* setTileWidth(const int x);
    Engine* setNumRooms(const int rooms);
    Engine* setSpawnRadius(const int radius);

    void generateRooms(std::vector<Room>& rooms);
    bool separateRooms(std::vector<Room>& rooms);
    void selectRooms(std::vector<Room>& rooms, const float threshold);
  };
}
#endif
