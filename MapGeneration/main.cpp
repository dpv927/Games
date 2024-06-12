#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <vector>
#include "TinyKeep/engine.hpp"
#include "TinyKeep/room.hpp"

const int NumRooms    {100};
const int WindowWidth {2000};
const int MiddleW     {WindowWidth>>1}; 
const int demoFPS     {60}; 
const int TileWidth   {20};
const int SpawnRadius {20 * TileWidth};

int main(void) {

  InitWindow(WindowWidth, WindowWidth, "");
  SetTargetFPS(demoFPS);
  std::srand(std::time(NULL));

  // Init the engine 
  std::vector<TinyKeep::Room> rooms(NumRooms);
  TinyKeep::Engine* engine = TinyKeep::Engine::getInstance()
    ->setOrigin(MiddleW, MiddleW)
    ->setNumRooms(NumRooms)
    ->setTileWidth(TileWidth)
    ->setSpawnRadius(SpawnRadius)
    ->setRoomMaxTilesWidth(11)
    ->setRoomMinTilesWidth(2)
    ->setRoomMaxTilesHeight(11)
    ->setRoomMinTilesHeight(2);

  // Create a 2D Camera
  Camera2D camera;
  camera.offset = {0,0};
  camera.target = {0,0};
  camera.rotation = 0;
  camera.zoom = 1;

  engine->generateRooms(rooms);
  while(engine->separateRooms(rooms));
  engine->selectRooms(rooms, 1.25f);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    /* Move the camera */
    if(IsKeyDown(KEY_W))
      camera.target.y-=25;
    if(IsKeyDown(KEY_S))
      camera.target.y+=25;
    if(IsKeyDown(KEY_D))
      camera.target.x+=25;
    if(IsKeyDown(KEY_A))
      camera.target.x-=25;
    BeginMode2D(camera);

    for (TinyKeep::Room room : rooms) {
      room.drawRoom(TileWidth);
    }

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
