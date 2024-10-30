use raylib::prelude::*;
use crate::ball::*;
use crate::paddle::*;
mod ball;
mod paddle;

const WINDOW_SIZE: i32 = 1000;
const MAX_SOUND_FRAMES: i32 = 5;

fn main() {

    let (mut rl, thread) = raylib::init()
        .size(1000, 1000)
        .title("Pong")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();
    rl.set_target_fps(60);

    let player1_texture = rl.load_texture(&thread, "player1.png").unwrap();
    let player2_texture = rl.load_texture(&thread, "player2.png").unwrap();
    let wall_texture = rl.load_texture(&thread, "wall.png").unwrap();

    let audio = RaylibAudio::init_audio_device().unwrap();
    let mut sound = audio.new_sound("beep.wav").unwrap();
    let mut sound_frames = 0;

    let mut player1 = Paddle::new(WINDOW_SIZE, PaddleSide::Player1, player1_texture);
    let mut player2 = Paddle::new(WINDOW_SIZE, PaddleSide::Player2, player2_texture);
    let mut ball = Ball::new(WINDOW_SIZE);

    while !rl.window_should_close() {
        if sound_frames == MAX_SOUND_FRAMES {
            sound_frames = 0;
            sound.stop();
        }

        sound_frames = sound_frames + 1;
        if ball.compute_wall_collisions(WINDOW_SIZE) && !sound.is_playing() {
            sound.play();
        }

        player1.compute_movement(WINDOW_SIZE, &rl);
        player2.compute_movement(WINDOW_SIZE, &rl);

        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::new(100,85,85,255));

        // Draw the background (metal plates and the brown frame)
        let wall_rect = Rectangle::new(0., 0., wall_texture.width as f32, wall_texture.height as f32);
        let mut wall_rect_dst = Rectangle::new(0., 0., (WINDOW_SIZE/3) as f32, (WINDOW_SIZE/3) as f32);

        for i in 0..3 {
            wall_rect_dst.y = ((i as i32) * (WINDOW_SIZE/3)) as f32;

            for j in 0..3 {
                wall_rect_dst.x = ((j as i32) * (WINDOW_SIZE/3)) as f32;
                d.draw_texture_pro(&wall_texture, wall_rect, wall_rect_dst, Vector2::zero(), 0., Color::WHITE)
            }
        }

            d.draw_rectangle_lines_ex(Rectangle::new(0., 0., WINDOW_SIZE as f32, WINDOW_SIZE as f32),
                paddle::PADDLE_MARGIN as f32, Color::new(100,85,85,255));

        // Draw game
        ball.draw(&mut d);
        player1.draw(&mut d);
        player2.draw(&mut d);
    }
}
