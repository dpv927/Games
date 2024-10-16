#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <raylib.h>
#include "tree.hpp"
#include "entry.hpp"

std::uniform_int_distribution<int> Node::distribution(1, 3);
std::mt19937 Node::rng(std::random_device{}());


inline void Node::addConnection(Entry src_entry, Node* dst_room, Entry dst_entry, Link::LinkType link_type) {
  auto& connection = this->links[src_entry];
  connection.link_type = link_type;
  connection.dst_room = dst_room;
  connection.dst_entry = dst_entry;
}

void Node::generateSubtree(int max_depth) {
  std::vector<Node*> nodes;
  nodes.reserve(max_depth * 5);
  int entry {0};

  // As the root room of the tree, generates 4 rooms and 
  // creates a connection to each of those rooms. Then 
  // generates the corresponding random subtree of rooms.
  //
  // A normal room can have [0-4] connections (including)
  // its parent room connection, but the root room has
  // always 4 connections.
  nodes.push_back(this);

  for(auto& link : this->links) {
    Entry iterEntry {(Entry)entry};
    Entry childEntry {getSymetric(iterEntry)};

    std::pair<int,int> offset = getOffset(iterEntry);
    Node* child {new Node(this->x + offset.first, this->y + offset.second)};

    child->addConnection(childEntry, this, iterEntry, Link::LinkType::PARENT);
    this->addConnection(iterEntry, child, childEntry, Link::LinkType::CHILD);
    nodes.push_back(child);
    ++entry;
  }

  for(auto& link : this->links) {
    link.dst_room->generateSubtree(1, max_depth, nodes);
  }
}

void Node::generateSubtree(int depth, int max_depth, std::vector<Node*>& nodes) {

  // A non-root room has always one connection used to connect 
  // itself with its parent. The idea here its to get a random 
  // number of unused doors (places to stablish a connection) 
  // and create connection to new rooms. 
  std::vector<Entry> unusedLinks(FREE_LINKS);
  int doors {0};

  for(int i = 0; i < LINKS; ++i) {
    if(this->links[i].dst_room == nullptr) {
      unusedLinks.push_back((Entry)i);
      ++doors;
    }
  }

  const int randLinks {std::min(doors, distribution(rng))};
  std::shuffle(unusedLinks.begin(), unusedLinks.end(), rng);
  
  for (int i {0}; i < randLinks; ++i) {
    Entry iterEntry {unusedLinks[i]};
    Entry childEntry {getSymetric(iterEntry)};

    std::pair<int,int> offset = getOffset(iterEntry);
    offset.first += this->x;
    offset.second += this->y;

    for(auto& node : nodes) {
      if(node->x == offset.first && node->y == offset.second) {
        // In case we found an already exsistent node in the 
        // target coordinates, abort the creation of a new node.
        // https://www.youtube.com/watch?v=8WVBT7FrgJI
        return;
      }
    }

    // Only create a new node if there are not any other nodes 
    // at the target coordinates.
    Node* child = new Node(offset.first, offset.second);
    nodes.push_back(child);

    child->addConnection(childEntry, this, iterEntry, Link::LinkType::PARENT);
    this->addConnection(iterEntry, child, childEntry, Link::LinkType::CHILD);

    if((depth + 1) < max_depth){
      child->generateSubtree(depth + 1, max_depth, nodes);
    }
  }
}

void Node::destroySubtree(void) {
  for (auto& link : this->links) {
    if (link.dst_room != nullptr && (link.link_type == Link::LinkType::CHILD)) {
      link.dst_room->destroySubtree();
      delete link.dst_room;
      link.dst_room = nullptr;
    }
  }
}

void Node::printSubtree(int depth) {
  std::string fmt;
  int port = 0;

  for (int i = 0; i < depth; i++)
    fmt += "\t";

  std::cout << fmt 
    << "\033[1m\033[32m<@" << (unsigned long long) this
    << ">\033[0m" << std::endl;
       
  for (auto& link : this->links) {
    if (link.dst_room == nullptr) {
      std::cout << fmt
        << "[" << port << "] = @null"
        << std::endl;
      
    } else {
      std::cout << fmt 
        << "[" << port << "] = @"
        << (unsigned long long)link.dst_room
        << std::endl;
    }
    ++port;
  }

  for (auto& link : this->links) {
    if (link.dst_room != nullptr && (link.link_type == Link::LinkType::CHILD)) {
      link.dst_room->printSubtree(depth + 1);
    }
  }
}


const int RoomDim = 100;
constexpr const int RoomDimH = RoomDim >> 1;
constexpr const int RoomDimD = RoomDim << 1;
const int LineThickness = 10.0;

void Node::drawSubtree(void) { 

  int x = this->x * RoomDimD;
  int y = this->y * RoomDimD;

  Vector2 src;
  Vector2 dst;
  src.x = x + RoomDimH;
  src.y = y + RoomDimH;

  for (auto& link : this->links) {
    if (link.dst_room != nullptr && (link.link_type == Link::LinkType::CHILD)) {
      dst.x = (link.dst_room->x * RoomDimD) + RoomDimH;
      dst.y = (link.dst_room->y * RoomDimD) + RoomDimH;
      
      DrawLineEx(src, dst, LineThickness, WHITE);
      link.dst_room->drawSubtree();
    }
  }

  DrawRectangleLines(x, y, RoomDim, RoomDim, WHITE);
}
