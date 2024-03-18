#include <string>
#include <raylib.h>
#include <utility>
#include <vector>

using namespace std;
typedef struct Player Player;
typedef struct Buff Buff;
typedef struct Projectile Projectile;  

struct Buff {
  string name;
  bool temporal;
  float lifeTime;
  float totalTime;
  Texture2D texture;

  void ApplyBuff(Player&);
  void Draw();
};

struct Projectile {
  int damage;
  float velocity;
  Vector2 target;
  Texture2D sprite;

  void Ai();
  void Draw();
};

struct Player {
  int maxLife;
  int life;
  int milk;
  Projectile shoot;
  Texture2D sprite;
  vector<Buff>buffs;

  enum Direction {
    NORTH, SOUTH,
    EAST, WEST,
    NORTHEAST,
    NORTHWEST,
    SOUTHEAST,
    SOUTHWEST
  } direction;
  
  void Shoot();
  void Move();
  void Draw();
};

struct Enemy {
  int maxLife;
  int life;
  bool melee;
  int milk;
  Projectile shoot;
  Texture2D sprite;
  vector<pair<Buff,float>>buffs;
};
