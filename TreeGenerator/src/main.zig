const std = @import("std");
const tree = @import("tree.zig");

pub fn main() !void {
    tree.Node.allocator = std.heap.c_allocator;
    tree.Node.rng = std.Random.DefaultPrng.init(undefined);

    var node = tree.Node.newNode();
    defer node.destroySubtree();
    // defer tree.Node.allocator.destroy(node);

    node.generateSubtree(10) catch {
        node.destroySubtree();
        return;
    };

    node.printSubtree();
}
