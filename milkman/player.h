#ifndef _PLAYER_H
#define _PLAYER_H

#include <raylib.h>

struct Player {
  /* Sprite things */
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

void ApplyConstantsScale(float scale);
void InitializePlayer(struct Player* player);
void MovePlayer(struct Player* player);
void DrawPlayer(struct Player player);

#endif // ndef _PLAYER_H
