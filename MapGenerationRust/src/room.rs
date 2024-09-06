use raylib::prelude::*;

#[derive(Debug)]
pub struct Room {
    pub x: i32,
    pub y: i32,
    pub width: i32,
    pub height: i32,
    pub main: bool,
    pub id: usize
}

const MAIN_COLOR: Color = Color{ r: 184, g: 124, b: 114, a: 255 };
const NORM_COLOR: Color = Color{ r: 20,  g: 69,  b: 108, a: 255 };

impl Room {
    
    pub fn is_colliding_with(&self, other: &Self) -> bool {
        (self.x < (other.x + other.width) && (self.x + self.width) > other.x) &&
        (self.y < (other.y + other.height) && (self.y + self.height) > other.y)   
    }

    pub fn draw_room(&self, handle: &mut RaylibMode2D<RaylibDrawHandle>) {
        handle.draw_rectangle(
            self.x,
            self.y,
            self.width,
            self.height,
            if self.main { 
                MAIN_COLOR 
            } else { NORM_COLOR });

        handle.draw_text(
            &self.id.to_string(),
            self.x + 15,
            self.y + 15,
            20, Color::RAYWHITE);

        handle.draw_rectangle_lines(
            self.x,
            self.y, 
            self.width,
            self.height,
            Color::WHITE);
    }
}
