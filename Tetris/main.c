#include <stdbool.h>
#include <stdint.h>
#include <raylib.h>

#define get_bit(block, bit) ((0x8000 >> bit) & block)
#define TILE_WIDTH 70 /*(px)*/
#define ROWS 20
#define COLS 10

enum Shape { I, J, L, O, S, T, Z };

// (I)
// 1 1 1 1    0 0 1 0    1 1 1 1    0 1 0 0
// 0 0 0 0 -> 0 0 1 0 -> 0 0 0 0 -> 0 1 0 0
// 0 0 0 0    0 0 1 0    0 0 0 0    0 1 0 0
// 0 0 0 0    0 0 1 0    0 0 0 0    0 1 0 0
//
// (T)
// 0 1 0 0    0 1 0 0    1 1 1 0    0 1 0 0
// 1 1 1 0 -> 0 1 1 0 -> 0 1 0 0 -> 1 1 0 0 
// 0 0 0 0    0 1 0 0    0 0 0 0    0 1 0 0 
// 0 0 0 0    0 0 0 0    0 0 0 0    0 0 0 0
//
// (O)
// 0 1 1 0
// 0 1 1 0
// 0 0 0 0
// 0 0 0 0
//
// (Z)
// 1 1 0 0    0 0 1 0    1 1 0 0    0 1 0 0
// 0 1 1 0 -> 0 1 1 0 -> 0 1 1 0 -> 1 1 0 0
// 0 0 0 0    0 1 0 0    0 0 0 0    1 0 0 0
// 0 0 0 0    0 0 0 0    0 0 0 0    0 0 0 0
//
// (L)
// 0 0 1 0    0 1 0 0    1 1 1 0    1 1 0 0
// 1 1 1 0 -> 0 1 0 0 -> 1 0 0 0 -> 0 1 0 0
// 0 0 0 0    0 1 1 0    0 0 0 0    0 1 0 0
// 0 0 0 0    0 0 0 0    0 0 0 0    0 0 0 0
//
// (J)
// 1 0 0 0    0 1 1 0    1 1 1 0    0 1 0 0
// 1 1 1 0 -> 0 1 0 0 -> 0 0 1 0 -> 0 1 0 0
// 0 0 0 0    0 1 0 0    0 0 0 0    1 1 0 0
// 0 0 0 0    0 0 0 0    0 0 0 0    0 0 0 0
//
// (S)
// 0 1 1 0    0 1 0 0    0 1 1 0    1 0 0 0
// 1 1 0 0 -> 0 1 1 0 -> 1 1 0 0 -> 1 1 0 0
// 0 0 0 0    0 0 1 0    0 0 0 0    0 1 0 0
// 0 0 0 0    0 0 0 0    0 0 0 0    0 0 0 0

static const uint16_t shapes[7][4] = {
  [I] = { 0xf000, 0x2222, 0xf000, 0x4444 },
  [J] = { 0x8e00, 0x6440, 0xe200, 0x44c0 },
  [L] = { 0x2e00, 0x4460, 0xe800, 0xc440 },
  [O] = { 0x6600, 0x6600, 0x6600, 0x6600 },
  [S] = { 0x6c00, 0x4620, 0x6c00, 0x8c40 },
  [T] = { 0x4e00, 0x4640, 0xe400, 0x4c40 },
  [Z] = { 0xc600, 0x2640, 0xc600, 0x4c80 },
};

static const Color colors[7] = {
  [I] = { 0xcc, 0x00, 0x00, 0xff },
  [J] = { 0x8e, 0x00, 0xcc, 0xff },
  [L] = { 0xcc, 0xcc, 0x00, 0xff },
  [O] = { 0x00, 0x00, 0xcc, 0xff },
  [S] = { 0x00, 0xcc, 0xcc, 0xff },
  [T] = { 0x00, 0xcc, 0x00, 0xff },
  [Z] = { 0xcc, 0x00, 0xcc, 0xff },
};

struct Tetromino {
  enum Shape shape;
  int angle;
  int x;
  int y;
};

