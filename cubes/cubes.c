#include <raylib.h>
#define CUBE_SIZE 2

int main(int argc, char *argv[]) {
  
  Camera3D camera = {
    .position = {0,0, CUBE_SIZE},
    .target = {0,0,0,},
    .up = {0,1,0},
    .fovy = 90,
    .projection = CAMERA_PERSPECTIVE
  };

  Vector3 position = {
    .x = ((float)-CUBE_SIZE)/2,
    .y = ((float)-CUBE_SIZE)/2,
    .z = ((float)-CUBE_SIZE)/2
  };
  
  InitWindow(800, 600, "3D graphics");
  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0x181818AA));
      
    BeginMode3D(camera);
    DrawCube(position, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RAYWHITE);
    EndMode3D();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
