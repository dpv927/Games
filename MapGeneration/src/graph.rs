/// 
/// In one of the steps of the PDGA (Procedural Dungeon Generation Algorithm), 
/// it is necessary to calculate a network of connections between a set of 
/// dungeons in order to generate paths between them. For this purpose, there 
/// is this module which generates and manages connection graphs between 
/// dungeons.
/// 
/// The idea is to select the main rooms (see Room.main in room.rs) and 
/// generate a graph between them. To make the process more efficient, the 
/// room IDs (see Room.id) are used instead of references to the rooms. 
/// Therefore, you'll see that in the structures of this module, usize is used 
/// (the same type as Room.id). 
///
/// How are the rooms efficiently retrieved later based on their IDs? 
/// The answer is the `engine::select_rooms` function, which returns a vector of
/// references to rooms (only those with the property main = true). The room 
/// with ID = 0 will be at position [0] of the vector, the one with ID = 1 at
/// position [1], and so on. 
///
/// @see room.rs (Room.id, Room.main)
/// @see engine.rs (select_rooms)
///


/// 
/// The UnionFind struct is part of the Kruskal Algorithm. It is used as a path
/// compression technique between nodes in a graph. It is optimized for graphs 
/// `(u->v) = w`, where u and v are integers (0..n). 
/// 
struct UnionFind {
    parent: Vec<usize>,
    rank: Vec<usize>
}

impl UnionFind {
    
    fn new(n: usize) -> UnionFind {
        UnionFind {
            parent: (0..n).collect(),
            rank: vec![0; n as usize]
        }
    }

    fn find(&mut self, u: usize) -> usize {
        let mut u_find = u;

        while u_find != self.parent[u_find] {
            self.parent[u_find] = self.parent[self.parent[u_find] as usize];
            u_find = self.parent[u_find];
        }
        u_find
    }

    fn unite(&mut self, u: usize, v: usize) {
        let root_u = self.find(u);
        let root_v = self.find(v);

        if root_u != root_v {
            if self.rank[root_u] > self.rank[root_v] {
                self.parent[root_v] = root_u;
            } 
            else if self.rank[root_u] < self.rank[root_v] {
                self.parent[root_u] = root_v;
            } else {
                self.parent[root_v] = root_u;
                self.rank[root_u] += 1;
            }
        }
    }
}

///
/// The Edge struct represents a edge `(u,w) = w` from a graph, where `u` and 
/// `v` are rooms IDs from two rooms. The propierty `w` is the edge's weight,
/// in this case is the euclidean distance between the center of each room.
///
#[derive(Eq, PartialEq, Debug)]
pub struct Edge {
    pub u: usize,
    pub v: usize,
    w: usize,
}

impl Ord for Edge {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.w.cmp(&other.w)
    }
}

impl PartialOrd for Edge {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.w.cmp(&other.w))
    }
}

impl Edge {
        
    pub fn new(u: usize, v: usize, w: usize) -> Edge {
        Edge { u, v, w }
    }
}

///
/// The Connection struct is made simply for memory saving reasons. To save 
/// a little bit of memory, instead of returning a Edges `(u->v) = w` from the 
/// final funcion, we return Connections (which does not have the `w` field). 
///
/// Once the process of creating a graph from a set of rooms if finished, we 
/// no longer care about the distance between rooms, so we delete the `w`
/// field from Edge and we now have the necessary information.
///
pub struct Connection {
    pub src: usize,
    pub dest: usize
}

///
/// Calculates the MST (Minimum Spanning Tree) over a graph. The graph is 
/// made up by `(u->v) = w` vertices and returns a connection vector, where 
/// each element is `(u->v)`.
/// 
/// The main idea of the MST (Minimum Spanning Tree) is to compute a network of
/// connections in a graph, where all vertices are reachable from each other 
/// (through any path) and the sum of all connections between all vertices is 
/// minimized.
/// 
pub fn calculate_mst(graph: &Vec<Edge>, num_vertices: usize) -> Vec<Connection> {
    let mut mst = vec![];
    let mut uf = UnionFind::new(num_vertices);

    for edge in graph {
        if uf.find(edge.u) != uf.find(edge.v) {
            uf.unite(edge.u, edge.v);
            mst.push(Connection {
                src: edge.u,
                dest: edge.v
            });

            if mst.len() == (num_vertices - 1) {
                break;
            }
        }
    }
    mst
}