struct Block {
  bool active;
  int color;
};

#define LEFT_SIDE  0 
#define RIGHT_SIDE 1 

void draw_frame(int offset, int width, int height);
void draw_tetronimo(struct Tetromino* t);
void move_to_side(struct Tetromino* t, int side);

int main(void) {

  int main_frame_width  = (COLS+2) * TILE_WIDTH;
  int main_frame_height = (ROWS+2) * TILE_WIDTH;
  int next_frame_width = 6 * TILE_WIDTH;
  int next_frame_gap   = TILE_WIDTH/2;

  InitWindow(main_frame_width + next_frame_width + next_frame_gap,
      main_frame_height, "Tetris");
  SetTraceLogLevel(LOG_ERROR);
  SetTargetFPS(10);


  struct Tetromino t;
  t.shape = Z;
  t.angle = 1;
  t.x = 4;
  t.y = 1;


  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    if(IsKeyDown(KEY_A))
      move_to_side(&t, LEFT_SIDE);
    else if (IsKeyDown(KEY_D))
      move_to_side(&t, RIGHT_SIDE);

    draw_tetronimo(&t);
    draw_frame(0, ROWS + 2, COLS + 2);
    draw_frame(main_frame_width + next_frame_gap, 6, 6);
    EndDrawing();
  }

  CloseWindow();
}


void draw_frame(int offset, int rows, int cols) {
  Color color = { 0x66, 0x66, 0x66, 0xff };
  int width = cols * TILE_WIDTH;
  int height = rows * TILE_WIDTH;

  // Draw a tile frame
  DrawRectangle(offset, 0, width, TILE_WIDTH, color);
  DrawRectangle(offset, height - TILE_WIDTH, width, TILE_WIDTH, color);
  DrawRectangle(offset, 0, TILE_WIDTH, height, color);
  DrawRectangle(offset + (width - TILE_WIDTH), 0, TILE_WIDTH, height, color);

  // Draw a grid to differentiate each block
  for(int i = 0; i < rows; i++) {
    Vector2 src  = { offset, TILE_WIDTH * i };
    Vector2 dest = { offset + width, TILE_WIDTH * i };
    DrawLineEx(src, dest, 2.0f, BLACK);
  }

  for(int i = 0; i < cols; i++) {
    Vector2 src  = { offset + (i * TILE_WIDTH), 0 };
    Vector2 dest = { offset + (i * TILE_WIDTH), height };
    DrawLineEx(src, dest, 2.0f, BLACK);
  }
}


void draw_tetronimo(struct Tetromino* t) {
  uint16_t shape = shapes[t->shape][t->angle];
  uint16_t x = 0, y = 0, i;
  Color color = colors[t->shape];

  for(int i = 0; i < 16; i++) {
      if(get_bit(shape, i)) {
        DrawRectangle(
            TILE_WIDTH * (1 + (t->x + x)),
            TILE_WIDTH * (1 + (t->y + y)),
            TILE_WIDTH,
            TILE_WIDTH,
            color);
      }
      y = ((x+1) == 4)? y+1 : y;
      x = (x+1) % 4;
    }
}


void move_to_side(struct Tetromino* t, int side) {
  switch(side) {
    case LEFT_SIDE: {
      if(t->x <= -2) 
        break;

      if(t->x > 0){
        t->x -= 1;
      
      } else if(t->x == 0){
        if(shapes[t->shape][t->angle] & 0x8888)
          break;
        else t->x -= 1;
      
      } else /* t.x == -1 */ {
        if(shapes[t->shape][t->angle] & 0x4444)
          break;
        else t->x -= 1;
      }
      break;
    };
    case RIGHT_SIDE: {
        if(t->x >= 8)
          break;

        if(t->x <= 5)
          t->x += 1;
        
        else if(t->x == 6) {
          if(shapes[t->shape][t->angle] & 0x1111)
            break;
          else t->x += 1;
        
        } else /* t.x == 7 */ {
          if(shapes[t->shape][t->angle] & 0x2222)
            break;
          else t->x += 1;
        }
      break;
    };
  }
}
