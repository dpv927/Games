#include <raylib.h>

#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    450
#define PAD_WIDTH        25
#define PAD_HEIGHT       100
#define DEF_PAD_X        50
#define DEF_PAD_Y        175
#define DEF_BALL_X       WINDOW_WIDTH>>1
#define DEF_BALL_Y       WINDOW_HEIGHT>>1
#define DEF_BALL_SPEED_X 5
#define DEF_BALL_SPEED_Y 5
#define BALL_RADIUS      10

enum { 
  NO_PLAYER = 0,
  PLAYER_1,
  PLAYER_2,
};

typedef struct{
  int x;
  int y;
  int radius;
} Circle;

void movePaddle(int keyPressed, Rectangle* paddle, int windowHeight, int speedY) {
  int newY = paddle->y + speedY;

  if(IsKeyDown(keyPressed) && (newY+paddle->height < windowHeight) 
    && (newY > 0)) {
    paddle->y += speedY;
  } 
}

int moveBall(Vector2* ball, Vector2* ballSpeed) {
  int newX = ball->x + ballSpeed->x;
  int newY = ball->y + ballSpeed->y;

  if(newX <= BALL_RADIUS)
    return PLAYER_2;
  if(newX >= WINDOW_WIDTH - BALL_RADIUS)
    return PLAYER_1;
  
  if(newY <= BALL_RADIUS || newY >= WINDOW_HEIGHT - BALL_RADIUS)
    ballSpeed->y *= -1;

  ball->x += ballSpeed->x;
  ball->y += ballSpeed->y; 
  return NO_PLAYER;
}

void manageColisions(Vector2 ball, Vector2* ballSpeed, Rectangle recPad1, Rectangle recPad2) {
  Vector2 bCenter = {ball.x, ball.y};

  if(CheckCollisionCircleRec(bCenter, BALL_RADIUS, recPad1)){
    if((bCenter.y - BALL_RADIUS <= recPad1.y) || 
        (bCenter.y + BALL_RADIUS >= recPad1.y + recPad1.height))
      ballSpeed->y *= -1;
    else { ballSpeed->x *= -1; }
  }

  if(CheckCollisionCircleRec(bCenter, BALL_RADIUS, recPad2)) {
    if((bCenter.y - BALL_RADIUS <= recPad2.y) || 
        (bCenter.y + BALL_RADIUS >= recPad2.y + recPad2.height))
      ballSpeed->y *= -1;
    else { ballSpeed->x *= -1; }
  }
}

int main(void) {

  Vector2 paddleSpeed = { 0, 12 };  
  int gameState;

  Vector2 ballSpeed = {
    .x = DEF_BALL_SPEED_X,
    .y = DEF_BALL_SPEED_Y 
  };
  
  Vector2 ball = {
    .x = DEF_BALL_X,
    .y = DEF_BALL_Y,
  };

  Rectangle recPad1 = {
    .x = DEF_PAD_X,
    .y = DEF_PAD_Y,
    .width = PAD_WIDTH,
    .height = PAD_HEIGHT,
  };

  Rectangle recPad2 = {
    .x = WINDOW_WIDTH - (DEF_PAD_X + PAD_WIDTH),
    .y = DEF_PAD_Y,
    .width = PAD_WIDTH,
    .height = PAD_HEIGHT,
  };

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "basic window");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);

    // Check Pad1 movement
    movePaddle(KEY_S, &recPad1, WINDOW_HEIGHT, paddleSpeed.y);
    movePaddle(KEY_W,   &recPad1, WINDOW_HEIGHT, paddleSpeed.y*(-1));
    
    // Check Pad2 movement
    movePaddle(KEY_DOWN, &recPad2, WINDOW_HEIGHT, paddleSpeed.y);
    movePaddle(KEY_UP, &recPad2, WINDOW_HEIGHT, paddleSpeed.y*(-1));

    // Move the ball
    manageColisions(ball, &ballSpeed, recPad1, recPad2);
    gameState = moveBall(&ball, &ballSpeed);
    
    if(gameState) { // One of the players won
      char* message = (gameState == PLAYER_1)? 
        "Player 1 won!" : "Player 2 won!";
      DrawText(message, 285, 200, 40, LIGHTGRAY);
    }

    // Draw all the elements
    DrawRectangleRec(recPad1, BLUE);
    DrawRectangleRec(recPad2, RED);
    DrawCircle(ball.x, ball.y, BALL_RADIUS, RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

