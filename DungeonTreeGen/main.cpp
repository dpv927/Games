#include <raylib.h>
#include "tree.hpp"

int main(void) {
  Node room;
  room.generateSubtree(5);
  room.printSubtree(0);

  InitWindow(1500, 1500, "Tree generation");
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_ERROR);

  Camera2D camera = {
    .offset = {750.,750.},
    .target = {0.,0.},
    .rotation = 0.,
    .zoom = 1.,
  };

  while(!WindowShouldClose()) {

    if(IsKeyDown(KEY_W)) { camera.target.y -= 25.; }
    if(IsKeyDown(KEY_S)) { camera.target.y += 25.; }
    if(IsKeyDown(KEY_D)) { camera.target.x += 25.; }
    if(IsKeyDown(KEY_A)) { camera.target.x -= 25.; }

    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(BLACK);
    room.drawSubtree(&room);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
