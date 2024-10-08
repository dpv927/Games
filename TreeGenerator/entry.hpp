#ifndef _H_DOOR
#define _H_DOOR 

#include <utility>

enum Entry {
  NORTH,
  EAST,
  SOUTH,
  WEST,
  UNSET
};

inline Entry getSymetric(Entry e) {
  switch (e) {
  case NORTH: return SOUTH;
  case EAST:  return WEST;
  case SOUTH: return NORTH;
  case WEST:  return EAST;
  default: return UNSET;
  }
}

inline std::pair<int, int> getOffset(Entry e) {
  switch (e) {
  case NORTH: return std::make_pair(0,1);
  case EAST:  return std::make_pair(1,0);
  case SOUTH: return std::make_pair(0,-1);
  case WEST:  return std::make_pair(-1,0);
  default: return std::make_pair(0,0);
  }
} 

#endif
