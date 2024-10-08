#ifndef _H_TREE
#define _H_TREE

#include <random>
#include "door.hpp"

#define FREE_CONNECTIONS 3
#define CONNECTIONS 4

class Room {
  
  struct Connection {
    Room* destRoom;
    Door destDoor;
    bool isParent;

    Connection() : 
      destRoom(nullptr),
      destDoor(UNSET),
      isParent(false) {}
  };

public:
  Connection connections[CONNECTIONS];
  int x;
  int y;

  Room() : x(0), y(0) {}
  ~Room() { destroySubtree(); }

  void generateSubtree(int maxDepth);
  void destroySubtree(void);
  void printSubtree(int depth);

private:
  inline void addParentConnection(Door srcDoor, Room* dstRoom, Door dstDoor) {
    auto& connection = this->connections[srcDoor];
    connection.destRoom = dstRoom;
    connection.destDoor = dstDoor;
    connection.isParent = true;
  }

  inline void addConnection(Door srcDoor, Room* dstRoom, Door dstDoor) {
    auto& connection = this->connections[srcDoor];
    connection.destRoom = dstRoom;
    connection.destDoor = dstDoor;
    connection.isParent = false;
  }


  void generateSubtree(int depth, int maxDepth);
  static std::uniform_int_distribution<int> distribution;
  static std::mt19937 rng;
};

#endif
