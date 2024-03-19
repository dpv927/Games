#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <vector>
#define TEXPATH "milkman.png"
#define BASEWRES 1366;
#define BASEHRES 768;

using namespace std;

struct Projectile {
  Vector2 position;
  float speedX;
  float speedY;
  float radius;
  float lifetime;
};

struct Player {
  Texture2D sprites;
  Rectangle frame;
  Rectangle position;
  Vector2 targetPosition;
  vector<Projectile*> projectiles;
  float lastShot;
} player;

int main(void) {
  float scaleX;
  float scaleY;
  int moveX;
  int moveY;

  // --------------- //
  // Window Settings //
  // --------------- //

  InitWindow(800,500,"Milkman");
  //SetConfigFlags(FLAG_FULLSCREEN_MODE);
  //ToggleFullscreen();
  SetTargetFPS(60);
 
  // Calculate objects scale
  scaleX = (float)GetScreenWidth()/BASEWRES;
  scaleY = (float)GetScreenHeight()/BASEHRES;


  // ---------------- //
  //    Init Player   //
  // ---------------- // 
  player.sprites = LoadTexture(TEXPATH);
  SetTextureFilter(player.sprites, TEXTURE_FILTER_TRILINEAR);
  player.frame.x = player.frame.y = 0;
  player.frame.width  = (float)player.sprites.width/6;
  player.frame.height = (float)player.sprites.height-1;
  
  player.position.x = GetScreenWidth()/2.0f;
  player.position.y = GetScreenHeight()/2.0f;
  player.position.width  = player.frame.width*scaleX;
  player.position.height = player.frame.height*scaleY; 

  player.targetPosition.x = player.position.x;
  player.targetPosition.y = player.position.y;
  player.lastShot = time(NULL);


  while (!WindowShouldClose()) {
    moveX = (IsKeyDown(KEY_D)-IsKeyDown(KEY_A));
    moveY = (IsKeyDown(KEY_S)-IsKeyDown(KEY_W));
    player.targetPosition.x += moveX * 10;
    player.targetPosition.y += moveY * 10;

    player.position.x += 0.08f * (player.targetPosition.x - player.position.x);
    player.position.y += 0.08f * (player.targetPosition.y - player.position.y);
    
    // Get the indicated sprite for the selected 
    // player movement.
    player.frame.x = (moveX==0 && moveY==0 || moveX==0 && moveY==1)? 0 :
      (moveX == 0 && moveY == -1)? player.frame.width :
      (moveX == -1 && moveY == 0)? 2*(float)player.frame.width :
      (moveX == 1 && moveY == 0)? 3*(float)player.frame.width :
      (moveX == -1 && moveY != 0)? 4*(float)player.frame.width :
      (moveX == 1 && moveY != 0)? 5*(float)player.frame.width : 0;

    // Si el usuario ha presionado la tecla espacio, generar un projectil;
    // Generar un projectil con direccion de las teclas de direccion
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (difftime(time(NULL),player.lastShot) > 5)) {
      player.lastShot = time(NULL);

      int mx = GetMouseX()-player.position.x;
      int my = GetMouseY()-player.position.y;
      float mod = sqrt(mx*mx + my*my);

      Projectile* projectile = new Projectile();
      projectile->position  = Vector2{
        player.position.x+player.position.width/2,
        player.position.y+player.position.height/2
      };
      
      projectile->speedX = mx/mod * 10;
      projectile->speedY = my/mod * 10;

      projectile->radius = 10;
      player.projectiles.push_back(projectile);
    }

    // Actualizar los projectiles
    for (Projectile* p : player.projectiles) {
      p->position.x += p->speedX;
      p->position.y += p->speedY;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);
    
    for (Projectile* p : player.projectiles) {
      DrawCircleV(p->position, p->radius, BLACK);
      DrawCircleV(p->position, p->radius*0.85f, WHITE);
    }
    DrawTexturePro(player.sprites, player.frame, player.position, Vector2{0}, 0, WHITE);
    
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
