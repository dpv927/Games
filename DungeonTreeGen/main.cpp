#include <algorithm>
#include <raylib.h>
#include <iostream>
#include "tree.hpp"

int main(void) {
  Node room;
  auto nodes = room.generate_subtree(10);
  // room.printSubtree(0);

  // The 'nodes' vector contains pointers to all of the 
  // generated nodes at the connection tree.
  //
  // Here, from all the nodes, filter only the nodes at 
  // the max depth (at the bottom of the tree).
  for(auto it = nodes.begin(); it != nodes.end(); ++it) {
    if((*it)->depth != Node::max_gen_depth) {
      it = nodes.erase(it);
      --it;
    }  
  }

  // Shuffle the max depth nodes and select 15% of them
  // as boss rooms. 
  std::mt19937 rng(std::random_device{}());
  std::shuffle(nodes.begin(), nodes.end(), rng);

  for(int i = 0; i < std::round(nodes.size() * 0.15); ++i) {
    nodes[i]->node_type = Node::NodeType::BOSS;
  }


  InitWindow(1500, 1500, "Tree generation");
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_ERROR);

  Camera2D camera = {
    .offset = {750.0f,750.0f},
    .target = {0.0f, 0.0f},
    .rotation = 0.0f,
    .zoom = 1.f,
  };

  while(!WindowShouldClose()) {

    if(IsKeyDown(KEY_W)) { camera.target.y -= 25.; }
    if(IsKeyDown(KEY_S)) { camera.target.y += 25.; }
    if(IsKeyDown(KEY_D)) { camera.target.x += 25.; }
    if(IsKeyDown(KEY_A)) { camera.target.x -= 25.; }
    switch(static_cast<int>(GetMouseWheelMove())) {
      case 1: 
        camera.zoom += 0.2;
        break;
      case -1:
        camera.zoom -= 0.2;
        break;
      default: 
        break;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    room.draw_subtree();
    DrawRectangle(0, 0, 40, 40, PINK);
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
