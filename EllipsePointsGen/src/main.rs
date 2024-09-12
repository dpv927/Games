use raylib::prelude::*;
use rand_distr::{Normal, Uniform, Distribution};

fn aprox_point(n: f32, m: f32) -> f32 {
    (n/m).round() * m
}

// This function can be easily optimized, but its intention is to show the
// basic procedure to generate points uniformly inside a ellipse. 
fn rand_ellipse(n: usize, horizontal_axis: i32, vertical_axis: i32) -> Vec<[f32;2]> {
    
    // Generate a matrix X ~ N(0, I_d)
    let mut x: Vec<[f32; 2]> = Vec::with_capacity(n);
    let normal = Normal::new(0.0, 1.0).unwrap();
    let mut rng = rand::thread_rng(); 

    for _ in 0..n {
        let mut row: [f32;2] = [0.0;2];
        row[0] = normal.sample(&mut rng);
        row[1] = normal.sample(&mut rng);
        x.push(row);
    }

    // Generate a vector U ~ U(0,1), then apply r = u^(1/d),
    // being d = 2 (dimensions x, y), so u^(1/d) = sqrt(u).
    let mut r: Vec<f32> = Vec::with_capacity(n);
    let uniform = Uniform::new(0.0, 1.0);
    
    for _ in 0..n {
        let u: f32 = uniform.sample(&mut rng);
        r.push(u.sqrt());
    }

    // Compute the norms of X. Each row of X has the form (x1, x2),
    // and in general the Euclidean norm is ||X|| = sqrt(x0^2 + x1^2...xd^2),
    // being d = 2 (because we have 2 dimensions x,y), 
    // ||X|| = sqrt(x0^2 + x1^2).
    let mut norm_x: Vec<f32> = vec![];
    
    for i in 0..n {
        norm_x.push((x[i][0].powi(2) + x[i][1].powi(2)).sqrt());
    }
    
    // Now we scale the points so they are uniformly distributed in the unit 
    // disk. Z = (r * X) / ||X|| for each point.
    // let mut z: Vec<[f32; 2]> = Vec::with_capacity(n);
    let mut z = x; 

    for i in 0..n {
        z[i][0] = (z[i][0]/norm_x[i]) * r[i];
        z[i][1] = (z[i][1]/norm_x[i]) * r[i];
    }

    // Transform the unit disk points into an ellipse by scaling with the axes.
    let mut ellipse_points: Vec<[f32; 2]> = Vec::with_capacity(n);
    
    for i in 0..n {
        let mut row: [f32; 2] = [0.0; 2];
        row[0] = z[i][0] * horizontal_axis as f32;
        row[1] = z[i][1] * vertical_axis as f32;
        ellipse_points.push(row);
    }

    ellipse_points
}

const BASE_WIN_WIDTH: i32 = 1080;
const BASE_POINT_RADIUS: f32 = 5.;
const NUM_POINTS: usize = 1000;
const VERTICAL_AXIS_TILES: i32 = 12;
const HORIZONTAL_AXIS_TILES: i32 = 20;
const BASE_TILE_WIDTH: i32 = 25;

fn main() {
 
    let (mut rl, thread) = raylib::init()
        .size(0, 0)
        .title("Uniform point generation in a ellipse")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();
    rl.set_target_fps(20);

    let win_half: i32;
    let win_width: i32;
    { // Adapt the window size to the user's monitor
        let monitor = window::get_current_monitor();
        let mon_h = window::get_monitor_height(monitor);
        let mon_w = window::get_monitor_width(monitor);
        win_width = mon_w * 2/5;
        win_half  = win_width >> 1;
        
        rl.set_window_size(win_width, win_width);
        rl.set_window_position((mon_w - win_width) >> 1, (mon_h - win_width) >> 1);
    }

    let tile_width = ((win_half << 1) * BASE_TILE_WIDTH)/BASE_WIN_WIDTH;
    let point_radius = ((win_half as f32 * 2.) * BASE_POINT_RADIUS)/BASE_WIN_WIDTH as f32;
    let points = rand_ellipse(
        NUM_POINTS,
        HORIZONTAL_AXIS_TILES * tile_width,
        VERTICAL_AXIS_TILES * tile_width
    );

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

        for point in &points {
            let x = point[0];
            let y = point[1];
            d.draw_circle(
                aprox_point(x, tile_width as f32) as i32 + win_half,
                aprox_point(y, tile_width as f32) as i32 + win_half,
                point_radius,
                Color::RAYWHITE
            );
        }
    }
}

