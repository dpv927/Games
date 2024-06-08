#include <string.h>
#include <raylib.h>
#include <stdbool.h>

#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    500
#define PAD_WIDTH        25
#define PAD_HEIGHT       100
#define DEF_PAD_X        50
#define PADDLE_SPEED     10
#define DEF_BALL_SPEED_X 5
#define DEF_BALL_SPEED_Y 5
#define BALL_WIDTH       20
#define FONTSIZE         40

const int DEF_PAD_Y  = (WINDOW_HEIGHT>>1) - (PAD_HEIGHT>>1);
const int DEF_BALL_X = WINDOW_WIDTH>>1;
const int DEF_BALL_Y = WINDOW_HEIGHT>>1;

struct Player {
  Rectangle paddle;
  int key_up;
  int key_down;
  int speed;
};

struct Ball {
  Rectangle shape;
  Vector2 speed;
};

enum GameState {
  NO_WIN = 0,
  PLAYER1_WON,
  PLAYER2_WON,
};

void checkPaddleMovement(struct Player* player) {
  int moveDir; // Moving direction
  
  moveDir = IsKeyDown(player->key_down) - IsKeyDown(player->key_up);
  if(player->paddle.y == 0 && moveDir == -1) return;
  if(player->paddle.y + player->paddle.height == WINDOW_HEIGHT && moveDir == 1) return;
  player->paddle.y += moveDir * player->speed;
}

bool checkPaddleCollision(struct Ball* ball, struct Player player) {
  
  if (CheckCollisionRecs(ball->shape, player.paddle)) {
    float paddleCenterY;
    float ballCenterY;
    float collisionPoint;

    // Determine collision point relative to paddle
    paddleCenterY = player.paddle.y + player.paddle.height/2.0f;
    ballCenterY = ball->shape.y + ball->shape.height/2.0f;
    collisionPoint = ballCenterY - paddleCenterY;

    // Normalize collision point (-1 to 1 range)
    collisionPoint /= (player.paddle.height/2);

    // Reflect ball
    ball->speed.x *= -1;
    ball->speed.y += collisionPoint * 2.0f;
    return true;
  }
  return false;
}

int moveBall(struct Ball* ball) {
  int newX = ball->shape.x + ball->speed.x;
  int newY = ball->shape.y + ball->speed.y;

  if (newX <= 0)
    return PLAYER2_WON;
  if (newX >= WINDOW_WIDTH - BALL_WIDTH)
    return PLAYER1_WON;
    
  if (newY <= 0 || newY >= WINDOW_HEIGHT - BALL_WIDTH)
    ball->speed.y *= -1;

  ball->shape.x = newX;
  ball->shape.y = newY; 
  return NO_WIN;
}

int main(void) {

  bool gameAlive = true;
  int winner;

  struct Player player1 = {
    .paddle = {
      .x = DEF_PAD_X,
      .y = DEF_PAD_Y,
      .width = PAD_WIDTH,
      .height = PAD_HEIGHT,
    },
    .key_down = KEY_S,
    .key_up = KEY_W,
    .speed = PADDLE_SPEED
  };

  struct Player player2 = {
    .paddle = {
      .x = WINDOW_WIDTH - (DEF_PAD_X + PAD_WIDTH),
      .y = DEF_PAD_Y,
      .width = PAD_WIDTH,
      .height = PAD_HEIGHT,
    },
    .key_down = KEY_DOWN,
    .key_up = KEY_UP,
    .speed = PADDLE_SPEED
  };

  struct Ball ball = {
    .shape = {
      .x = DEF_BALL_X,
      .y = DEF_BALL_Y,
      .width = BALL_WIDTH,
      .height = BALL_WIDTH
    },
    .speed = {
      DEF_BALL_SPEED_X,
      DEF_BALL_SPEED_Y
    }
  };

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    if(gameAlive /* Game keeps going */) {
      checkPaddleMovement(&player1);
      checkPaddleMovement(&player2);

      if((winner = moveBall(&ball))) {
        // Someone won
        gameAlive = false;
      }

      // Check colisiones
      if (checkPaddleCollision(&ball,player1) 
        || checkPaddleCollision(&ball, player2)) {
        ball.shape.x += ball.speed.x;
      }

      // Draw all the elements
      DrawRectangleRec(player1.paddle, BLUE);
      DrawRectangleRec(player2.paddle, RED);
      DrawRectangleRec(ball.shape, RAYWHITE);
    }
    else {
      // Show game end information1
      int positiony = (WINDOW_HEIGHT>>1) - FONTSIZE;
      int positionx = (WINDOW_WIDTH>>1) - (FONTSIZE*(int)strlen("Player1 won"))/3;
      DrawText(TextFormat("Player%d won!", winner), positionx, positiony, FONTSIZE, WHITE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

