use raylib::prelude::*;

#[derive(Debug)]
pub struct Room {
    pub x: i32,
    pub y: i32,
    pub width: i32,
    pub height: i32,
    pub main: bool,
    pub id: u32
}

impl Room {
    
    pub fn is_colliding_with(&self, other: &Self) -> bool {
        (self.x < (other.x + other.width) && (self.x + self.width) > other.x) &&
        (self.y < (other.y + other.height) && (self.y + self.height) > other.y)   
    }

    pub fn draw_room(&self, tile_size: u32, handle: &mut RaylibMode2D<RaylibDrawHandle>) {
        let color = if self.main { Color::RED } else { Color::BLUE };
        let tile_size = tile_size as i32;
        let mut pos_x: i32 = self.x;
        let mut pos_y: i32;

        // Draw a internal grid
        while pos_x < (self.x + self.width) {
            pos_y = self.y;
            while pos_y < (self.y + self.height) {
                handle.draw_rectangle_lines(
                    pos_x,
                    pos_y,
                    tile_size,
                    tile_size, 
                    color);
                pos_y += tile_size;
            }
            pos_x += tile_size;
        }

        // Draw the room edges 
        handle.draw_rectangle_lines(
            self.x,
            self.y, 
            self.width,
            self.height,
            Color::WHITE);
    }
}
