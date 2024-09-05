use crate::room::Room;
use crate::graph::Connection;
use rand::prelude::*;
use std::collections::HashMap;
use std::hash::RandomState;

const ROOM_WIDTH_MIN:  u32 = 2;
const ROOM_WIDTH_MAX:  u32 = 12;
const ROOM_HEIGHT_MIN: u32 = 2;
const ROOM_HEIGHT_MAX: u32 = 12;

fn aprox_coordinate(n: f32, m: f32) -> i32 {
    ((n / m).round() as i32) * (m as i32)
}

pub fn generate_rooms(
    num_rooms: u32,
    origin_x: i32,
    origin_y: i32,
    tile_width: u32,
    spawn_radius: u32,
) -> Vec<Room> {

    let mut rng = rand::thread_rng();
    let mut rooms = vec![];

    for _ in 0..num_rooms {
        let rnd_radius = (spawn_radius as f32) * (rng.gen::<f32>().sqrt());
        let angle = rng.gen::<f32>().sqrt() * 2.0 * std::f32::consts::PI;

        rooms.push(Room {
            x: aprox_coordinate((rnd_radius * angle.cos()) + origin_x as f32, tile_width as f32),
            y: aprox_coordinate((rnd_radius * angle.sin()) + origin_y as f32, tile_width as f32),
            width: (rng.gen_range(ROOM_WIDTH_MIN..ROOM_WIDTH_MAX) * tile_width) as i32,
            height: (rng.gen_range(ROOM_HEIGHT_MIN..ROOM_HEIGHT_MAX) * tile_width) as i32,
            main: false,
            id: usize::MAX,
        });
    }
    rooms
}

pub fn select_rooms(rooms: &mut Vec<Room>, threshold: f32) -> Vec<&Room> {
    let (average_width, average_height) = rooms.iter().fold((0.0, 0.0), 
        |(acc_width, acc_height), room| {
            (acc_width + room.width as f32, acc_height + room.height as f32)
    });

    let rooms_count = rooms.len() as f32;
    let width_threshold  = average_width/rooms_count  * threshold;
    let height_threshold = average_height/rooms_count * threshold;

    let mut selected_rooms: Vec<&Room> = vec![];
    let mut id_count = 0;

    for room in rooms {
        if room.width >= width_threshold as i32 && room.height >= height_threshold as i32 {
            room.main = true;
            room.id = id_count;
            id_count += 1;
            selected_rooms.push(room);
        }
    }
    selected_rooms
}

pub fn separate_rooms(rooms: &mut Vec<Room>, tile_width: u32) {
    let mut rooms_overlap: bool;

    loop {
        // Reset overlap check
        rooms_overlap = false;

        for i in 0..rooms.len() {
            let (left, right) = rooms.split_at_mut(i + 1);
            let actual = &mut left[i];

            let mw_i = (actual.width) >> 1;
            let mh_i = (actual.height) >> 1;

            for other in right.iter_mut() {
                if !actual.is_colliding_with(other) {
                    continue;
                }

                let mw_j = (other.width) >> 1;
                let mh_j = (other.height) >> 1;

                // Differential betteen both rooms coordinates
                let dx = (other.x + mw_j) - (actual.x + mw_i);
                let dy = (other.y + mh_j) - (actual.y + mh_i);

                // Instead of overlap, they are overlap/2 to avoid doing 
                // the same operation twice at the 'if's below.
                let overlap_x = (mw_i + mw_j) - dx.abs();
                let overlap_y = (mh_i + mh_j) - dy.abs();

                if overlap_x < overlap_y {
                    if dx > 0 {
                        actual.x -= overlap_x >> 1;
                        other.x  += overlap_x >> 1;
                    } else {
                        actual.x += overlap_x >> 1;
                        other.x  -= overlap_x >> 1;
                    }
                } else {
                    if dy > 0 {
                        actual.y -= overlap_y >> 1;
                        other.y  += overlap_y >> 1;
                    } else {
                        actual.y += overlap_y >> 1;
                        other.y  -= overlap_y >> 1;
                    }
                }

                // Ajustar las coordenadas a la cuadrícula
                actual.x = aprox_coordinate(actual.x as f32, tile_width as f32) as i32;
                actual.y = aprox_coordinate(actual.y as f32, tile_width as f32) as i32;
                other.x  = aprox_coordinate(other.x as f32,  tile_width as f32) as i32;
                other.y  = aprox_coordinate(other.y as f32,  tile_width as f32) as i32;
                rooms_overlap = true;
            }
        }

        if !rooms_overlap {
            break;
        }
    }
}

pub fn calculate_graph(selected_rooms: &Vec<&Room>) -> Vec<Connection> {
    let room_hashes = vec![];
    let mut map: HashMap<(i32,i32), i32> = HashMap::with_capacity(10);


    // map.insert(1, 2);

    room_hashes
}
