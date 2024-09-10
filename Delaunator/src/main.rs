use raylib::prelude::*;
use delaunator::*;
use rand::Rng;


const EDGE_COLOR  : Color = Color::new(245, 245, 245, 40);
const VERTEX_COLOR: Color = Color::RAYWHITE;
const INIT_POINTS: usize = 15;


fn draw_triangulation(points: &Vec<Point>, triangles: &Vec<usize>, handle: &mut RaylibDrawHandle) {
    for i in (0..triangles.len()).step_by(3) {
        handle.draw_line( // Draw line from vertex V1 to vertex V2 
            points[triangles[i]].x as i32,   points[triangles[i]].y as i32,
            points[triangles[i+1]].x as i32, points[triangles[i+1]].y as i32,
            EDGE_COLOR);
        
        handle.draw_line( // Draw line from vertex V1 to vertex V3 
            points[triangles[i]].x as i32,   points[triangles[i]].y as i32,
            points[triangles[i+2]].x as i32, points[triangles[i+2]].y as i32,
            EDGE_COLOR);

        handle.draw_line( // Draw line from vertex V2 to vertex V3 
            points[triangles[i+1]].x as i32, points[triangles[i+1]].y as i32,
            points[triangles[i+2]].x as i32, points[triangles[i+2]].y as i32,
            EDGE_COLOR);
    }
}

fn draw_vertices(points: &Vec<Point>, handle: &mut RaylibDrawHandle) {
    for point in points {
        handle.draw_circle(point.x as i32, point.y as i32, 5., VERTEX_COLOR);
    }
}

fn generate_random_points(max_width: i32, max_height: i32) -> Vec<Point> {
    let mut points = Vec::with_capacity(INIT_POINTS);
    let mut rng = rand::thread_rng();

    for _ in 0..INIT_POINTS {
        points.push(Point{
            x: rng.gen::<f64>() * max_width as f64,
            y: rng.gen::<f64>() * max_height as f64
        });
    } 

    points
}

fn scale_window_to_monitor(width_ratio: f32, height_ratio: f32, handle: &mut RaylibHandle) -> (i32, i32) {
    // Get the user's monitor propierties.
    let monitor_width  = window::get_monitor_width(window::get_current_monitor());
    let monitor_height = window::get_monitor_height(window::get_current_monitor());
    let window_width  = (monitor_width as f32 * width_ratio) as i32;
    let window_height = (monitor_height as f32 * height_ratio) as i32;

    // Apply the scale to the window.
    handle.set_window_position((monitor_width - window_width)/2, (monitor_height - window_height)/2);
    handle.set_window_size(window_width, window_height);
    (window_width, window_height)
}


fn main() {

    let (mut rl, thread) = raylib::init()
        .size(0, 0)
        .title("Delaunator")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();

    let (w, h) = scale_window_to_monitor(0.6, 0.7, &mut rl);
    let mut points = generate_random_points(w, h);

    while !rl.window_should_close() {
        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::BLACK);

        // Check user input and see if we can add another vertex.
        if d.is_mouse_button_down(MouseButton::MOUSE_BUTTON_LEFT) {
            let point = Point{ 
                x: d.get_mouse_x() as f64,
                y: d.get_mouse_y() as f64 
            };

            if !points.contains(&point) {
                points.push(point);
            }
        }

        let result = triangulate(&points);
        draw_triangulation(&points, &result.triangles, &mut d);
        draw_vertices(&points, &mut  d);
    }
}
