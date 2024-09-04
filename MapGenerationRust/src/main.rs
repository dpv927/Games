use raylib::prelude::*;
mod engine;
mod room;

const TILE_WIDTH: u32 = 20;
const NUM_ROOMS: u32 = 100;
const SPAWN_RADIUS: u32 = 5 * TILE_WIDTH;


fn main() {
    let (mut rl, thread) = raylib::init()
        .size(0, 0)
        .title("Map Generation")
        .build();
    rl.set_target_fps(60);

    let win_w: i32;
    let win_h: i32;

    { // Adapt the window size to the user's monitor
        let monitor = window::get_current_monitor();
        let mon_w = window::get_monitor_width(monitor);
        let mon_h = window::get_monitor_height(monitor);
        win_w = (mon_w as f32 * 0.6) as i32;
        win_h = (mon_h as f32* 0.8) as i32;
        
        rl.set_window_size(win_w, win_h);
        rl.set_window_position((mon_w - win_w) >> 1, (mon_h - win_h) >> 1);
    }

    let mut rooms = engine::generate_rooms(NUM_ROOMS, win_w >> 1, win_h >> 1,
        TILE_WIDTH, SPAWN_RADIUS);
    _ = engine::select_rooms(&mut rooms, 1.35);
    engine::separate_rooms(&mut rooms, TILE_WIDTH);

    let mut camera = Camera2D{ 
        offset: Vector2::new(0.0, 0.0),
        target: Vector2::new(0.0, 0.0),
        rotation: 0.0,
        zoom: 1.0,
    };

    while !rl.window_should_close() {
        if rl.is_key_down(KeyboardKey::KEY_W) { camera.target.y -= 25.0; } 
        if rl.is_key_down(KeyboardKey::KEY_S) { camera.target.y += 25.0; }
        if rl.is_key_down(KeyboardKey::KEY_D) { camera.target.x += 25.0; } 
        if rl.is_key_down(KeyboardKey::KEY_A) { camera.target.x -= 25.0; }

        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::BLACK);

        let mut d2 = d.begin_mode2D(camera); 
        for room in &rooms {
            room.draw_room(TILE_WIDTH, &mut d2);
        }
    }
}
