use raylib::prelude::*;
use crate::space::Space;

pub const TETRONIMOS: [[u16;4];7] = [
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

    /* I */ [ 0xf000, 0x2222, 0xf000, 0x4444 ],
    /* J */ [ 0x8e00, 0x6440, 0xe200, 0x44c0 ],
    /* L */ [ 0x2e00, 0x4460, 0xe800, 0xc440 ],
    /* O */ [ 0x6600, 0x6600, 0x6600, 0x6600 ],
    /* S */ [ 0x6c00, 0x4620, 0x6c00, 0x8c40 ],
    /* T */ [ 0x4e00, 0x4640, 0xe400, 0x4c40 ],
    /* Z */ [ 0xc600, 0x2640, 0xc600, 0x4c80 ],
];

pub const COLORS: [Color;7] = [
    /* I */ Color::new(0xcc, 0x00, 0x00, 0xff),
    /* J */ Color::new(0x8e, 0x00, 0xcc, 0xff),
    /* L */ Color::new(0xcc, 0xcc, 0x00, 0xff),
    /* O */ Color::new(0x00, 0x00, 0xcc, 0xff),
    /* S */ Color::new(0x00, 0xcc, 0xcc, 0xff),
    /* T */ Color::new(0x00, 0xcc, 0x00, 0xff),
    /* Z */ Color::new(0xcc, 0x00, 0xcc, 0xff),
];

pub struct Tetronimo {
    pub shape: usize,
    pub angle: usize,
    pub x: i32,
    pub y: i32,
}

pub enum Direction {
    Right,
    Left,
}

impl Tetronimo {

    pub fn new(shape: usize, x: i32, y: i32) -> Tetronimo {
        Tetronimo { shape, angle: 0, x, y }
    }

    pub fn get_bit(shape: u16, i: u8) -> u16 {
        (0x8000 >> i) & shape
    } 

    pub fn move_to_side(&mut self, direction: Direction) {
        let shape = TETRONIMOS[self.shape][self.angle];

        match direction {
            Direction::Left => {
                if self.x <= -2 { 
                    return; 
                }

                if self.x > 0 {
                    self.x -= 1;

                } else if self.x == 0 {
                    if (shape & 0x8888) != 0 {
                        return;
                    } else { self.x -= 1; } 
                
                } else /* self.x == -1 */ {
                    if (shape & 0x4444) != 0 {
                        return;
                    } else { self.x -= 1; }
                }
            },
            Direction::Right => {
                if self.x >= 8 {
                    return;
                }

                if self.x <= 5 {
                    self.x += 1;
                
                } else if self.x == 6 {
                    if (shape & 0x1111) != 0 {
                        return;
                    } else { self.x += 1; }
                
                } else /* self.x == 7 */ {
                    if (shape & 0x2222) != 0 {
                        return;
                    } else { self.x += 1; }
                }
            },
        }
    }

    pub fn rotate(&mut self) {
        let next_shape = TETRONIMOS[self.shape][(self.angle + 1) % 4];
        let shape = TETRONIMOS[self.shape][self.angle];

        if self.x < 0 {
            match self.x {
                -2 => { self.x = 0; },
                -1 => { 
                    if ((next_shape & 0x8888) != 0) && ((shape & 0x4444) != 0) {
                        self.x = 0;
                    }
                },
                _ => {},
            }
        } else if self.x > 6 {
            match self.x {
                7 => {
                    if (next_shape & 0x1111) != 0 {
                        self.x = 6;
                    }
                },
                8 => {
                    if ((next_shape & 0x8888) !=0) && ((shape & 0x8888) != 0) {
                        self.x = 7;
                    } else { self.x = 6; }
                },
                _ => {},
            }
        }
        self.angle = (self.angle + 1) % 4;
    }

    pub fn move_down(&mut self, space: &mut Space) -> bool {
        let shape = TETRONIMOS[self.shape][self.angle];
        let mut collision = false;
        
        // Check if is colliding with the bottom
        let mut row_mask = 0x000f;
        let mut last_row = 3;

        loop {
            if (row_mask & shape) != 0  || // Its the last != 0 row
                (last_row - 1) < 0 { // End of the loop
                break;
            }

            row_mask <<= 4;
            last_row -= 1;
        }

        if self.y + last_row == 19 {
            // The Tetronimo is touching the bottom
            collision = true;
        } else {
            // The Tetronimo is somewhere in the space
            let mut row = space.blocks[(self.y + 1) as usize];
            let mut x_i = 0;
            let mut y_i = 1;

            for bit in 0..16 {
                if Tetronimo::get_bit(shape, bit) != 0 && 
                    Tetronimo::get_bit(row, (self.x + x_i) as u8) != 0 {
                    collision = true;
                }

                if (x_i + 1) == 4 {
                    y_i += 1;
                    x_i = 0;
                
                    if self.y + y_i >= 19 { 
                        break; 
                    }
                
                    row = space.blocks[(self.y + y_i) as usize];
                } else { x_i += 1; }
            }
        }

        if !collision {
            self.y += 1;
        } else {
            // Merge the Tetronimo and the other blocks at the space.
            let y = self.y as usize;
            let mut row_mask = 0xf000;

            for row in 0..(last_row+1) {
                println!("{}", last_row);
                space.blocks[y + row as usize] = 
                    ((shape & row_mask) << (row * 4)) >> self.x;
                row_mask >>= 4;
            }

            let mut x_i = 0;
            let mut y_i = 0;

            for bit in 0..16 {

                if Tetronimo::get_bit(shape, bit) != 0 {
                    // Set each block of the Tetronimo in the space the 
                    // its color.
                    space.colors[(self.y + y_i) as usize][(self.x + x_i) as usize] 
                        = self.shape as u8;
                }
                
                if (x_i + 1) == 4 {
                    y_i += 1;
                    x_i = 0;

                    if y_i > last_row { 
                        break; 
                    }
                } else { x_i += 1; }
            }
            self.x = 3;
            self.y = 0;
        }
        collision
    }
}
