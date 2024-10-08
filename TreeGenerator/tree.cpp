#include <iostream>
#include <random>
#include <algorithm>
#include "tree.hpp"

std::uniform_int_distribution<int> Node::distribution(1, 4);
std::mt19937 Node::rng(std::random_device{}());


void Node::generateSubtree(int maxDepth) {
  int entry {0};

    // As the root room of the tree, generates 4 rooms and 
    // creates a connection to each of those rooms. Then 
    // generates the corresponding random subtree of rooms.
    //
    // A normal room can have [0-4] connections (including)
    // its parent room connection, but the root room has
    // always 4 connections.

    for(auto& link : this->links) {
      Entry childEntry {getSymetric((Entry)entry)};
      Node* child {new Node()};

      child->addParentConnection(childEntry, this, (Entry)entry);
      this->addConnection((Entry)entry, child, childEntry);
      
      child->generateSubtree(1, maxDepth);
      ++entry;
    }
  }

void Node::generateSubtree(int depth, int maxDepth) {

  // A non-root room has always one connection used to connect 
  // itself with its parent. The idea here its to get a random 
  // number of unused doors (places to stablish a connection) 
  // and create connection to new rooms. 
    
  Entry unusedLinks[FREE_LINKS] = { UNSET, UNSET, UNSET };
  int doors {0};

  for (int i {0}; i < LINKS; ++i) {
    if (this->links[i].dstRoom == nullptr) {
      unusedLinks[doors++] = (Entry)i;
    }
  }

  const int randLinks {std::min(doors, distribution(rng))};
  if(randLinks == 0) { return; }
  std::shuffle(std::begin(unusedLinks), std::end(unusedLinks), rng);

  for (int i {0}; i < randLinks; ++i) {
    Entry iterEntry {unusedLinks[i]};
    Entry childEntry {getSymetric(iterEntry)};
    Node* child {new Node()};

    child->addParentConnection(childEntry, this, iterEntry);
    this->addConnection(iterEntry, child, childEntry);

    if((depth + 1) < maxDepth){
      child->generateSubtree(depth + 1, maxDepth);
    }
  }
} 

void Node::destroySubtree(void) {
  for (auto& link : this->links) {
    if (link.dstRoom != nullptr && !link.isParent) {
      link.dstRoom->destroySubtree();
      delete link.dstRoom;
      link.dstRoom = nullptr;
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
    if (link.dstRoom == nullptr) {
      std::cout << fmt
        << "[" << port << "] = @null"
        << std::endl;
      
    } else {
      std::cout << fmt 
        << "[" << port << "] = @"
        << (unsigned long long)link.dstRoom
        << std::endl;
    }
    ++port;
  }

  for (auto& link : this->links) {
    if (link.dstRoom != nullptr && !link.isParent) {
      link.dstRoom->printSubtree(depth + 1);
    }
  }
}
