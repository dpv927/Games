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

  static int max_gen_depth;
  Link links[LINKS];
  int depth;
  int x;
  int y;

  enum NodeType {
    BOSS,
    NORMAL,
  } node_type;

  Node() : x(0), y(0), depth(0), node_type(NORMAL) {}
  ~Node() { this->destroy_subtree(); }

  std::vector<Node*> generate_subtree(int max_depth);
  void destroy_subtree(void);
  void print_subtree(int depth);
  void draw_subtree(void);

private:

  Node(int x, int y, int depth) : x(x), y(y), depth(depth), node_type(NORMAL) {
    if(depth > Node::max_gen_depth) {
      Node::max_gen_depth = depth;
    }
  }

  inline void add_connection(Entry src_entry, Node* dst_room, Entry dst_entry, Link::LinkType link_type);
  void generate_subtree(int depth, int max_depth, std::vector<Node*>& nodes);
  
  static std::uniform_int_distribution<int> distribution;
  static std::mt19937 rng;
};

#endif
