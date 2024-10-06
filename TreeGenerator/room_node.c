#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "room_node.h"

uint8_t rnd_links(uint8_t max) {
  return (uint8_t) rand() % (max + 1); 
}

room_node new_root() {
  room_node rn;
  rn.links[0] = NULL;
  rn.links[1] = NULL;
  rn.links[2] = NULL;
  rn.links[4] = NULL;
  return rn;
}

room_node new_node(/*int x, int y*/) {
  uint8_t num_links = rnd_links(3);
  room_node rn;
  
  /* This malloc is handled after calling
   * this function (trust me). */
  rn.links = malloc(sizeof(rn) * num_links);
  rn.num_links = num_links;
  // rn.x = x;
  // rn.y = y;
  return rn;
}

room_node new_leaf(/*int x, int y*/) {
  room_node rn;
  rn.links = NULL;
  rn.num_links = 0;
  // rn.x = x;
  // rn.y = y;
  return rn;
}

uint8_t pgenerate_subtree(room_node* node, uint32_t depth, uint32_t max_depth) {
  room_node** links = node->links;
  room_node* rn;

  if(depth == (max_depth - 1)) {
    
    for(uint8_t _ = 0; _ < node->num_links; _++) {
      if(!(rn = malloc(sizeof(room_node)))) {
        return 1;
      }

      *rn = new_leaf();
      *links = rn;
      ++links;
    }
  } else {

    for(uint8_t _ = 0; _ < node->num_links; _++) {
      uint8_t num_links = rnd_links(3);
      
      if(!(rn = malloc(sizeof(room_node)))) {
        return 1;
      }

      if(!num_links) {
        *rn = new_leaf();
        *links = rn;
        ++links;

      } else {
        *rn = new_node();
        
        // You trusted
        if(!rn->links) {
          return 1;
        }
        
        *links = rn;
        ++links;

        // When detected an error, just return from the 
        // bottom of the tree and end.
        if(pgenerate_subtree(rn, depth + 1, max_depth))
          return 1;
      }
    }
  }
  return 0;
}

uint8_t generate_subtree(room_node* node, uint32_t depth) {
  return pgenerate_subtree(node, 0, depth);
}

void destroy_subtree(room_node* node) {
  for(int i = 0; i < node->num_links; i++) {
    if(node->links[i]) {
      destroy_subtree(node->links[i]);
      free(node->links[i]);
    }
  }
  free(node->links);
}
