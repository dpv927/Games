use raylib::prelude::*;
mod engine;
mod room;
mod graph;

const TILE_WIDTH: u32 = 20;
const NUM_ROOMS: u32 = 100;
const SPAWN_RADIUS: u32 = 20 * TILE_WIDTH;


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

    let mut engine = engine::Pdg::new();
    engine.generate_rooms(NUM_ROOMS, win_w >> 1, win_h >> 1, TILE_WIDTH, SPAWN_RADIUS);
    engine.select_rooms(1.35);
    engine.separate_rooms(TILE_WIDTH);
    engine.calculate_graph();

    let mut camera = Camera2D{ 
        offset: Vector2::new(0., 0.),
        target: Vector2::new(0., 0.),
        rotation: 0.,
        zoom: 1.,
    };

    while !rl.window_should_close() {
        if rl.is_key_down(KeyboardKey::KEY_W) { camera.target.y -= 25.0; } 
        if rl.is_key_down(KeyboardKey::KEY_S) { camera.target.y += 25.0; }
        if rl.is_key_down(KeyboardKey::KEY_D) { camera.target.x += 25.0; } 
        if rl.is_key_down(KeyboardKey::KEY_A) { camera.target.x -= 25.0; }

        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color{r: 12, g: 62, b: 84, a: 255});

        let mut d2 = d.begin_mode2D(camera); 
        for room in &engine.rooms {
            room.draw_room(&mut d2);
        }

        for connection in &engine.connections {
            // Draw each connected main room in the generated rooms
            let src = &engine.rooms[engine.selected_rooms[connection.src]];
            let dest = &engine.rooms[engine.selected_rooms[connection.dest]];
            
            d2.draw_line_ex(
                Vector2{ 
                    x: src.x as f32 + (src.width as f32)/2.,
                    y: src.y as f32 + (src.height as f32)/2. 
                },
                Vector2{ 
                    x: dest.x as f32 + (dest.width as f32)/2.,
                    y: dest.y as f32 + (dest.height as f32)/2. 
                },
                5., Color{r: 241, g: 224, b: 90, a: 255});
        }
    }
}
