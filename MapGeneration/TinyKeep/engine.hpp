#ifndef TINYKEEP_ENGINE
#define TINYKEEP_ENGINE

#include <cstdint>
#include <raylib.h>
#include <vector>
#include "room.hpp"

namespace TinyKeep {

  struct Engine {
  public:
    std::vector<Room> rooms;
    std::vector<Room*> main_rooms;
  private:
    static Engine* instance;
    Engine(void);

  public:
    static Engine* getInstance();
    void generateRooms(
        const uint16_t room_width_min,
        const uint16_t room_width_max, 
        const uint16_t room_height_min,
        const uint16_t room_height_max,
        const float origin_x,
        const float origin_y,
        const uint16_t tile_width,
        const uint32_t num_rooms,
        const uint32_t spawn_radius);
    void separateRooms(const uint16_t tile_width);
    void selectRooms(const float threshold);
  };
}
#endif
