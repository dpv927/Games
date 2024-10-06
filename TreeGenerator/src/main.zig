const std = @import("std");
const port = TreeConnection.Port;

const TreeConnection = struct {
    const Port = enum(u2) {
        north,
        south,
        east,
        west,
    };

    dest_node: *TreeNode,
    dest_port: Port,
};

const TreeNode = struct {
    var rng: std.Random.DefaultPrng = undefined;
    var allocator: std.mem.Allocator = undefined;

    links: [4]?*TreeConnection,
    x: i32,
    y: i32,

    pub fn new_root() !*TreeNode {
        const root = try allocator.create(TreeNode);
        root.* = TreeNode{
            .links = [_]?TreeConnection{null} ** 4,
            .x = 0,
            .y = 0,
        };
        return root;
    }

    fn new_node(parent: *TreeNode, parent_port: TreeConnection.Port, node_port: TreeConnection.Port) !*TreeNode {
        const node = try allocator.create(TreeNode);
        node.* = TreeNode{
            .links = ([_]?TreeConnection{null} ** 4),
            .x = 0,
            .y = 0,
        };

        node.links[@intFromEnum(node_port)] = TreeConnection{
            .dest_node = parent,
            .dest_port = parent_port,
        };
        return node;
    }

    pub fn generate_subtree(self: *TreeNode, max_depth: u32) !void {
        try self.pgenerate_subtree(0, max_depth);
    }

    fn pgenerate_subtree(self: *TreeNode, depth: u32, max_depth: u32) !void {
        for (0..(rng.random().int(u8) % 5)) |_| {
            // Generate a random unused port at the
            // current node.
            var rand_port = rng.random().int(u8) % 4;
            while (self.links[rand_port] != null) {
                std.debug.print("pepe\n", .{});
                rand_port = rng.random().int(u8) % 4;
            }

            // Obtain the connection endpoints as enums
            const parent_port: port = @enumFromInt(rand_port);
            const child_port = switch (parent_port) {
                port.north => port.south,
                port.south => port.north,
                port.east => port.west,
                port.west => port.east,
            };

            // Try to create a child node (the allocation can fail)
            const child_node = try new_node(self, parent_port, child_port);

            // Create the link (Parent) -> (Child).
            // Also (Child) -> (Parent) at new_node()
            self.links[rand_port] = TreeConnection{
                .dest_node = child_node,
                .dest_port = child_port,
            };

            if ((depth + 1) < max_depth) {
                // Keep generating subtrees unless this node is a
                // leaf node parent.
                try child_node.pgenerate_subtree(depth + 1, max_depth);
            }
        }
    }

    pub fn destroy_subtree(self: *TreeNode) void {
        defer allocator.destroy(self);

        for (self.links) |link| {
            if (link != null) {
                link.?.dest_node.destroy_subtree();
            }
        }
    }
};

pub fn main() !void {
    TreeNode.rng = std.Random.DefaultPrng.init(undefined);
    TreeNode.allocator = std.heap.c_allocator;

    const node = try TreeNode.new_root();
    try node.generate_subtree(2);
    node.destroy_subtree();
}
