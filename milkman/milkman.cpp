#include <cmath>
#include <raylib.h>
#include <vector>
#include <chrono>
#include <memory>

#define TEXPATH "milkman.png"
#define BASEWRES 1366;
#define BASEHRES 768;
#define BASE_PL_SPEED 10
#define BASE_PR_SPEED 8

using namespace std;
using namespace std::chrono;

struct Projectile {
  Vector2 position;
  float speedX;
  float speedY;
  float radius;
  time_point<high_resolution_clock> spawnTime;

  Projectile(Vector2 pos, float spX, float spY, float rad,
    time_point<high_resolution_clock> spawn):
    position(pos), speedX(spX), speedY(spY), radius(rad),
    spawnTime(spawn) {};
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
  float playerSpeed;
  float projectileSpeed;
  int moveX;
  int moveY;
  int screenWidth;
  int screenHeight;

  // --------------- //
  // Window Settings //
  // --------------- //

  InitWindow(0,0,"Milkman");
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  ToggleFullscreen();
  SetTargetFPS(60);
 
  screenWidth = GetScreenWidth();
  screenHeight = GetScreenHeight();

  // Calculate objects scale
  scaleX = (float)screenWidth/BASEWRES;
  scaleY = (float)screenHeight/BASEHRES;
  playerSpeed = BASE_PL_SPEED * scaleX;
  projectileSpeed = BASE_PR_SPEED * scaleX;

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
  auto lastShot = high_resolution_clock::now();

  while (!WindowShouldClose()) {
    moveX = (IsKeyDown(KEY_D)-IsKeyDown(KEY_A));
    moveY = (IsKeyDown(KEY_S)-IsKeyDown(KEY_W));
    player.targetPosition.x += moveX * playerSpeed;
    player.targetPosition.y += moveY * playerSpeed;

    player.position.x += 0.08f * (player.targetPosition.x - player.position.x);
    player.position.y += 0.08f * (player.targetPosition.y - player.position.y);
    
    // Get the indicated sprite for the selected 
    // player movement.
    player.frame.x = (moveX==0 && moveY==0 || moveX==0 && moveY==1)? 0 :
      (moveX ==  0 && moveY == -1)? player.frame.width :
      (moveX == -1 && moveY ==  0)? 2*(float)player.frame.width :
      (moveX ==  1 && moveY ==  0)? 3*(float)player.frame.width :
      (moveX == -1 && moveY !=  0)? 4*(float)player.frame.width :
      (moveX ==  1 && moveY !=  0)? 5*(float)player.frame.width : 0;

    // Si el usuario ha presionado la tecla espacio, generar un projectil;
    // Generar un projectil con direccion de las teclas de direccion
    time_point timeNow = high_resolution_clock::now();
    double diff = duration_cast<milliseconds>(timeNow - lastShot).count();

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && diff > 300) {
      lastShot = timeNow;
      int mx = GetMouseX()-player.position.x;
      int my = GetMouseY()-player.position.y;
      float mod = sqrt(mx*mx + my*my);

      player.projectiles.push_back(make_unique<Projectile>(
        Vector2{
          player.position.x+player.position.width/2,
          player.position.y+player.position.height/2
        },
        (mx/mod)*projectileSpeed,
        (my/mod)*projectileSpeed,
        10*scaleY,
        timeNow
      ));
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Comprobar en la lista de proyectiles si existen algunos los cuales 
    // han cumplido su tiempo de vida. En ese caso, borrarlo, y en caso 
    // contrario, actualizar su posicion y dibujarlo
    
    for (auto it = player.projectiles.begin(); it != player.projectiles.end();) {
      auto& projectile = *it;

      if (projectile->position.x > screenWidth || projectile->position.y > screenHeight ||
        duration_cast<milliseconds>(timeNow - projectile->spawnTime).count() >= 2000) {
        it = player.projectiles.erase(it);
      } else {
        projectile->position.x += projectile->speedX;
        projectile->position.y += projectile->speedY;
        DrawCircleV(projectile->position, projectile->radius, BLACK);
        DrawCircleV(projectile->position, projectile->radius*0.85f, WHITE);
        ++it;
      }
    }

    DrawTexturePro(player.sprites, player.frame, player.position, Vector2{0}, 0, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

