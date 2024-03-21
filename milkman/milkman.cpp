#include <cmath>
#include <raylib.h>
#include <vector>
#include <chrono>
#include <memory>
#define TEXPATH "milkman.png"
#define BASEWRES 1366;
#define BASEHRES 768;

using namespace std;
using namespace std::chrono;

struct Projectile {
  Vector2 position;
  float speedX;
  float speedY;
  float radius;
  time_point<milliseconds> spawnTime;

  Projectile(time_point<milliseconds>spawn, Vector2 pos, float spX, 
             float spY, float rad):
    spawnTime(spawn), position(pos), speedX(spX), 
    speedY(spY), radius(rad) {};
};

struct Player {
  Texture2D sprites;
  Rectangle frame;
  Rectangle position;
  Vector2 targetPosition;
  vector<unique_ptr<Projectile>> projectiles;
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
  time_point lastShot = high_resolution_clock::now();

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
    time_point timeNow = high_resolution_clock::now();
    double diff = duration_cast<milliseconds>(timeNow - lastShot)
      .count()/1000.0f;

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && diff > 0.3f) {
      lastShot = timeNow;
      int mx = GetMouseX()-player.position.x;
      int my = GetMouseY()-player.position.y;
      float mod = sqrt(mx*mx + my*my);

      player.projectiles.push_back(make_unique<Projectile>(
        Vector2{
          player.position.x+player.position.width/2,
          player.position.y+player.position.height/2
        },
        (mx/mod)*10,
        (my/mod)*10,
        10
      ));
    }

    // Actualizar los projectiles
    for(auto it = player.projectiles.begin(); it != player.projectiles.end(); ++it) {
      if(it->get()->)
    }

    //for (Projectile* p : player.projectiles) {
    //  p->position.x += p->speedX;
    //  p->position.y += p->speedY;
    // }

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

