#ifndef _H_TREE
#define _H_TREE

#include <random>
#include "entry.hpp"

#define FREE_LINKS 3
#define LINKS 4

class Node {
  
  struct Link {
    Node* dstRoom;
    Entry dstEntry;
    bool isParent;

    Link() : 
      dstRoom(nullptr),
      dstEntry(UNSET),
      isParent(false) {}
  };

public:
  Link links[LINKS];
  int x;
  int y;

  Node() : x(0), y(0) {}
  ~Node() { destroySubtree(); }

  void generateSubtree(int maxDepth);
  void destroySubtree(void);
  void printSubtree(int depth);

private:
  inline void addParentConnection(Entry srcEntry, Node* dstRoom, Entry dstEntry) {
    auto& connection = this->links[srcEntry];
    connection.dstRoom = dstRoom;
    connection.dstEntry = dstEntry;
    connection.isParent = true;
  }

  inline void addConnection(Entry srcEntry, Node* dstRoom, Entry dstEntry) {
    auto& connection = this->links[srcEntry];
    connection.dstRoom = dstRoom;
    connection.dstEntry = dstEntry;
    connection.isParent = false;
  }


  void generateSubtree(int depth, int maxDepth);
  static std::uniform_int_distribution<int> distribution;
  static std::mt19937 rng;
};

#endif
