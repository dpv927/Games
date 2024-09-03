#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include "TinyKeep/engine.hpp"
#include "TinyKeep/graph.hpp"
#include "TinyKeep/room.hpp"

const uint16_t RoomWidthMin   {2};
const uint16_t RoomWidthMax   {11};
const uint16_t RoomHeightMin  {2};
const uint16_t RoomHeightMax  {11};
const uint16_t TileWidth      {20};
const uint32_t NumRooms       {200};
const uint32_t SpawnRadius    {20 * TileWidth};
const float MainRoomThreshold {1.25};
const float WindowWidthRatio  {0.6};
const float WindowHeightRatio {0.8};

int main(void) {

  InitWindow(0, 0, "Map Generation");
  SetTargetFPS(60);
  std::srand(std::time(NULL));
  
  int window_middle_x;
  int window_middle_y;

  { // Scale the window size to the user's 
    // monitor resolution.
    const int m  = GetCurrentMonitor();
    const int mw = GetMonitorWidth(m);
    const int mh = GetMonitorHeight(m);
    const int ww = mw * WindowWidthRatio;
    const int wh = mh * WindowHeightRatio;
    window_middle_x = ww >> 1;
    window_middle_y = wh >> 1;

    SetWindowSize(ww, wh);
    SetWindowPosition((mw - ww)/2.0, (mh - wh)/2.0);
  }

  TinyKeep::Engine* engine = TinyKeep::Engine::getInstance();
  engine->generateRooms(
      RoomWidthMin,
      RoomWidthMax,
      RoomHeightMin,
      RoomHeightMax,
      window_middle_x,
      window_middle_y,
      TileWidth,
      NumRooms,
      SpawnRadius);

  engine->separateRooms(TileWidth);
  engine->selectRooms(MainRoomThreshold);
  auto graph = Graph::calculate_graph(engine->rooms);

  Camera2D camera;
  camera.offset = {0,0};
  camera.target = {0,0};
  camera.rotation = 0;
  camera.zoom = 1;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Move the camera 
    if(IsKeyDown(KEY_W))
      camera.target.y-=25;
    if(IsKeyDown(KEY_S))
      camera.target.y+=25;
    if(IsKeyDown(KEY_D))
      camera.target.x+=25;
    if(IsKeyDown(KEY_A))
      camera.target.x-=25;
    BeginMode2D(camera);

    for (TinyKeep::Room& room : engine->rooms)
      room.drawRoom(TileWidth);
    
    for(auto& edge : graph) {
      TinyKeep::Room* u = engine->main_rooms[edge.u];
      TinyKeep::Room* v = engine->main_rooms[edge.v];

      float u_x = u->x + (u->width)/2.0;
      float u_y = u->y + (u->height)/2.0;
      float v_x = v->x + (v->width)/2.0;
      float v_y = v->y + (v->height)/2.0; 
      DrawLineEx(Vector2{u_x, u_y}, Vector2{v_x, v_y}, 5, GREEN);
    }

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
