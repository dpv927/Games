#include <cmath>
#include <cstdlib>
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

  void Engine::generateRooms(Room rooms[]) {
    float rndRadius;
    float angle;

    for (int i = 0; i < numRooms; i++) {
      Room& room = rooms[i];
      rndRadius = SpawnRadius * sqrt(genRandom());
      angle = genRandom()*2.0f*M_PI;

      room.x = aproxCoordinate(rndRadius * cos(angle) + origin.x, tileWidth);
      room.y = aproxCoordinate(rndRadius * sin(angle) + origin.y, tileWidth);
      room.width  = genRandomFrom(Engine::rminTilesW, Engine::rmaxTilesW) * tileWidth;
      room.height = genRandomFrom(Engine::rminTilesH, Engine::rmaxTilesH) * tileWidth;
      room.area = room.width * room.height;
    }
  }

  bool Engine::separateRooms(Room rooms[]) {
    bool rooms_overlap = false;

    for (int i = 0; i < numRooms; i++) {
      const float mrw_i = rooms[i].width/2.0f;
      const float mrh_i = rooms[i].height/2.0f;
      Room& actual = rooms[i];

      for (int j = i + 1; j < numRooms; j++) {
        Room& other = rooms[j];

        if (actual.isCollidingWidth(other)){
          const float mrw_j = rooms[j].width/2.0f;
          const float mrh_j = rooms[j].height/2.0f;

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

  void Engine::selectRooms(Room rooms[]) {
  
  }
}
