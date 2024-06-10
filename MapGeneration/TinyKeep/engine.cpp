#include <cmath>
#include <cstdlib>
#include <vector>
#include "engine.hpp"
#include "../utils.hpp"

namespace TinyKeep {

  int Engine::rminTilesW = DEF_MIN_TILESW;
  int Engine::rmaxTilesW = DEF_MAX_TILESW;
  int Engine::rminTilesH = DEF_MIN_TILESH;
  int Engine::rmaxTilesH = DEF_MAX_TILESH;

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

  void Engine::generateRooms(std::vector<Room>& rooms) {
    float rndRadius;
    float angle;

    for (Room& room : rooms) {
      rndRadius = SpawnRadius * sqrt(genRandom());
      angle = genRandom() * 2.0f * M_PI;
      
      room.x = aproxCoordinate(rndRadius * cos(angle) + origin.x, tileWidth);
      room.y = aproxCoordinate(rndRadius * sin(angle) + origin.y, tileWidth);
      room.width  = genRandomFrom(Engine::rminTilesW, Engine::rmaxTilesW) * tileWidth;
      room.height = genRandomFrom(Engine::rminTilesH, Engine::rmaxTilesH) * tileWidth;
      room.mainRoom = false;
    }
  }

  bool Engine::separateRooms(std::vector<Room>& rooms) {
    bool rooms_overlap = false;

    for (auto it = rooms.begin(); it != rooms.end(); it++) {
      Room& actual = *it;
      const float mrw_i = actual.width/2.0f;
      const float mrh_i = actual.height/2.0f;

      for (auto jt = (it + 1); jt != rooms.end(); jt++) {
        Room& other = *jt;

        if (actual.isCollidingWidth(other)){
          const float mrw_j = other.width/2.0f;
          const float mrh_j = other.height/2.0f;
          
          // Differential betteen both rooms center 
          // coordinates
          const float dx = (other.x + mrw_j) - (actual.x + mrw_i);
          const float dy = (other.y + mrh_j) - (actual.y + mrh_i);

          // Instead of overlap, they are overlap/2 to avoid doing 
          // the same operation twice at the 'if's below.
          const float overlapX = ((mrw_i + mrw_j) - fabs(dx))/2.0f;
          const float overlapY = ((mrh_i + mrh_j) - fabs(dy))/2.0f;

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

  void Engine::selectRooms(std::vector<Room>& rooms, float threshold) {
    float avgWidth  = 0.0f;
    float avgHeight = 0.0f;

    // Get the average area of a room;
    for (Room& room : rooms) {
      avgWidth  += room.width;
      avgHeight += room.height;
    }

    avgWidth  = avgWidth/numRooms  * threshold;
    avgHeight = avgHeight/numRooms * threshold;

    // Select the mai rooms (the rooms with)
    // a greater area than the average 
    for (Room& room : rooms)
      if((room.width >= avgWidth) && (room.height >= avgHeight))
        room.mainRoom = true;
  }
}
