#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 400
#define NUM_ORBITALS 40
#define NUM_RINGS 20
#define RINGS_DISTANCE 20
#define CIRCLE_RADIUS 5
#define RGB_to_HEX(R,G,B) ((R<<16) | (G<<8) | B)

const float DegToRad = M_PI/180;
const int VectorXOfsset = WINDOW_WIDTH>>1;
const int VectorYOfsset = WINDOW_HEIGHT>>1;

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
  
  Vector2 orbitals[NUM_RINGS][NUM_ORBITALS];
  Vector2 offsets[NUM_RINGS];

  for (int ring = 0, offset = 0; ring<NUM_RINGS; ring++, offset+=RINGS_DISTANCE) {
    offsets[ring].x = 100 + offset;
    offsets[ring].y = 0;
      
    for (int orbital = 0; orbital<NUM_ORBITALS; orbital++) {
      orbitals[ring][orbital].x = offsets[ring].x;
      orbitals[ring][orbital].y = offsets[ring].y;
      rotateVector(&offsets[ring], (float)360/NUM_ORBITALS);
    }
  }

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "basic window");
  SetTargetFPS(120);
  srand(time(NULL));

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);

    for (int ring = 0; ring<NUM_RINGS; ring++) { 
      for (int orbital = 0; orbital<NUM_ORBITALS; orbital++) {
        DrawCircle(
          orbitals[ring][orbital].x + VectorXOfsset,
          orbitals[ring][orbital].y + VectorYOfsset,
          CIRCLE_RADIUS,
          GetColor(RGB_to_HEX(rand()%256, rand()%256, rand()%256))
        );
        rotateVector(&orbitals[ring][orbital], 1);
      }
    }

    DrawCircle(VectorXOfsset, VectorYOfsset, 5, RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
