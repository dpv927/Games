use raylib::prelude::*;

//# Base ball constants #//
const BALL_SPEED:  i32 = 5;
const BALL_RADIUS: i32 = 15;

pub struct Ball {
    x: i32,
    y: i32,
    dx: i32,
    dy: i32,
    radius: i32,
}

impl Ball {
    
    pub fn new(window_size: i32) -> Ball {
        let center = window_size >> 1;
        Ball { x: center, y: center, dx: BALL_SPEED + 2, dy: BALL_SPEED, radius: BALL_RADIUS }
    }

    pub fn compute_wall_collisions(&mut self, window_limit: i32) -> bool {
        let x_limit = self.x + self.dx;
        let y_limit = self.y + self.dy;
        let mut play_sound = false;

        if x_limit + self.radius >= window_limit {
            self.dx = -self.dx;
            self.x = window_limit - self.radius;
            play_sound = true;
    
        } else if x_limit - self.radius <= 0 {
            self.dx = -self.dx;
            self.x = self.radius;
            play_sound = true;
        }

        if y_limit + self.radius >= window_limit {
            self.dy = -self.dy;
            self.y = window_limit - self.radius;
            play_sound = true;

        } else if y_limit - self.radius <= 0 {
            self.dy = -self.dy;
            self.y = self.radius;
            play_sound = true;
        }

        self.x = self.x + self.dx;
        self.y = self.y + self.dy;
        play_sound
    }

    

    pub fn draw(&self, handle: &mut RaylibDrawHandle) {
        handle.draw_circle(self.x, self.y, self.radius as f32, Color::RAYWHITE);
        handle.draw_circle_lines(self.x, self.y, self.radius as f32, Color::BLACK);
    }
}

