#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <raylib.h>
#include <raymath.h>
#include <cmath>

// ------- CONSTANTS DEFINITION ---------
#define ROUNDM(n,m)(floor((float)(n+m-1)/m)*m)
#define WindowWidth 2000
#define TileWidth 15
#define NumRooms 50
#define SpawnRadius 20

constexpr int HalfWindow = WindowWidth>>1;
constexpr int MinTileWidth = TileWidth*3;
constexpr int MaxTileWidth = TileWidth*7;


// -------- FUNCTIONS ----------

void DrawRoom(Rectangle* room) {
  int posx = room->x;
  int posy = room->y;

  for (posx = room->x; posx< (room->x + room->width); posx+=TileWidth) {
    for (posy = room->y; posy < (room->y + room->height); posy+=TileWidth) {
      DrawRectangleLines(posx, posy, TileWidth, TileWidth, BLUE);
    }
  }
}

void GenerateRooms(Rectangle* rooms[], int centerX, int centerY) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> real_dis(0,1);
  std::uniform_int_distribution<> int_dis(MinTileWidth,MaxTileWidth);

  double radius;
  double theta;

  for (int i=0; i<NumRooms; i++) {
    radius = TileWidth * SpawnRadius * sqrt(real_dis(gen));
    theta = real_dis(gen) * 2 * M_PI;

    rooms[i] = (Rectangle*) malloc(sizeof(Rectangle));
    rooms[i]->x = centerX + ROUNDM(radius * cos(theta), TileWidth);
    rooms[i]->y = centerY + ROUNDM(radius * sin(theta), TileWidth);
    rooms[i]->width  = ROUNDM(int_dis(gen), TileWidth);
    rooms[i]->height = ROUNDM(int_dis(gen), TileWidth);
  }
}

bool IsAnyRoomOverlapped(Rectangle* rooms[]) {
  Rectangle room;

  for (int i = 0; i < NumRooms; i++) {
    room = *rooms[i];

    for (int j = 0; j < NumRooms; j++) {
      if(i == j) continue;
      if(CheckCollisionRecs(room, *rooms[j]))
        return true;
    } 
  }
  return false;
}

void SeparateRooms(Rectangle* rooms[]) {
  Vector2 direction;
  Rectangle room1, room2;

  do {
    for (int current = 0; current < NumRooms; current++) {
      room1 = *rooms[current];
      
      for (int other = 0; other < NumRooms; other++) {
        room2 = *rooms[other];

        if(current == other || !CheckCollisionRecs(room1, room2))
          continue; // Same or colliding Rooms
 
        // Get the direction vector between both rooms
        direction.x = (room2.x/2.0f) - (room1.x/2.0f);
        direction.y = (room2.y/2.0f) - (room2.y/2.0f);
        direction = Vector2Normalize(direction);
        
        // Move both rooms in opposite directions
        room1.x += round(-direction.x)*TileWidth;
        room1.y += round(-direction.y)*TileWidth;
        room2.x += round(direction.x)*TileWidth;
        room2.y += round(direction.y)*TileWidth;

        *rooms[current] = room1;
        *rooms[other] = room2;
      }
    }
  }while (IsAnyRoomOverlapped(rooms));
}


int main(void) {

  

  InitWindow(WindowWidth, WindowWidth, "Window Title");
  SetTargetFPS(10);
  DrawFPS(20, 20);

  Rectangle* rooms[NumRooms];
  GenerateRooms(rooms, HalfWindow, HalfWindow);
  SeparateRooms(rooms);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(20, 20);

    for(Rectangle* room : rooms) {
      // DrawRectangleRec(*room, WHITE);
      DrawRoom(room);
      DrawRectangleLines(room->x, room->y, room->width, room->height,WHITE);
    }

    DrawLine(HalfWindow, 0, HalfWindow, WindowWidth, RED);
    DrawLine(0, HalfWindow, WindowWidth, HalfWindow, RED);
    EndDrawing();
  }

  for(Rectangle* room : rooms) {
    free(room);
  }

  CloseWindow();
  return 0;
}
