#include <cmath>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <cstdlib>
#include <ctime>

const int NumPoints   = 100;
const int WindowWidth = 2000;
const int MiddleW     = WindowWidth>>1; 
const int demoFPS     = 10; 
const int TileWidth   = 20;
const int SpawnRadius = 20 * TileWidth;

#define genRandom()  ((float)std::rand()/RAND_MAX)
#define aproxPoint(n) (round((float)n/TileWidth)*TileWidth)

void GeneratePoints(Vector2 points[]) {
  for (int i=0; i<NumPoints; i++) {
    float r = SpawnRadius * sqrt(genRandom());
    float theta = genRandom()*2.0f*M_PI;

    points[i].x = r*cos(theta) + MiddleW;
    points[i].y = r*sin(theta) + MiddleW;

    float x = points[i].x;
    float y = points[i].y;

    points[i].x = aproxPoint(points[i].x);
    points[i].y = aproxPoint(points[i].y);

    std::cout << "(" << x << "," << y << ")" << " -> "
      << "(" << aproxPoint(x) << "," << aproxPoint(y) << ")"
      << std::endl;
    }
}

void DrawGrid(void) {
  for (int i=MiddleW; i<WindowWidth; i+=TileWidth) {
    DrawLine(i, 0, i, WindowWidth, BLACK);
    DrawLine(0, i, WindowWidth, i, BLACK);
  }

  for (int i=MiddleW; i>=0; i-=TileWidth) {
    DrawLine(i, 0, i, WindowWidth, BLACK);
    DrawLine(0, i, WindowWidth, i, BLACK);
  }
}

void DrawAllPoints(Vector2 points[]) {
  for (int i=0; i<NumPoints; i++)
    DrawCircle(points[i].x, points[i].y, 5, BLACK);
}

int main(void) {

  InitWindow(WindowWidth, WindowWidth, "Window Title");
  SetTargetFPS(demoFPS);

  Vector2 points[NumPoints];
  std::srand(std::time(0));

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    GeneratePoints(points);
    DrawAllPoints(points);
    DrawGrid();

    // Draw axis and the circle
    DrawLine(MiddleW, 0, MiddleW, WindowWidth, RED);
    DrawLine(0, MiddleW, WindowWidth, MiddleW, RED);
    DrawCircleLines(MiddleW, MiddleW, SpawnRadius, BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
