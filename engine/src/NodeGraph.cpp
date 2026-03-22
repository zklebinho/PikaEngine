#include "kylie/NodeGraph.hpp"

#include <sstream>

namespace kylie::graph {

NodeId NodeGraph::addNode(const std::string& name) {
    Node node;
    node.id = nextNodeId_++;
    node.name = name;
    nodes_.emplace(node.id, node);
    return node.id;
}

bool NodeGraph::addInputPin(NodeId nodeId, const std::string& name) {
    auto it = nodes_.find(nodeId);
    if (it == nodes_.end()) return false;
    Pin pin{nextPinId_++, name, true};
    it->second.inputs.push_back(pin);
    return true;
}

bool NodeGraph::addOutputPin(NodeId nodeId, const std::string& name) {
    auto it = nodes_.find(nodeId);
    if (it == nodes_.end()) return false;
    Pin pin{nextPinId_++, name, false};
    it->second.outputs.push_back(pin);
    return true;
}

bool NodeGraph::connect(NodeId fromNode, PinId fromPin, NodeId toNode, PinId toPin) {
    if (nodes_.find(fromNode) == nodes_.end() || nodes_.find(toNode) == nodes_.end()) {
        return false;
    }
    edges_.push_back(Connection{fromNode, fromPin, toNode, toPin});
    return true;
}

std::vector<Node> NodeGraph::nodes() const {
    std::vector<Node> result;
    result.reserve(nodes_.size());
    for (const auto& [_, node] : nodes_) {
        result.push_back(node);
    }
    return result;
}

std::vector<Connection> NodeGraph::connections() const { return edges_; }

std::string NodeGraph::toJsonLike() const {
    std::ostringstream out;
    out << "{ \"nodes\": [";
    bool firstNode = true;
    for (const auto& [_, node] : nodes_) {
        if (!firstNode) out << ", ";
        firstNode = false;
        out << "{ \"id\": " << node.id << ", \"name\": \"" << node.name << "\" }";
    }
    out << "], \"connections\": [";
    bool firstConn = true;
    for (const auto& edge : edges_) {
        if (!firstConn) out << ", ";
        firstConn = false;
        out << "{ \"from\": [" << edge.fromNode << "," << edge.fromPin << "], "
            << "\"to\": [" << edge.toNode << "," << edge.toPin << "] }";
    }
    out << "] }";
    return out.str();
}

}  // namespace kylie::graph
