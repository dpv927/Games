#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include "TinyKeep/engine.hpp"

const int NumRooms    = 100;
const int WindowWidth = 2000;
const int MiddleW     = WindowWidth>>1; 
const int demoFPS     = 10; 
const int TileWidth   = 20;
const int SpawnRadius = 20 * TileWidth;

int main(void) {

  InitWindow(WindowWidth, WindowWidth, "Window Title");
  SetTargetFPS(demoFPS);
  std::srand(std::time(NULL));

  // Init the engine
  TinyKeep::Room rooms[NumRooms];
  TinyKeep::Engine engine;
  engine.setOrigin(MiddleW, MiddleW);
  engine.setNumRooms(NumRooms);
  engine.setTileWidth(TileWidth);
  engine.setSpawnRadius(SpawnRadius);

  // Create a 2D Camera
  Camera2D camera;
  camera.offset = {0,0};
  camera.target = {0,0};
  camera.rotation = 0;
  camera.zoom = 1;

  engine.generateRooms(rooms);
    
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    /* Move the camera */
    if(IsKeyDown(KEY_W))
      camera.target.y-=50;
    if(IsKeyDown(KEY_S))
      camera.target.y+=50;
    if(IsKeyDown(KEY_D))
      camera.target.x+=50;
    if(IsKeyDown(KEY_A))
      camera.target.x-=50;
    BeginMode2D(camera);

    engine.separateRooms(rooms);

    for (TinyKeep::Room room : rooms) {
      room.drawRoom(TileWidth);
    }

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
