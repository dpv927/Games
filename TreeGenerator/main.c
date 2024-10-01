#include "room_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(void) {
  room_node root = new_root();
  assert(root.links);
  srand(time(NULL));

  if(generate_subtree(&root, 10))
    printf("There was an allocating problem"
        " at generate_subtree!");
  destroy_subtree(&root);
}
