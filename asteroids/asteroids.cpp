#include <raylib.h>

struct Player {
  Vector2 pos;
  Vector2 vel;
  float rot;
} player;

void DrawPlayer(const Vector2 position) {
  Vector2 p1, p2, p3, p4;
  //
  //      position
  //
  //       p3  p4 
  //   p1          p2
  //
 
  // Both sides
  p1 = position;
  p1.x -= 25;
  p1.y += 50;
  p2 = p1;
  p2.x += 50;

  // Inner points
  p3 = p1;
  p3.x += 15;
  p3.y -= 10;
  p4 = p2;
  p4.x -= 15;
  p4.y -= 10;

  DrawLineEx(position, p1, 3.5f, WHITE);
  DrawLineEx(position, p2, 3.5f, WHITE);
  DrawLineEx(p1, p3,  3.5f, WHITE);
  DrawLineEx(p2, p4,  3.5f, WHITE); 
  DrawLineEx(p3, p4,  3.5f, WHITE);
}



int main(void) {
  InitWindow(1280, 720, "Window Title");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    player.pos = Vector2{100,100};
    DrawPlayer(player.pos);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
