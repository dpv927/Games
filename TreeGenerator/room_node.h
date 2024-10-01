#ifndef _H_ROOM_NODE
#define _H_ROOM_NODE

#include <stdint.h>

typedef struct room_node 
  room_node;

struct room_node {
  room_node** links;
  unsigned char num_links;
};

room_node new_root();
uint8_t generate_subtree(room_node* node, uint32_t depth);
void destroy_subtree(room_node* node);

#endif
