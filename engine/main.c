#include <raylib.h>

int main(void) {

  InitWindow(800, 600, "Window Title");
  SetTargetFPS(60);
  
  Camera3D camera = {
    .position = {30,10,0} ,
    .target = {0,0,0},
    .up = {0,1,0},
    .fovy = 89,
    .projection = CAMERA_PERSPECTIVE
  };
    
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(TextFormat("Position X: %i", (int)camera.position.x), 10, 10, 18, BLACK);
    DrawText(TextFormat("Position Y: %i", (int)camera.position.y), 10, 30, 18, BLACK);
    DrawText(TextFormat("Position Z: %i", (int)camera.position.z), 10, 50, 18, BLACK);

    if(IsKeyDown(KEY_DOWN)) 
      camera.position.y -= 1;
    else if(IsKeyDown(KEY_UP))
      camera.position.y += 1;
    else if(IsKeyDown(KEY_RIGHT))
      camera.position.x += 1;
    else if(IsKeyDown(KEY_LEFT))
      camera.position.x -= 1;
    else if(IsKeyDown(KEY_W))
      camera.position.z -= 1;
    else if(IsKeyDown(KEY_S))
      camera.position.z += 1;
    BeginMode3D(camera);

    DrawGrid(100, 10);
    DrawCylinder((Vector3){0,0,0}, 4, 4, 10, 360, BLACK);
    DrawCylinder((Vector3){0,10,0}, 10, 10, 10, 360, BLACK);
    

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
