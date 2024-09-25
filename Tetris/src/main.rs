use raylib::prelude::*;
use rand_distr::Distribution;
use tetromino::{Tetronimo, Direction};
use frame::Frame;
use space::Space;

mod tetromino;
mod frame;
mod space;

const TILE_SIZE: i32 = 70;
const FONT_SIZE: i32 = 40;
const FONT_COLOR: Color = Color::new(173,176,187,255);

fn main() {
     let (mut rl, thread) = raylib::init()
        .size(0, 0)
        .title("Map Generation")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();
    rl.set_target_fps(60);

    {
        let monitor_width  = window::get_monitor_width(window::get_current_monitor());
        let monitor_height = window::get_monitor_height(window::get_current_monitor());
        /* Main frame width (10 + 2) + space (1) + next frame width (4 + 2) */
        let window_width  = 19 * TILE_SIZE;
        /* Main frame height (20 + 2) */
        let window_height = 22 * TILE_SIZE;

        rl.set_window_position((monitor_width - window_width)/2, (monitor_height - window_height)/2);
        rl.set_window_size(window_width, window_height);
    }

    let mut rng = rand::thread_rng();
    let dist = rand_distr::Uniform::new(0,7);
    let mut timer_gravity: std::time::Instant;
    let mut timer_user: std::time::Instant;

    // Frames (Places to show tetrominoes and blocks)
    // In the main_frame we show the game, and in the next_frame e show
    // the next tetromino to pick.
    let main_frame = Frame::new(20, 10, TILE_SIZE, 0, 3, 0);
    let next_frame = Frame::new(4,  4,  TILE_SIZE, 13 * TILE_SIZE, 0, 0);
    let info_x = TILE_SIZE * 13;

    // Current tetromino and the next one.
    let mut actual = Tetronimo::new(dist.sample(&mut rng), main_frame.def_x, main_frame.def_y);
    let mut next   = Tetronimo::new(dist.sample(&mut rng), next_frame.def_x, next_frame.def_y);

    // All the possitioned tetrominoes as blocks in an array.
    let mut space = Space::new();

    // Some variables
    let shapes = 0;
    let rows = 0;
    let score = 0;
    timer_gravity = std::time::Instant::now();
    timer_user = std::time::Instant::now();

    while !rl.window_should_close() {

        let duration_gravity = timer_gravity.elapsed();
        let duration_user = timer_user.elapsed();
        let mut must_move_down = false;

        // Check the user input each 0.06 seconds to move the tetromino one 
        // block down or one block to the sides (never both at the same time).
        if duration_user >= std::time::Duration::from_secs_f32(0.06) {
            must_move_down = rl.is_key_down(KeyboardKey::KEY_S);
            timer_user = std::time::Instant::now();

            if rl.is_key_down(KeyboardKey::KEY_A) {
                actual.move_to_side(Direction::Left);
            
            } else if rl.is_key_down(KeyboardKey::KEY_D) {
                actual.move_to_side(Direction::Right);
            }
        } 
        
        // Each 0.65 seconds move the tetromino one block down.
        // This is usually called 'gravity'.
        if duration_gravity >= std::time::Duration::from_secs_f32(0.65) {
            timer_gravity = std::time::Instant::now();
            must_move_down = true;
        }

        // When trying to move the tetromino one block down, check if 
        // the tetromino collided with the floor or other tetromino.
        // If this happens, pick the next tetromino and merge the actual 
        // tetromino with the rest blocks.
        if must_move_down && actual.move_down(&mut space) {
            actual = next;
            actual.x = main_frame.def_x;
            actual.y = main_frame.def_y;

            next = Tetronimo::new(
                dist.sample(&mut rng),
                next_frame.def_x, 
                next_frame.def_y);
            // TODO update points
            // TODO eliminate complete rows
        }

        // Rotate the tetromino (if possible) only once.
        if rl.is_key_pressed(KeyboardKey::KEY_UP) {
            actual.rotate(&space);
        }

        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::BLACK);

        main_frame.draw_space(&space, &mut d);
        main_frame.draw_tetronimo(&actual, &mut d);
        next_frame.draw_tetronimo(&next, &mut  d);
        main_frame.draw_self(&mut d);
        next_frame.draw_self(&mut d);

        d.draw_text(&format!("Shapes: {}", shapes), info_x, 7 * TILE_SIZE, FONT_SIZE, FONT_COLOR);
        d.draw_text(&format!("Rows: {}", rows),     info_x, 8 * TILE_SIZE, FONT_SIZE, FONT_COLOR);
        d.draw_text(&format!("Score: {}", score),   info_x, 9 * TILE_SIZE, FONT_SIZE, FONT_COLOR);
    }
}
