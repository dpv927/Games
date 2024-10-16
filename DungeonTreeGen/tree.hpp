#ifndef _H_TREE
#define _H_TREE

#include <random>
#include <vector>
#include "entry.hpp"

#define FREE_LINKS 3
#define LINKS 4

struct Node {
  
  struct Link {
    
    Node* dst_room;
    Entry dst_entry;
    
    enum LinkType {
      UNSET_LINK,
      CHILD,
      PARENT,
    } link_type;

    Link() : 
      dst_room(nullptr),
      dst_entry(UNSET),
      link_type(UNSET_LINK) {}
  };

  Link links[LINKS];
  int x;
  int y;

  Node() : x(0), y(0) {}
  ~Node() { destroySubtree(); }

  void generateSubtree(int max_depth);
  void destroySubtree(void);
  void printSubtree(int depth);
  void drawSubtree(void);

private:
  Node(int x, int y) : x(x), y(y) {}
  
  void generateSubtree(int depth, int max_depth, std::vector<Node*>& nodes);
  inline void addConnection(Entry src_entry, Node* dst_room, Entry dst_entry, Link::LinkType link_type);
  
  static std::uniform_int_distribution<int> distribution;
  static std::mt19937 rng;
};

#endif
