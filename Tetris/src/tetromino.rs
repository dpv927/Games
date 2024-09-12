use raylib::prelude::*;

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
}
