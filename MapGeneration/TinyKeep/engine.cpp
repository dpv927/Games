#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "engine.hpp"
#include "../utils.hpp"

namespace TinyKeep {

  Engine* Engine::instance = nullptr;

  Engine::Engine(void) {
    // Room sides tiles number
    this->rminTilesW = DEF_MIN_TILESW;
    this->rmaxTilesW = DEF_MAX_TILESW;
    this->rminTilesH = DEF_MIN_TILESH;
    this->rmaxTilesH = DEF_MAX_TILESH;
  
    // Generator propierties
    this->origin.x    = DEF_ORIGINXY;
    this->origin.y    = DEF_ORIGINXY;
    this->tileWidth   = DEF_TILEW;
    this->numRooms    = DEF_NUMROOMS;
    this->spawnRadius = DEF_SPAWNRAD;
  }

  Engine* Engine::getInstance(void) {
    if(instance == nullptr) 
      instance = new Engine();
    return instance;;
  }

  Engine* Engine::setOrigin(const int x, const int y) {
    this->origin.x = x;
    this->origin.y = y;
    return this;
  }

  Engine* Engine::setRoomMinTilesWidth(const int n) {
    this->rminTilesW = n;
    return this;;
  }

  Engine* Engine::setRoomMaxTilesWidth(const int n) {
    this->rmaxTilesW = n;
    return this;
  }

  Engine* Engine::setRoomMinTilesHeight(const int n) {
    this->rminTilesH = n;
    return this;
  }

  Engine* Engine::setRoomMaxTilesHeight(const int n) {
    this->rmaxTilesH = n;
    return this;
  }

  Engine* Engine::setTileWidth(const int width) {
    this->tileWidth = width;
    return this;;
  }

  Engine* Engine::setNumRooms(const int rooms) {
    this->numRooms = rooms;
    return this;
  }

  Engine* Engine::setSpawnRadius(const int radius) {
    this->spawnRadius = radius;
    return this;
  }

  void Engine::generateRooms(std::vector<Room>& rooms) {
    for (Room& room : rooms) {
      const double rndRadius = spawnRadius * std::sqrt(genRandom());
      const double angle = genRandom() * 2.0 * M_PI;
      
      room.x = aproxCoordinate(rndRadius * std::cos(angle) + origin.x, tileWidth);
      room.y = aproxCoordinate(rndRadius * std::sin(angle) + origin.y, tileWidth);
      room.width  = genRandomFrom(Engine::rminTilesW, Engine::rmaxTilesW) * tileWidth;
      room.height = genRandomFrom(Engine::rminTilesH, Engine::rmaxTilesH) * tileWidth;
      room.mainRoom = false;
    }
  }

  bool Engine::separateRooms(std::vector<Room>& rooms) {
    bool rooms_overlap {false};

    for (auto it = rooms.begin(); it != rooms.end(); it++) {
      Room& actual {*it};
      const float mrw_i {actual.width/2.0f};
      const float mrh_i {actual.height/2.0f};

      for (auto jt = (it + 1); jt != rooms.end(); jt++) {
        Room& other {*jt};

        if (actual.isCollidingWidth(other)){
          const float mrw_j {other.width/2.0f};
          const float mrh_j {other.height/2.0f};
          
          // Differential betteen both rooms center 
          // coordinates
          const float dx {(other.x + mrw_j) - (actual.x + mrw_i)};
          const float dy {(other.y + mrh_j) - (actual.y + mrh_i)};

          // Instead of overlap, they are overlap/2 to avoid doing 
          // the same operation twice at the 'if's below.
          const float overlapX = ((mrw_i + mrw_j) - std::fabs(dx))/2.0f;
          const float overlapY = ((mrh_i + mrh_j) - std::fabs(dy))/2.0f;

          if (overlapX < overlapY) {
            if (dx > 0) {
              actual.x -= overlapX;
              other.x += overlapX;
            } else {
              actual.x += overlapX;
              other.x -= overlapX;
            }
          } else {
            if (dy > 0) {
              actual.y -= overlapY;
              other.y += overlapY;
            } else {
              actual.y += overlapY;
              other.y -= overlapY;
            }
          }

          // Adjust the coordinates to the grid
          actual.x = aproxCoordinate(actual.x, tileWidth);
          actual.y = aproxCoordinate(actual.y, tileWidth);
          other.x  = aproxCoordinate(other.x,  tileWidth);
          other.y  = aproxCoordinate(other.y,  tileWidth);
          rooms_overlap = true;
        }
      }
    }
    return rooms_overlap;  
  } 

  void Engine::selectRooms(std::vector<Room>& rooms, const float threshold) {
    double avgWidth  {0};
    double avgHeight {0};
    long idCount {0};

    // Get the average area of a room;
    for (const Room& room : rooms) {
      avgWidth  += room.width;
      avgHeight += room.height;
    }

    avgWidth  = avgWidth/numRooms  * threshold;
    avgHeight = avgHeight/numRooms * threshold;

    // Select the mai rooms (the rooms with)
    // a greater area than the average 
    for (Room& room : rooms) {
      if((room.width >= avgWidth) && (room.height >= avgHeight)) {
        room.middlex = room.x + room.width/2,0;
        room.middley = room.y + room.height/2.0;
        room.mainRoom = true;
        room.id = idCount++;
        std::cout << room.id << " " << idCount << std::endl;
      }
    }
  }
}
