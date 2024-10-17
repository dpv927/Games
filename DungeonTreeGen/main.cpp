#include <algorithm>
#include <raylib.h>
#include "tree.hpp"

int main(void) {
  Node room;
  auto nodes = room.generateSubtree(10);
  // room.printSubtree(0);

  // Filter only the nodes at the max depth
  for(auto it = nodes.begin(); it != nodes.end(); ++it) {
    if((*it)->depth != Node::max_depth) {
      it = nodes.erase(it);
      --it;
    } else {
      (*it)->node_type = Node::NodeType::MAIN;
    }
  }

  // Randomize the nodes and select some rooms as 
  // boss rooms. TODO select a % of all nodes, not
  // a count.
  std::mt19937 rng(std::random_device{}());
  int selected_nodes {0};
  std::shuffle(nodes.begin(), nodes.end(), rng);
  
  for(auto& node : nodes) {
    if(selected_nodes == 3) { break; }
    node->node_type = Node::NodeType::BOSS;
    ++selected_nodes;
  }


  InitWindow(1500, 1500, "Tree generation");
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_ERROR);

  Camera2D camera = {
    .offset = {500.0f,500.0f},
    .target = {0.0f, 0.0f},
    .rotation = 0.0f,
    .zoom = 1.0f,
  };

  while(!WindowShouldClose()) {

    if(IsKeyDown(KEY_W)) { camera.target.y -= 25.; }
    if(IsKeyDown(KEY_S)) { camera.target.y += 25.; }
    if(IsKeyDown(KEY_D)) { camera.target.x += 25.; }
    if(IsKeyDown(KEY_A)) { camera.target.x -= 25.; }

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    room.drawSubtree();
    DrawRectangle(0, 0, 40, 40, PINK);
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
