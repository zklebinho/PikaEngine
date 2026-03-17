// PikaEngine - Minimal node graph model for visual blocks
#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace pika::graph {

using NodeId = int;
using PinId = int;

struct Pin {
    PinId id{};
    std::string name;
    bool isInput{true};
};

struct Node {
    NodeId id{};
    std::string name;
    std::vector<Pin> inputs;
    std::vector<Pin> outputs;
};

struct Connection {
    NodeId fromNode{};
    PinId fromPin{};
    NodeId toNode{};
    PinId toPin{};
};

class NodeGraph {
public:
    NodeId addNode(const std::string& name);
    bool addInputPin(NodeId node, const std::string& name);
    bool addOutputPin(NodeId node, const std::string& name);
    bool connect(NodeId fromNode, PinId fromPin, NodeId toNode, PinId toPin);

    std::vector<Node> nodes() const;
    std::vector<Connection> connections() const;

    // Debug serialization (JSON-like string, not strict JSON yet)
    std::string toJsonLike() const;

private:
    NodeId nextNodeId_{1};
    PinId nextPinId_{1};
    std::unordered_map<NodeId, Node> nodes_;
    std::vector<Connection> edges_;
};

}  // namespace pika::graph
