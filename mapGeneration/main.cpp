#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <raylib.h>
#include <cmath>

#define ROUNDM(n,m)(floor((float)(n+m-1)/m)*m)
#define WindowWidth 1000
#define TileWidth 15
#define NumRooms 100
#define SpawnRadius 250

constexpr int HalfWindow = WindowWidth>>1;
constexpr int MinTileWidth = TileWidth*3;
constexpr int MaxTileWidth = TileWidth*10;


 
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
  double u;

  for (int i=0; i<NumRooms; i++) {
    radius = SpawnRadius * sqrt(real_dis(gen));
    theta = real_dis(gen) * 2 * M_PI;

    rooms[i] = (Rectangle*) malloc(sizeof(Rectangle));
    rooms[i]->x = centerX + ROUNDM(radius * cos(theta), TileWidth);
    rooms[i]->y = centerY + ROUNDM(radius * sin(theta), TileWidth);
    rooms[i]->width  = ROUNDM(int_dis(gen), TileWidth);
    rooms[i]->height = ROUNDM(int_dis(gen), TileWidth);
  }
}

int main(void) {

  InitWindow(WindowWidth, WindowWidth, "Window Title");
  SetTargetFPS(10);
  DrawFPS(20, 20);

  Rectangle* rooms[NumRooms];

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(20, 20);

    GenerateRooms(rooms, HalfWindow, HalfWindow);

    for(Rectangle* room : rooms) {
      //DrawRectangle(room->x, room->y, room->width, room->height, BLUE);
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
