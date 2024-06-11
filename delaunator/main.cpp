#include "delaunator.hpp"
#include "cstdio"
#include <cstddef>
extern "C" {
  #include <raylib.h>
}

int main(void) {

  InitWindow(800, 800, "Window Title");
  SetTargetFPS(60);

  std::vector<double> coords = {
    158, 165,
    576, 101,
    457, 289,
    142, 587,
    419, 701,
    607, 523,
    448, 478
  };

  delaunator::Delaunator d(coords);
  for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
    printf(
      "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
      d.coords[2 * d.triangles[i]],        // V1x
      d.coords[2 * d.triangles[i] + 1],    // V1y
      d.coords[2 * d.triangles[i + 1]],    // V2x
      d.coords[2 * d.triangles[i + 1] + 1],// V2y
      d.coords[2 * d.triangles[i + 2]],    // V3x
      d.coords[2 * d.triangles[i + 2] + 1] // V3y
    );
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    // Draw All the points
    for(std::size_t i = 0; i<coords.size(); i+=2) {
      DrawCircle(coords[i], coords[i+1], 5, BLACK);
    }
    
    // Draw all the vertices
    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
      DrawLine( // Draw line from vertex V1 to vertex V2 
        d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1],
        d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1],
        GREEN);
      DrawLine( // Draw line from vertex V1 to vertex V3 
        d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1],
        d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1],
        GREEN);
      DrawLine( // Draw line from vertex V2 to vertex V3 
        d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1],
        d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1],
        GREEN);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
