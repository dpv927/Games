#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <ostream>
#include <random>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>

#define ROUNDM(n,m)(round((float)n/m)*m)
#define GET_RAND() ((float)rand()/(float)RAND_MAX)

#define WINDOW_DIM  2000 /* Window width and height */
#define MAX_ROOM_WH 11   /* Room max width and height number of tiles */
#define MIN_ROOM_WH 2    /* Room min width and height number of tiles */
#define TILE_W      24   /* Width of a tile in pixels */
#define NumRooms    20   /* Number of rooms to generate */
#define SPAWN_RAD   32   /* Room spawn circle radius in pixels */


void DrawRoom(Rectangle* room);
void GenerateRooms(Rectangle* rooms[], int centerX, int centerY);
// bool IsAnyRoomOverlapped(Rectangle* rooms[]);
// void SeparateRooms(Rectangle* rooms[]);


// Generates a bunch of rooms within a circle area.
// centerX and centerY are the circle center coordinates
//

void GenerateRooms(Rectangle* rooms[], int centerX, int centerY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> real_dis(0, 1);

    double radius;
    double theta;

    for (int i = 0; i < NumRooms; i++) {
        theta = 2 * M_PI * real_dis(gen);
        radius = sqrt(real_dis(gen)) * SPAWN_RAD; // Uso de sqrt para distribución uniforme en el área

        // Crear la habitación
        rooms[i] = (Rectangle*)malloc(sizeof(Rectangle));
        rooms[i]->x = centerX + (radius * cos(theta));
        rooms[i]->y = centerY + (radius * sin(theta));
        rooms[i]->width = TILE_W * (MIN_ROOM_WH + round(real_dis(gen) * (MAX_ROOM_WH - MIN_ROOM_WH)));
        rooms[i]->height = TILE_W * (MIN_ROOM_WH + round(real_dis(gen) * (MAX_ROOM_WH - MIN_ROOM_WH)));

        // Ajustar a la cuadrícula
        rooms[i]->x = ROUNDM(rooms[i]->x, TILE_W);
        rooms[i]->y = ROUNDM(rooms[i]->y, TILE_W);
    }
}
/*
void GenerateRooms(Rectangle* rooms[], int centerX, int centerY) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> real_dis(0,1);
  // srand(time(NULL));

  double radius;
  double theta;
  double rnd;
  
  for (int i=0; i<NumRooms; i++) {
    
    theta = 2 * M_PI * real_dis(gen);
    rnd = real_dis(gen) + real_dis(gen);
    radius = (rnd>1)? 2-rnd : rnd;

    // theta = 2 * M_PI * GET_RAND();
    //rnd = GET_RAND() + GET_RAND();
    // radius = sqrt(GET_RAND()); 
    // radius = (rnd>1)? 2-rnd : rnd;

    // Create the room
    rooms[i] = (Rectangle*) malloc(sizeof(Rectangle));
    rooms[i]->x = centerX + (radius * cos(theta));
        rooms[i]->y = centerY + (radius * sin(theta));
    //rooms[i]->x = ROUNDM((SPAWN_RAD* radius * cos(theta)), TILE_W);
    //rooms[i]->y = ROUNDM((SPAWN_RAD* radius * sin(theta)), TILE_W);
    rooms[i]->width  = MIN_ROOM_WH + round(GET_RAND() * (MAX_ROOM_WH - MIN_ROOM_WH));
    rooms[i]->height = MIN_ROOM_WH + round(GET_RAND() * (MAX_ROOM_WH - MIN_ROOM_WH));

    // Center the room
    //rooms[i]->x = (rooms[i]->x * TILE_W/2.0f);
    //rooms[i]->y = (rooms[i]->y * TILE_W/2.0f);

    // Snap to the grid
    rooms[i]->x = ROUNDM(rooms[i]->x, TILE_W);
    rooms[i]->y = ROUNDM(rooms[i]->y, TILE_W);
  }
}*/

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
        room1.x += round(-direction.x)*TILE_W;
        room1.y += round(-direction.y)*TILE_W;
        room2.x += round(direction.x)*TILE_W;
        room2.y += round(direction.y)*TILE_W;

        *rooms[current] = room1;
        *rooms[other] = room2;
      }
    }
  }while (IsAnyRoomOverlapped(rooms));
}

void DrawRoom(Rectangle* room) {
  int posx = room->x;
  int posy = room->y;

  //for (posx = room->x; posx< (room->x + room->width*TILE_W); posx+=TILE_W)
  //  for (posy = room->y; posy < (room->y + room->height*TILE_W); posy+=TILE_W)
  //    DrawRectangleLines(posx, posy, TILE_W, TILE_W, BLUE);
  DrawRectangle(room->x, room->y, room->width*TILE_W, room->height*TILE_W,BLUE);
  DrawRectangleLines(room->x, room->y, room->width*TILE_W, room->height*TILE_W,WHITE);

  std::cout << "(" << posx << ",";
  std::cout << posy << ")";
}

int main(void) {

  InitWindow(WINDOW_DIM, WINDOW_DIM, "Window Title");
  SetTargetFPS(10);
  DrawFPS(20, 20);

  const int halfWindow = WINDOW_DIM>>1;
  Rectangle* rooms[NumRooms];

  Vector2 target = {0,0};
  Vector2 offset = {0,0};
  Camera2D camera = {
    .offset = offset,
    .target = target,
    .rotation = 0,
    .zoom = 1,
  };

  GenerateRooms(rooms, halfWindow, halfWindow);
  //SeparateRooms(rooms);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(20, 20);

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

    //GenerateRooms(rooms, halfWindow, halfWindow);
    //SeparateRooms(rooms);

    for(Rectangle* room : rooms)
      DrawRoom(room);
    std::cout << std::endl;
    std::cout << std::endl;

    DrawLine(halfWindow, 0, halfWindow, WINDOW_DIM, RED);
    DrawLine(0, halfWindow, WINDOW_DIM, halfWindow, RED);
    DrawCircleLines(0, 0, SPAWN_RAD*TILE_W, RED);

    EndMode2D();
    EndDrawing();
  }

  for(Rectangle* room : rooms) {
    free(room);
  }

  CloseWindow();
  return 0;
}
