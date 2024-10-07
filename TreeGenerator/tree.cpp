#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

typedef struct Room Room;

int allocs = 0;
int frees = 0;

enum Door {
  NORTH,
  EAST,
  SOUTH,
  WEST,
  UNSET
};

inline Door getSymetric(Door door) {
  switch (door) {
  case NORTH: return SOUTH;
  case EAST:  return WEST;
  case SOUTH: return NORTH;
  case WEST:  return EAST;
  default: return UNSET;
  }
}

struct RoomConnection {
  Room* destRoom;
  Door destDoor;
  bool isParent;

  RoomConnection() : 
    destRoom(nullptr),
    destDoor(UNSET),
    isParent(false) {}
};

struct Room {
  static std::mt19937 rng;
  static std::uniform_int_distribution<int> distribution;

  #define MAX_CONNECTIONS 4
  RoomConnection connections[MAX_CONNECTIONS];
  int x;
  int y;

  Room() : x(0), y(0) {}

  ~Room() {
    destroySubtree();
  }

  void addParentConnection(Door srcDoor, Room* dstRoom, Door dstDoor) {
    RoomConnection& connection = this->connections[(int)srcDoor];
    connection.destRoom = dstRoom;
    connection.destDoor = dstDoor;
    connection.isParent = true;
  }

  void addConnection(Door srcDoor, Room* dstRoom, Door dstDoor) {
    RoomConnection& connection = this->connections[(int)srcDoor];
    connection.destRoom = dstRoom;
    connection.destDoor = dstDoor;
    connection.isParent = false;
  }

  void generateSubtree(int maxDepth) {
    int door = 0;

    for(auto& connection : this->connections) {
      Door thisDoor = (Door)door;
      Door childDoor = getSymetric(thisDoor);
      Room* child = new Room();
      
      child->addParentConnection(childDoor, this, thisDoor);
      connection.destDoor = childDoor;
      connection.destRoom = child;
      connection.isParent = false;
      child->generateSubtree(1, maxDepth);
    }
  }

  void generateSubtree(int depth, int maxDepth) {
    //Door unusedDoors[] = { UNSET, UNSET, UNSET };
    std::vector<Door> unusedDoors;
    
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
      if (this->connections[i].destRoom == nullptr) {
        unusedDoors.push_back((Door)i);
      }
    }

    if (unusedDoors.empty()) return;

    const int randConnections = std::min(static_cast<int>(unusedDoors.size()), distribution(rng));
    if (randConnections == 0) return;
    std::shuffle(unusedDoors.begin(), unusedDoors.end(), rng);

    for (int i = 0; i < randConnections; i++) {
      Door thisDoor = unusedDoors[i];
      Door childDoor = getSymetric(thisDoor);
      Room* child = new Room();
      allocs += 1;

      child->addParentConnection(childDoor, this, thisDoor);
      this->addConnection(thisDoor, child, childDoor);

      if ((depth + 1) < maxDepth) {
        child->generateSubtree(depth + 1, maxDepth);
      }
    }
  }

  void destroySubtree() {
    for (auto& connection : this->connections) {
      if (connection.destRoom != nullptr && !connection.isParent) {
        connection.destRoom->destroySubtree();
        delete connection.destRoom;
        connection.destRoom = nullptr;
        frees += 1;
      }
    }
  }

  void printSubtree(int depth) {
    std::string fmt;
    int port = 0;

    // Setup the depth identation
    for (int i = 0; i < depth; i++)
      fmt += "\t";

    std::cout << fmt 
      << "\033[1m\033[32m<@" << (unsigned long long) this
      << ">\033[0m" << std::endl;
       
    for (auto& connection : this->connections) {
      if (connection.destRoom == nullptr) {
        std::cout << fmt
          << "[" << port << "] = @null"
          << std::endl;
      
      } else {
        std::cout << fmt 
          << "[" << port << "] = @"
          << (unsigned long long)connection.destRoom
          << std::endl;
      }
      ++port;
    }

    for (auto& connection : this->connections) {
      if (connection.destRoom != nullptr && !connection.isParent) {
        connection.destRoom->printSubtree(depth + 1);
      }
    }
  }
};

std::mt19937 Room::rng(std::random_device{}());
std::uniform_int_distribution<int> Room::distribution(1, 4);

int main() {
    {
      Room room;
      room.generateSubtree(2);
      room.printSubtree(0);
    }

    std::cout << "allocs: " << allocs << std::endl;
    std::cout << "frees: " << frees << std::endl;
    return 0;
}
