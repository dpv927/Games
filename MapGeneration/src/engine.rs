use std::collections::HashMap;
use rand::prelude::*;
use crate::room::Room;
use crate::graph::*;

const ROOM_WIDTH_MIN:  u32 = 3;
const ROOM_WIDTH_MAX:  u32 = 16;
const ROOM_HEIGHT_MIN: u32 = 3;
const ROOM_HEIGHT_MAX: u32 = 16;

pub struct Pdg {
    pub rooms: Vec<Room>,
    pub selected_rooms: Vec<usize>,
    pub graph: Vec<Edge>,
    pub connections: Vec<Connection>
}

impl Pdg {

    pub fn new() -> Pdg {
        Pdg {
            rooms: vec![],
            selected_rooms: vec![],
            graph: vec![],
            connections: vec![],
        }
    }

    ///
    /// generates rooms randomly inside a radius, centered in a given coordinates
    /// (x, y). the radius is measured in tiles, and the tiles are measured
    /// in pixels.
    ///
    pub fn generate_rooms(&mut self, num_rooms: u32, x: i32, y: i32, 
        tile_width: u32, spawn_radius: u32) {

        let mut rng = rand::thread_rng();

        for i in 0..num_rooms {
            let rnd_radius = (spawn_radius as f32) * (rng.gen::<f32>().sqrt());
            let angle = rng.gen::<f32>().sqrt() * 2.0 * std::f32::consts::PI;

            self.rooms.push(Room {
                x: aprox_coordinate((rnd_radius * angle.cos()) + x as f32, tile_width as f32),
                y: aprox_coordinate((rnd_radius * angle.sin()) + y as f32, tile_width as f32),
                width: (rng.gen_range(ROOM_WIDTH_MIN..ROOM_WIDTH_MAX) * tile_width) as i32,
                height: (rng.gen_range(ROOM_HEIGHT_MIN..ROOM_HEIGHT_MAX) * tile_width) as i32,
                main: false,
                id: i as usize,
            });
        }
    }

    /// 
    /// Given a vector of generated rooms (Pdg.rooms), calculates which of 
    /// all the rooms have a larger than average area and exceed a certain 
    /// threshold. 
    ///
    /// Also stores in 'Pdg.selected_rooms' the indexes of each selected 
    /// room at 'Pdg.rooms'. F.e, if we want to obtain a selected room from
    /// 'Pdg.rooms', we only have to do `pdg.rooms[pdg.selected_rooms[id]]`.
    ///
    pub fn select_rooms(&mut self, threshold: f32) {
    
        let (average_width, average_height) = self.rooms.iter().fold((0., 0.), 
            |(acc_width, acc_height), room| {
                (acc_width + room.width as f32, acc_height + room.height as f32)
        });

        let rooms_count = self.rooms.len() as f32;
        let width_threshold  = (average_width/rooms_count  * threshold) as i32;
        let height_threshold = (average_height/rooms_count * threshold) as i32;

        for i in 0..self.rooms.len() {
            let room = &mut self.rooms[i];

            if room.width >= width_threshold && room.height >= height_threshold {
                self.selected_rooms.push(i);
                room.main = true;
            }
        }
    }

    /// 
    /// When generating the rooms at 'Pdg.generate_rooms', all the rooms are 
    /// accummulated at one radius, which causes some rooms to be overlapped
    /// and we want them to be side to side or at least separated at some
    /// distance (in the worst scenario).
    ///
    pub fn separate_rooms(&mut self, tile_width: u32) {
        let mut rooms_overlap: bool;

        loop {
            // reset overlap check
            rooms_overlap = false;

            for i in 0..self.rooms.len() {
                let (left, right) = self.rooms.split_at_mut(i + 1);
                let actual = &mut left[i];

                let mw_i = (actual.width) >> 1;
                let mh_i = (actual.height) >> 1;

                for other in right.iter_mut() {
                    if !actual.is_colliding_with(other) {
                        continue;
                    }

                    let mw_j = (other.width) >> 1;
                    let mh_j = (other.height) >> 1;

                    // differential betteen both rooms coordinates
                    let dx = (other.x + mw_j) - (actual.x + mw_i);
                    let dy = (other.y + mh_j) - (actual.y + mh_i);

                    // instead of overlap, they are overlap/2 to avoid doing 
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

                    // ajustar las coordenadas a la cuadrícula
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

    pub fn calculate_graph(&mut self) {
        let mut room_hashes: HashMap<(i32,i32), usize> = HashMap::new();
        let mut coordinates: Vec<delaunator::Point> = vec![];

        room_hashes.reserve(self.selected_rooms.len());
        coordinates.reserve(self.selected_rooms.len());

        for room_index in 0..self.selected_rooms.len() {
            let room = &self.rooms[self.selected_rooms[room_index]];

            // Calculate every room middle coordinate (x,y).
            // Note that we get rid of the decimal part.
            let middle_x = (room.x + room.width/2) as f64;
            let middle_y = (room.y + room.height/2) as f64;

            // We cant use f64 at the HashMap, so we use i32.
            // As every room is separated, we dont need to worry about 
            // decimal precission.
            coordinates.push(delaunator::Point{x: middle_x, y: middle_y});
            room_hashes.insert((middle_x as i32, middle_y as i32), room_index);
        }


        // Calculate Delaunay triangulation. Delaunator returns an array
        // [a,b,..] where each element is the index of a point in 'coordinates'
        // that conforms a triangle.
        let triangles = delaunator::triangulate(&coordinates).triangles;

        // We are shure that each coordinate maps to a single room id 
        // in the room_hashes map, but we have to notice if it 
        // somehow fails.
        let recover_id = |opt: Option<&usize>, v: (i32,i32)| -> usize { 
            match opt {
                Some(id) => *id,
                None => { 
                    let (src, dest) = v;
                    panic!("unknown vertex ({},{}).", src, dest) 
                },
            }
        };

        // Distance betteen two points (x1,y1) and (x2,y2) as a Integer.
        let point_distance = |x1: i32, y1: i32, x2: i32, y2: i32| -> usize {
            (((x2 - x1).pow(2) + (y2 - y1).pow(2)) as f32).sqrt() as usize
        };
 
        for i in (0..triangles.len()).step_by(3) {
            // Get each vertex of a triangle (Three connected rooms). 
            let v1 = (coordinates[triangles[i]].x as i32,   coordinates[triangles[i]].y as i32);
            let v2 = (coordinates[triangles[i+1]].x as i32, coordinates[triangles[i+1]].y as i32);
            let v3 = (coordinates[triangles[i+2]].x as i32, coordinates[triangles[i+2]].y as i32);
        
            // Get each vertex the associated room ID
            let hv1 = recover_id(room_hashes.get(&v1), v1);
            let hv2 = recover_id(room_hashes.get(&v2), v2);
            let hv3 = recover_id(room_hashes.get(&v3), v3);
            
            // Add to the graph all the connections inside the triangle.
            self.graph.push(Edge::new(hv1, hv2, point_distance(v1.0, v1.1, v2.0, v2.1)));
            self.graph.push(Edge::new(hv1, hv3, point_distance(v1.0, v1.1, v3.0, v3.1)));
            self.graph.push(Edge::new(hv2, hv3, point_distance(v2.0, v2.1, v3.0, v3.1)));
        }

        self.graph.sort();
        self.connections = calculate_mst(&self.graph, self.selected_rooms.len());
    }
}

fn aprox_coordinate(n: f32, m: f32) -> i32 {
    ((n / m).round() as i32) * (m as i32)
}
