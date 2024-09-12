use raylib::prelude::*;
use crate::tetromino::*;

const FRAME_COLOR: Color = Color::new(
    0x66,
    0x66,
    0x66,
    0xff
);

pub struct Frame {
    tile_width: i32,
    cols: i32,
    rows: i32,
    offset: i32,
    pub def_x: i32,
    pub def_y: i32,
}

impl Frame {
    
    pub fn new(rows: i32, cols: i32, tile_width: i32, offset: i32, def_x: i32, def_y: i32) -> Frame {
        Frame { tile_width, rows, cols, offset, def_x, def_y }
    }

    ///
    /// Draws the frame, including a grid to help differentiate each block 
    /// of the tetrominoes.
    ///
    pub fn draw_self(&self, handle: &mut RaylibDrawHandle) {
        let width  = (self.cols + 2) * self.tile_width;
        let height = (self.rows + 2) * self.tile_width;

        // Draw a tile frame
        handle.draw_rectangle(self.offset, 0, width, self.tile_width, FRAME_COLOR);
        handle.draw_rectangle(self.offset, height - self.tile_width, width, self.tile_width, FRAME_COLOR);
        handle.draw_rectangle(self.offset, 0, self.tile_width, height, FRAME_COLOR);
        handle.draw_rectangle(self.offset + (width - self.tile_width), 0, self.tile_width, height, FRAME_COLOR);
    
        // Draw a grid to differentiate each block
        for i in 0..(self.rows + 2) {
            let src  = Vector2::new(self.offset as f32, (self.tile_width * i) as f32);
            let dest = Vector2::new((self.offset + width) as f32, (self.tile_width * i) as f32);
            handle.draw_line_ex(src, dest, 2., Color::BLACK);
        }

        for i in 0..(self.cols + 2) {
            let src  = Vector2::new((self.offset + (i * self.tile_width)) as f32, 0. );
            let dest = Vector2::new((self.offset + (i * self.tile_width)) as f32, height as f32);
            handle.draw_line_ex(src, dest, 2., Color::BLACK);
        }
    }

    /// 
    /// Draws a tetromino inside of the frame.
    ///
    pub fn draw_tetronimo(&self, t: &Tetronimo, handle: &mut RaylibDrawHandle) {
        let shape = TETRONIMOS[t.shape][t.angle];
        let color = COLORS[t.shape];
        let mut bit = 0; 
        let mut x = 0;
        let mut y = 0;

        loop {
            if Tetronimo::get_bit(shape, bit) != 0 {
                handle.draw_rectangle(
                    self.offset + self.tile_width * (1 + (t.x + x)),
                    self.tile_width * (1 + (t.y + y)),
                    self.tile_width,
                    self.tile_width,
                    color);
            }

            y = if (x+1) == 4 { y+1 } else { y }; 
            x = (x + 1) % 4;
            
            if bit == 15 { 
                break;
            } else { bit += 1; }
        };
    }
}
