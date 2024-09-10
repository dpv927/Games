use rand::Rng;
use raylib::prelude::*;

struct Point {
    x: i32,
    y: i32
}

const BASE_WIN_WIDTH: i32 = 1080;
const BASE_POINT_RADIUS: f32 = 5.;
const NUM_POINTS: usize = 1000;
const BASE_TILE_WIDTH: i32 = 20;
const SPAWN_RADIUS: i32 = 20;


fn aprox_point(n: f32, m: f32) -> f32 {
    (n/m).round() * m
}


fn main() {
    let (mut rl, thread) = raylib::init()
        .size(0, 0)
        .title("Map Generation")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();
    rl.set_target_fps(20);

    let win_half: i32;
    let win_width: i32;
    { // Adapt the window size to the user's monitor
        let monitor = window::get_current_monitor();
        let mon_h = window::get_monitor_height(monitor);
        let mon_w = window::get_monitor_width(monitor);
        win_width = mon_h >> 1;  
        win_half  = win_width >> 1;
        
        rl.set_window_size(win_width, win_width);
        rl.set_window_position((mon_w - win_width) >> 1, (mon_h - win_width) >> 1);
    }

    let tile_width = ((win_half << 1) * BASE_TILE_WIDTH)/BASE_WIN_WIDTH;
    let point_radius = ((win_half as f32 * 2.) * BASE_POINT_RADIUS)/BASE_WIN_WIDTH as f32;

    let mut rng = rand::thread_rng();
    let mut points: Vec<Point> = vec![];
    points.reserve(NUM_POINTS);

    for _ in 0..NUM_POINTS {
        let r = (tile_width * SPAWN_RADIUS) as f32 * rng.gen::<f32>().sqrt();
        let theta = 2.0 * std::f32::consts::PI * rng.gen::<f32>(); 

        points.push(Point{
            x: aprox_point(r * theta.cos(), tile_width as f32) as i32,
            y: aprox_point(r * theta.sin(), tile_width as f32) as i32 
        });
    }

    while !rl.window_should_close() {
        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::BLACK);
        let mut i = win_half; 

        loop { // Draw half of the grid (right)
            d.draw_line(i, 0, i, win_width, Color::new(245, 245, 245, 40));
            d.draw_line(0, i, win_width, i, Color::new(245, 245, 245, 40));
            if i >= win_width { break; }
            i += tile_width;
        }

        i = win_half; 

        loop { // Draw half of the grid (left)
            d.draw_line(i, 0, i, win_width, Color::new(245, 245, 245, 40));
            d.draw_line(0, i, win_width, i, Color::new(245, 245, 245, 40));
            if i <= 0 { break; }
            i -= tile_width;
        }

        // Draw circle points
        for i in 0..points.len() {
            d.draw_circle(
                points[i].x + win_half, 
                points[i].y + win_half,
                point_radius,
                Color::RAYWHITE);
        }
    }    
}

