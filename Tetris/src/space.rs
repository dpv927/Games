// A space is where all the tetrominoes are placed. When placing a tetromino 
// along the others, it 'fuses' with them in an array.
//
// We consider a tetris layout to be 10 blocks of width x 20 blocks tall,
// so we can express a tetris layout as rows of 10 bits (cause words of 
// 10 bits does not exist, we take the top 10 bits from 16-bits words).
//
// Because tetrominoes are also expressed as blocks of 16 bits in tetrominoes.rs,
// we can easily determine certain conditions of the space much faster than
// if we did in other way.
//

pub struct Space {
    pub blocks: [u16;20],
    pub colors: [[u8;10];20]
}

impl Space {
    
    pub fn new() -> Space {
        Space {
            blocks: [0;20],
            colors: [[0;10];20]
        }
    }
}
