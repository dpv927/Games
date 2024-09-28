use raylib::prelude::*;
use rand_distr::{Normal, Uniform, Distribution};

const DIMENSIONS: usize = 3;
const NUM_POINTS: usize = 1000;
const SPHERE_RAD: f32 = 200.;


fn main() {
    let normal = Normal::new(0., 1.).unwrap();
    let mut rng = rand::thread_rng();

    // Y ~ MVN(0, I(d)) matrix. Must be filled up 
    // with a standard distribution.
    let mut y: [[f32; DIMENSIONS]; NUM_POINTS] 
        = [[0.; DIMENSIONS]; NUM_POINTS];

    for point in 0..NUM_POINTS {
        // Generate point (x, y, z) in Y
        for dim in 0..DIMENSIONS {
            y[point][dim] = normal.sample(&mut rng);
        }
    }

    // U ~ U(0,1) array. Must be filled up with 
    // a uniform distribution.
    let mut u: [f32; NUM_POINTS] = [0.; NUM_POINTS];
    let uniform = Uniform::new(0., 1.);

    for point in 0..NUM_POINTS {
        u[point] = uniform.sample(&mut rng);
    }

    // R = radius * (U^(1/DIMENSIONS)). Will contain 
    // a proportional radius to 3rd-root of U.
    let mut r = [0.; NUM_POINTS];

    for point in 0..NUM_POINTS {
        r[point] = SPHERE_RAD * 
            u[point].powf(1.0 / DIMENSIONS as f32);
    }

    // Calculate the norm of each point in Y.
    // The norm of a point (x, y, z) is sqrt(x^2 + y^2 + z^2)
    let mut norm_y: [f32; NUM_POINTS] = [0.; NUM_POINTS];

    for point in 0..NUM_POINTS {
        let y_point = &y[point];
        norm_y[point] = (y_point[0].powi(2) + y_point[1].powi(2)
            + y_point[2].powi(2)).sqrt();
    }

    // Generate X, the points uniformly distributed 
    // in the d-dimensional ball
    let mut x = y;

    for point in 0..NUM_POINTS {
        let y_point = &y[point];
        let norm = norm_y[point];
        let scaling_factor = r[point] / norm;

        for dim in 0..DIMENSIONS {
            x[point][dim] = y_point[dim] * scaling_factor;
        }
    }
    
    // SHOW THE GENERATED 
    // POINTS

    let (mut rl, thread) = raylib::init()
        .size(SPHERE_RAD as i32 * 7, SPHERE_RAD as i32 * 7)
        .title("Uniform point generation in a ellipse")
        .log_level(TraceLogLevel::LOG_ERROR)
        .build();

    let mut camera = Camera3D::perspective(
        /* Pos */ Vector3::new(300., 300., 300.),
        /* Target */ Vector3::new(0., 0., 0.),
        /* Up */ Vector3::new(0., 1., 0.),
        /* Fovy */ 89.
    );

    while !rl.window_should_close() {
        if rl.is_key_down(KeyboardKey::KEY_S) { camera.position.y -= 20.0; }
        if rl.is_key_down(KeyboardKey::KEY_W) { camera.position.y += 20.0; }
        if rl.is_key_down(KeyboardKey::KEY_A) { camera.position.z += 20.0; }
        if rl.is_key_down(KeyboardKey::KEY_D) { camera.position.z -= 20.0; }
        if rl.is_key_down(KeyboardKey::KEY_UP) { camera.position.x -= 20.0; }
        if rl.is_key_down(KeyboardKey::KEY_DOWN) { camera.position.x += 20.0; }

        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::BLACK);

        let mut d3 = d.begin_mode3D(camera);
        for point in x {
            d3.draw_sphere(Vector3::new(point[0], point[1], point[2]), 
                2., Color::WHITE);
        }

        d3.draw_cube_wires(Vector3::new(0., 0., 0.), 
            400., 400., 400., Color::WHITE);
    }
}
