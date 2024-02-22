#include <math.h>
#include <raylib.h>
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800
#define NUM_ORBITALS 4

typedef struct {
  int x;
  int y;
  int radius;
} Circle;

static const float DegToRad = M_PI/180;

void rotateVector(Vector2* vec, float deg) {
  float radians, cos_rad, sin_rad;
  float vec_x, vec_y;

  radians = deg * DegToRad;
  cos_rad = cosf(radians);
  sin_rad = sinf(radians);

  vec_x = vec->x;
  vec_y = vec->y;

  float prime_x = vec_x * cos_rad - vec_y * sin_rad;
  float prime_y = vec_x * sin_rad + vec_y * cos_rad;
  vec->x = prime_x;
  vec->y = prime_y;
}

int main(void) {
  
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "basic window");
  SetTargetFPS(60);

  Vector2 center = {
    .x = WINDOW_WIDTH>>1,
    .y = (WINDOW_HEIGHT>>1)+100,
  };

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw the center circle
    DrawCircle(center.x, center.y, 10, RAYWHITE);
    rotateVector(&center, 1);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
