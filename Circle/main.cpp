#include <cmath>
#include <raylib.h>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

static const int SpawnRadius = 200; // px
static const int NumPoints   = 10;
static const int WindowWidth = 800;
static const int MiddleW     = WindowWidth>>1; 
static const int demoFPS     = 10; 

float randomGen() {
  return (float)std::rand()/RAND_MAX;
}

int main(void) {

  InitWindow(WindowWidth, WindowWidth, "Window Title");
  SetTargetFPS(demoFPS);

  Vector2 points[NumPoints];
  std::srand(std::time(0));

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i=0; i<NumPoints; i++) {
      float r = SpawnRadius * sqrt(randomGen());
      float theta = randomGen()*2.0f*M_PI;

      points[i].x = r*cos(theta) + MiddleW;
      points[i].y = r*sin(theta) + MiddleW;
      DrawRectangleLines(points[i].x, points[i].y, 20, 20, BLACK);
    }

    DrawCircleLines(MiddleW, MiddleW, SpawnRadius, BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
