use rand::Rng;
use rand::rngs::ThreadRng;
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
const GRID_COLOR:  Color = Color::new(245, 245, 245, 40);
const POINT_COLOR: Color = Color::RAYWHITE;


fn aprox_point(n: f32, m: f32) -> f32 {
    (n/m).round() * m
}

fn generate_points(points: &mut Vec<Point>, tile_width: i32, rng: &mut ThreadRng) {
    if !points.is_empty() { 
        points.clear();
    }

    for _ in 0..NUM_POINTS {
        let r = (tile_width * SPAWN_RADIUS) as f32 * rng.gen::<f32>().sqrt();
        let theta = 2.0 * std::f32::consts::PI * rng.gen::<f32>(); 

        points.push(Point{
            x: aprox_point(r * theta.cos(), tile_width as f32) as i32,
            y: aprox_point(r * theta.sin(), tile_width as f32) as i32 
        });
    }
}

fn draw_points(points: &Vec<Point>, offset: i32, point_radius: f32, handle: &mut RaylibDrawHandle) {
    for point in points {
        handle.draw_circle(
            point.x + offset, 
            point.y + offset,
            point_radius,
            POINT_COLOR);
    }
}

fn draw_grid(max_width: i32, tile_width: i32, handle: &mut RaylibDrawHandle) {
     let mut i = max_width/2; 

    loop { // Draw half of the grid (right)
        handle.draw_line(i, 0, i, max_width, GRID_COLOR);
        handle.draw_line(0, i, max_width, i, GRID_COLOR);
        if i >= max_width { break; }
        i += tile_width;
    }

    i = max_width/2; 
    
    loop { // Draw half of the grid (left)
        handle.draw_line(i, 0, i, max_width, GRID_COLOR);
        handle.draw_line(0, i, max_width, i, GRID_COLOR);
        if i <= 0 { break; }
        i -= tile_width;
    }
}

fn scale_window_to_monitor(width_ratio: f32, handle: &mut RaylibHandle) -> (i32, i32) {
    // Get the user's monitor propierties.
    let monitor_width  = window::get_monitor_width(window::get_current_monitor());
    let monitor_height = window::get_monitor_height(window::get_current_monitor());
    let window_width  = (monitor_width as f32 * width_ratio) as i32;

    // Apply the scale to the window.
    handle.set_window_position((monitor_width - window_width)/2, (monitor_height - window_width)/2);
    handle.set_window_size(window_width, window_width);
    (window_width, window_width)
}


fn main() {
    let (mut rl, thread) = raylib::init()
        .size(0, 0)
        .title("Map Generation")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();
    rl.set_target_fps(10);

    // Scale the window to the user's monitor resolution.
    let (window_width, _) = scale_window_to_monitor(0.4, &mut rl);
    let ratio = window_width as f32/BASE_WIN_WIDTH as f32; 
    
    // Apply the new scale to some elements.
    let tile_width   = BASE_TILE_WIDTH * ratio as i32;
    let point_radius = BASE_POINT_RADIUS * ratio;

    let mut rng = rand::thread_rng();
    let mut points: Vec<Point> = vec![];
    points.reserve(NUM_POINTS);

    while !rl.window_should_close() {
        // Generate a new set of points.
        generate_points(&mut points, tile_width, &mut rng);

        // Draw the new point set.
        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::BLACK);

        draw_grid(window_width, tile_width, &mut d);
        draw_points(&points, window_width/2, point_radius, &mut d);
    }    
}

