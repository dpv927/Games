#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <vector>
#include "engine.hpp"
#include "../utils.hpp"
#include "delaunator.hpp"
#include "graph.hpp"

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
 
  // Fast integer *2 multiplication
  inline std::size_t mult2(std::size_t x) {
    return x << 1;
  }

  /// Euclidean distance between two points (x1,y1) and (x2,y2).
  inline float point_distance(float x1, float y1, float x2, float y2) {
    return sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
  }

  std::vector<Graph::Edge> Engine::calculate_graph(void) {
    std::map<std::pair<double,double>, int> roomHashes;
    std::vector<double> coords;
    std::vector<Graph::Edge> graph;
    std::size_t num_rooms {0};

    // Insert the coordinates of every main room
    // in a vector for the Delaunator library 
    for (TinyKeep::Room& room : rooms) {
      if(!room.mainRoom)
        continue;

      float middlex = room.x + room.width/2.0f;
      float middley = room.y + room.height/2.0f;

      coords.push_back(middlex);
      coords.push_back(middley);
      roomHashes[std::pair(middlex, middley)] = room.id;
      num_rooms++;
    }

    // Calculate the triangulations
    delaunator::Delaunator d(coords);
    
    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
      // Get all 3 triangle vertices.
      const std::pair v1(d.coords[mult2(d.triangles[i])],     d.coords[mult2(d.triangles[i]) + 1]);
      const std::pair v2(d.coords[mult2(d.triangles[i + 1])], d.coords[mult2(d.triangles[i + 1]) + 1]);
      const std::pair v3(d.coords[mult2(d.triangles[i + 2])], d.coords[mult2(d.triangles[i + 2]) + 1]);

      // Get each vertex room ID
      const std::size_t hv1 = roomHashes[v1];
      const std::size_t hv2 = roomHashes[v2];
      const std::size_t hv3 = roomHashes[v3];

      // Add each triangle edge to the graph as a new edge.
      graph.push_back({hv1, hv2, point_distance(v1.first, v1.second, v2.first, v2.second)});
      graph.push_back({hv1, hv3, point_distance(v1.first, v1.second, v3.first, v3.second)});
      graph.push_back({hv2, hv3, point_distance(v2.first, v2.second, v3.first, v3.second)});
    }
    return Graph::calculate_MST(graph, num_rooms);
  }
}
