#include <raylib.h>
#define CAMERA_SPEED 5

enum {
  BODY,      // Body IndeX
  LEFT_EYE,  // Left eye index
  RIGHT_EYE, // Right eye index
  HAT_1,     // Hat body index
  HAT_2,     // Hat platform idex
  HAT_3      // Hat band index
};

typedef struct {
  Rectangle sprite[6];
  int x, y;
} Player;

void ManageUserInput(Camera2D *, Player *);
void DrawPlayer(Player *);

int main(void) {
  InitWindow(900, 500, "");
  SetTargetFPS(60);

  Player player;
  player.x = GetScreenWidth() >> 1;
  player.y = GetScreenHeight() >> 1;
  player.sprite[BODY] = (Rectangle){player.x, player.y, 30, 30};

  Camera2D camera;
  camera.offset = (Vector2){0, 0};
  camera.target = (Vector2){0, 0};
  camera.rotation = 0;
  camera.zoom = 1.0f;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    // DrawRectangle(-200, 100, 500, 220, GRAY);
    DrawPlayer(&player);
    ManageUserInput(&camera, &player);

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

/*
void ManageUserInput(Camera2D *c, Rectangle *p) {
  if (IsKeyDown(KEY_W))
    c->target.y -= CAMERA_SPEED;
  else if (IsKeyDown(KEY_S))
    c->target.y += CAMERA_SPEED;
  else if (IsKeyDown(KEY_A))
    c->target.x -= CAMERA_SPEED;
  else if (IsKeyDown(KEY_D))
    c->target.x += CAMERA_SPEED;
}*/
