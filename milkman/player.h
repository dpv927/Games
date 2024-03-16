#ifndef _PLAYER_H
#define _PLAYER_H
#include <raylib.h>

/* Player movement settings */
#define PLAYER_LERP   0.1f
#define PLAYER_SPEED  6
        
/** Player Display Settings **/
#define BODY_COLOR (Color){17,17,17,255}
#define EYES_COLOR (Color){239,239,239,255}
#define HAT1_COLOR (Color){130,90,90,255}
#define HAT2_COLOR (Color){159,98,98,255}
#define HAT3_COLOR (Color){152,120,120,255}

struct Player {
  /* Sprite things */
  Rectangle rightEye;
  Rectangle leftEye;
  Rectangle body;
  Rectangle hat1;
  Rectangle hat2;
  Rectangle hat3;
  /* Motion */
  float tPosx;
  float tPosy;
};

void ApplyPropiertiesScale(float scale);
void InitializePlayer(struct Player* player);
void ApplyPlayerPosition(struct Player* player);
void MovePlayer(struct Player* player);
void DrawPlayer(struct Player player);

#endif // ifndef _PLAYER_H
