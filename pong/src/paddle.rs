use raylib::prelude::*;

pub const PADDLE_MARGIN: i32 = 20;
const PADDLE_SPEED: i32 = 10;

pub struct Paddle {
    texture: Texture2D,
    side: PaddleSide,
    x: i32,
    y: i32,
    dy: i32,
}

pub enum PaddleSide {
    Player1,
    Player2,
}

impl Paddle {

    pub fn new(window_limit: i32, side: PaddleSide, texture: Texture2D) -> Paddle {
        let middle = window_limit >> 1;

        match side {
            PaddleSide::Player1 => Paddle { 
                x: PADDLE_MARGIN,
                y: middle - texture.height,
                dy:PADDLE_SPEED, 
                texture,
                side,
            },
            PaddleSide::Player2 => Paddle {
                x: window_limit - PADDLE_MARGIN - texture.width,
                y: middle - texture.height,
                dy:PADDLE_SPEED, 
                texture,
                side,
            }
        }
    }

    pub fn compute_movement(&mut self, window_limit: i32, handle: &RaylibHandle) {
        let mut next_y = self.y;

        match self.side {
            PaddleSide::Player1 => { 
                if handle.is_key_down(KeyboardKey::KEY_W) { next_y = next_y - self.dy; }
                if handle.is_key_down(KeyboardKey::KEY_S) { next_y = next_y + self.dy; }
            },
            PaddleSide::Player2 => { 
                if handle.is_key_down(KeyboardKey::KEY_UP) { next_y = next_y - self.dy; }
                if handle.is_key_down(KeyboardKey::KEY_DOWN) { next_y = next_y + self.dy; }
            }
        }

        if next_y == self.y { return; }

        if next_y + self.texture.height >= window_limit {
            self.y = window_limit - self.texture.height;
        } else if next_y <= 0 {
            self.y = 0;
        } else {
            self.y = next_y;
        }
    }

    pub fn draw(&self, handle: &mut RaylibDrawHandle) {
        handle.draw_texture(&self.texture, self.x, self.y, Color::WHITE);
    }
}
