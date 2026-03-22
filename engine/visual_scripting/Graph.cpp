#include "Graph.h"

#include <sstream>

namespace kylie::visual {

NodeBlock::NodeBlock(std::uint32_t id, std::string title, NodeCategory category)
    : id_(id), title_(std::move(title)), category_(category) {}

void NodeBlock::addPin(const std::string& name, PinKind kind) {
    pins_.push_back(Pin{nextPinId_++, name, kind});
}

NodeBlock& VisualScriptGraph::addNode(const std::string& title, NodeCategory category) {
    nodes_.emplace_back(nextNodeId_++, title, category);
    return nodes_.back();
}

bool VisualScriptGraph::connect(std::uint32_t fromNode, std::uint32_t fromPin, std::uint32_t toNode, std::uint32_t toPin) {
    connections_.push_back(Connection{fromNode, fromPin, toNode, toPin});
    return true;
}

std::string VisualScriptGraph::debugSummary() const {
    std::ostringstream out;
    out << "Nodes: " << nodes_.size() << ", Connections: " << connections_.size();
    return out.str();
}

}  // namespace kylie::visual
