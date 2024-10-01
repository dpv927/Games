const std = @import("std");

const TreeConnection = struct {
    const port = enum(u2) {
        north,
        south,
        east,
        west,
    };

    dest_node: *TreeNode,
    dest_port: port,
};

const TreeNode = struct {
    links: [4]?TreeConnection,
    x: i32,
    y: i32,

    pub fn new_root(allocator: *std.mem.Allocator) !*TreeNode {
        const root = try allocator.create(TreeNode);
        root.* = TreeNode{
            .links = [_]?TreeConnection{null} ** 4,
            .x = 0,
            .y = 0,
        };
        return root;
    }

    fn new_node(alloc: *std.mem.Allocator, parent: *TreeNode, src_port: u2, dst_port: u2) !*TreeNode {
        _ = src_port;
        _ = dst_port;
        _ = parent;

        const root = try alloc.create(TreeNode);
        root.* = TreeNode{
            .links = ([_]?TreeConnection{null} ** 4),
            .x = 0,
            .y = 0,
        };
        return root;
    }

    fn is_leaf(self: *TreeNode) bool {
        return (self.links[0] == null) and
            (self.links[1] == null) and
            (self.links[2] == null) and
            (self.links[3] == null);
    }
};

pub fn main() !void {
    var allocator = std.heap.c_allocator;
    const root = try TreeNode.new_root(&allocator);
    defer allocator.destroy(root);
}
