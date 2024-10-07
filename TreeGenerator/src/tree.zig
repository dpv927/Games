const std = @import("std");

const Port = enum(u2) {
    North,
    East,
    South,
    West,

    pub fn getSymmetric(self: Port) Port {
        return switch (self) {
            Port.North => Port.South,
            Port.East => Port.West,
            Port.South => Port.North,
            Port.West => Port.East,
        };
    }
};

const NodeConnection = struct {
    dstNode: ?*Node,
    dstPort: Port,
    isParent: bool,

    pub fn new(destNode: ?*Node, destPort: Port, isParent: bool) NodeConnection {
        return NodeConnection{
            .dstNode = destNode,
            .dstPort = destPort,
            .isParent = isParent,
        };
    }
};

pub const Node = struct {
    pub var allocator: std.mem.Allocator = undefined;
    pub var rng: std.Random.DefaultPrng = undefined;
    pub var count: u32 = 0;

    connections: [4]NodeConnection,
    id: u32,
    x: u32,
    y: u32,

    pub fn newNode() Node {
        count += 1;

        return Node{
            .connections = [_]NodeConnection{
                NodeConnection.new(null, undefined, false),
            } ** 4,
            .x = 0,
            .y = 0,
            .id = count,
        };
    }

    fn addParentConnection(self: *Node, srcPort: Port, dstNode: *Node, dstPort: Port) void {
        var connection = &self.connections[@intFromEnum(srcPort)];
        connection.dstNode = dstNode;
        connection.dstPort = dstPort;
        connection.isParent = true;
    }

    fn addConnection(self: *Node, srcPort: Port, dstNode: *Node, dstPort: Port) void {
        var connection = &self.connections[@intFromEnum(srcPort)];
        connection.dstNode = dstNode;
        connection.dstPort = dstPort;
        connection.isParent = false;
    }

    pub fn generateSubtree(self: *Node, maxDepth: u32) !void {
        try self.pgenerateSubtree(0, maxDepth);
        // for (self.connections) |connection| {
        //     try connection.dstNode.?.pgenerateSubtree(1, maxDepth);
        //}
    }

    fn pgenerateSubtree(self: *Node, depth: u32, maxDepth: u32) !void {
        // Get the unused ports (ports without a connection) so we can
        // generate a random number of connections over those ports.
        var unusedPorts = [_]Port{undefined} ** 4;
        var port: u8 = 0;

        for (self.connections) |connection| {
            if (connection.dstNode == null) {
                unusedPorts[port] = @enumFromInt(port);
                port += 1;
            }
        }

        // Number of connections to generate for this node. This number
        // goes in the range [0-3]. Why not 4? One connection is already
        // in use by the father node.
        //
        // Only if the number of connections to create is different to 3,
        // shuffle the unusedPorts list (its useless otherwise). This is
        // because when we are creating connections we will pick the first
        // 'randConnections' Ports from the array to create connections
        // in those selected Ports.
        const randConnections = rng.random().int(u8) % 4;
        if (randConnections == 0) {
            return;
        } else if (randConnections != 3) {
            for (0..3) |index| {
                const rand = rng.random().int(u8) % 4;
                const tmp = unusedPorts[rand];
                unusedPorts[rand] = unusedPorts[index];
                unusedPorts[index] = tmp;
            }
        }

        for (0..randConnections) |index| {
            const nodePort = unusedPorts[index];
            const childPort = nodePort.getSymmetric();

            var child = try allocator.create(Node);
            child.* = Node.newNode();

            child.addParentConnection(childPort, self, nodePort);
            self.addConnection(nodePort, child, childPort);

            if ((depth + 1) < maxDepth) {
                try child.pgenerateSubtree(depth + 1, maxDepth);
            }
        }
    }

    pub fn destroySubtree(self: *Node) void {
        for (self.connections) |connection| {
            if (connection.dstNode != null and !connection.isParent) {
                connection.dstNode.?.destroySubtree();
                allocator.destroy(connection.dstNode.?);
            }
        }
    }

    pub fn printSubtree(self: *Node) void {
        self.pprintSubtree(0);
    }

    pub fn pprintSubtree(self: *Node, depth: u32) void {
        for (self.connections, 0..) |connection, door| {

            // Print all non-parent connections, The format is
            // [srcAddr:srcPort] -> [dstAddr:dstPort].
            if (connection.dstNode != null) {
                for (0..depth) |_| {
                    std.debug.print("\t", .{});
                }

                std.debug.print("[{x:0>4}:{}] -> [{x:0>4}:{}]\n", .{
                    self.id,
                    door,
                    connection.dstNode.?.id,
                    @intFromEnum(connection.dstPort),
                });

                if (!connection.isParent)
                    connection.dstNode.?.pprintSubtree(depth + 1);
            }
        }
    }
};
