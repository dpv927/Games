use raylib::prelude::*;
use delaunator::*;

fn main() {

    let points = vec![
        Point { x: 158., y: 165. },
        Point { x: 576., y: 101. },
        Point { x: 457., y: 289. },
        Point { x: 142., y: 587. },
        Point { x: 419., y: 701. },
        Point { x: 607., y: 523. },
        Point { x: 448., y: 478. }
    ];

    let result = triangulate(&points);

    for i in (0..result.triangles.len()).step_by(3) {
        println!("Triangle points: [[{}, {}], [{}, {}], [{}, {}]]",
            points[result.triangles[i]].x,   points[result.triangles[i]].y,
            points[result.triangles[i+1]].x, points[result.triangles[i+1]].y,
            points[result.triangles[i+2]].x, points[result.triangles[i+2]].y)
    }

    let (mut rl, thread) = raylib::init()
        .size(800, 800)
        .title("Delaunator")
        .build();

    while !rl.window_should_close() {
        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::RAYWHITE);

        for point in &points {
            d.draw_circle(point.x as i32, point.y as i32, 5., Color::BLACK);
        }
    
        for i in (0..result.triangles.len()).step_by(3) {
            d.draw_line( // Draw line from vertex V1 to vertex V2 
                points[result.triangles[i]].x as i32,   points[result.triangles[i]].y as i32,
                points[result.triangles[i+1]].x as i32, points[result.triangles[i+1]].y as i32,
                Color::BLUE);
            d.draw_line( // Draw line from vertex V1 to vertex V3 
                points[result.triangles[i]].x as i32,   points[result.triangles[i]].y as i32,
                points[result.triangles[i+2]].x as i32, points[result.triangles[i+2]].y as i32,
                Color::BLUE);
            d.draw_line( // Draw line from vertex V2 to vertex V3 
                points[result.triangles[i+1]].x as i32, points[result.triangles[i+1]].y as i32,
                points[result.triangles[i+2]].x as i32, points[result.triangles[i+2]].y as i32,
                Color::BLUE);
        }
    }
}
