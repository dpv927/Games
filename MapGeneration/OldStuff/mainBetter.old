#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <cmath>

const int NumRooms    = 100;
const int WindowWidth = 2000;
const int MiddleW     = WindowWidth>>1; 
const int demoFPS     = 10; 
const int TileWidth   = 10;
const int SpawnRadius = 10 * TileWidth;


#define genRandom() ((float)(std::rand())/(float)(RAND_MAX))
#define genRandomFrom(min,max) (std::rand()%(max - min + 1) + min)
#define aproxCoordinate(n) (round((float)(n)/TileWidth)*TileWidth)


void GenerateRooms(Rectangle rooms[]) {
  float rndRadius;
  float angle;

  for (int i = 0; i < NumRooms; i++) {
    rndRadius = SpawnRadius * sqrt(genRandom());
    angle = genRandom()*2.0f*M_PI;

    rooms[i].x = aproxCoordinate(rndRadius * cos(angle) + MiddleW);
    rooms[i].y = aproxCoordinate(rndRadius * sin(angle) + MiddleW);
    rooms[i].width  = genRandomFrom(2,11) * TileWidth;
    rooms[i].height = genRandomFrom(2,11) * TileWidth;
  }
}

bool separateRooms(Rectangle rooms[]) {
  bool rooms_overlap = false;

  for (int i = 0; i < NumRooms; i++) {
    const float mrw_i = rooms[i].width/2.0f;
    const float mrh_i = rooms[i].height/2.0f;

    for (int j = 0; j < NumRooms; j++) {
      if (i != j && CheckCollisionRecs(rooms[i], rooms[j])) {
        const float mrw_j = rooms[j].width/2.0f;
        const float mrh_j = rooms[j].height/2.0f;

        // Differential betteen both rooms center coordinates
        const float dx = (rooms[j].x + mrw_j) - (rooms[i].x + mrw_i);
        const float dy = (rooms[j].y + mrh_j) - (rooms[i].y + mrh_i);

        // Instead of overlap, they are overlap/2 to avoid doing 
        // the same operation twice at the 'if's below.
        const float overlapX = ((mrw_i + mrw_j) - fabs(dx))/2.0f;
        const float overlapY = ((mrh_i + mrh_j) - fabs(dy))/2.0f;

        if (overlapX < overlapY) {
          if (dx > 0) {
            rooms[i].x -= overlapX;
            rooms[j].x += overlapX;
          } else {
            rooms[i].x += overlapX;
            rooms[j].x -= overlapX;
          }
        } else {
          if (dy > 0) {
            rooms[i].y -= overlapY;
            rooms[j].y += overlapY;
          } else {
            rooms[i].y += overlapY;
            rooms[j].y -= overlapY;
          }
        }

        rooms[i].x = aproxCoordinate(rooms[i].x);
        rooms[i].y = aproxCoordinate(rooms[i].y);
        rooms[j].x = aproxCoordinate(rooms[j].x);
        rooms[j].y = aproxCoordinate(rooms[j].y);
        rooms_overlap = true;
      }
    }
  }
  return rooms_overlap;
}

void DrawRoom(Rectangle& room) {
  for (int posx = room.x; posx< (room.x + room.width); posx+=TileWidth)
    for (int posy = room.y; posy < (room.y + room.height); posy+=TileWidth)
      DrawRectangleLines(posx, posy, TileWidth, TileWidth, BLUE);
  DrawRectangleLines(room.x, room.y, room.width, room.height, WHITE);
}

int main(void) {

  InitWindow(WindowWidth, WindowWidth, "Window Title");
  SetTargetFPS(demoFPS);
  std::srand(std::time(NULL));

  Rectangle rooms[NumRooms];
  Vector2 target = {0,0};
  Vector2 offset = {0,0};
  Camera2D camera = {
    .offset = offset,
    .target = target,
    .rotation = 0,
    .zoom = 1,
  };
  
  GenerateRooms(rooms);
  while(separateRooms(rooms));
  
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

    for(Rectangle room : rooms) {
      DrawRoom(room);
    }

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
