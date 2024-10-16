#include <raylib.h>
#include "tree.hpp"

int main(void) {
  Node room;
  room.generateSubtree(10);
  room.printSubtree(0);

  InitWindow(1500, 1500, "Tree generation");
  SetTargetFPS(60);
  SetTraceLogLevel(LOG_ERROR);

  Camera2D camera = {
    .offset = {750.0f,750.0f},
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
    DrawRectangle(0, 0, 100, 100, PURPLE);
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
