
#include <raylib.h>

/* Player movement */
#define PLAYER_LERP  0.1f
#define PLAYER_SPEED 6

/* Player sprite settings */
#define BODY_COLOR (Color){17,17,17,255}
#define EYES_COLOR (Color){239,239,239,255}
#define HAT1_COLOR (Color){130,90,90,255}
#define HAT2_COLOR (Color){159,98,98,255}
#define HAT3_COLOR (Color){152,120,120,255}
static float PlayerWidth  = 90;
static float PlayerHeight = 75;
static float EyeWidth  = 15;
static float EyeHeight = 15;
static float EyeOffset = 20;
static float HatHeight = 35;

class Player {
  
public: 
  /* Sprite shapes */
  Rectangle rightEye;
  Rectangle leftEye;
  Rectangle body;
  Rectangle hat1;
  Rectangle hat2;
  Rectangle hat3;
  /* Movement */
  float tPosx;
  float tPosy;
};


