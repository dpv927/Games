#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "engine.hpp"
#include "../utils.hpp"

namespace TinyKeep {

  Engine* Engine::instance = nullptr;
  Engine::Engine(){}
  
  Engine* Engine::getInstance(void) {
    if(instance == nullptr) 
      instance = new Engine();
    return instance;;
  }

  inline float aprox_coordinate(float n, float m) {
   return round((static_cast<float>(n))/m)*m;
  }

  void Engine::generateRooms(
        const uint16_t room_width_min,
        const uint16_t room_width_max, 
        const uint16_t room_height_min,
        const uint16_t room_height_max,
        const float origin_x,
        const float origin_y,
        const uint16_t tile_width,
        const uint32_t num_rooms,
        const uint32_t spawn_radius) {

    rooms.reserve(num_rooms);
    
    for(uint32_t i = 0; i < num_rooms; i++) {
      const float rndRadius = spawn_radius * std::sqrt(utils::gen_random());
      const float angle = utils::gen_random() * 2.0 * M_PI;
      
      Room room;
      room.x = aprox_coordinate(rndRadius * std::cos(angle) + origin_x, tile_width);
      room.y = aprox_coordinate(rndRadius * std::sin(angle) + origin_y, tile_width);
      room.width  = utils::gen_random_from(room_width_min, room_width_max) * tile_width;
      room.height = utils::gen_random_from(room_height_min, room_height_max) * tile_width;
      room.mainRoom = false;
      this->rooms.push_back(room);
    }
  }

  void Engine::separateRooms(uint16_t tile_width) {
    bool rooms_overlap;

    do {
      rooms_overlap = false;

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
            actual.x = aprox_coordinate(actual.x, tile_width);
            actual.y = aprox_coordinate(actual.y, tile_width);
            other.x  = aprox_coordinate(other.x,  tile_width);
            other.y  = aprox_coordinate(other.y,  tile_width);
            rooms_overlap = true;
          }
        }
      }
    } while(rooms_overlap);
  } 

  void Engine::selectRooms(const float threshold) {
    double avgWidth  {0};
    double avgHeight {0};
    long idCount {0};

    // Get the average area of a room;
    for (const Room& room : rooms) {
      avgWidth  += room.width;
      avgHeight += room.height;
    }

    avgWidth  = avgWidth/rooms.size()  * threshold;
    avgHeight = avgHeight/rooms.size() * threshold;

    // Select the main rooms (the rooms with)
    // a greater area than the average 
    for (Room& room : rooms) {
      if((room.width >= avgWidth) && (room.height >= avgHeight)) {
        room.mainRoom = true;
        room.id = idCount++;
        main_rooms.push_back(&room);
      }
    }
  }
}
