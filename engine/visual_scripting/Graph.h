#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace kylie::visual {

enum class NodeCategory { Event, Logic, Math, GameObject, Custom };

enum class PinKind { Input, Output };

struct Pin {
    std::uint32_t id{};
    std::string name;
    PinKind kind{PinKind::Input};
};

class NodeBlock {
public:
    NodeBlock(std::uint32_t id, std::string title, NodeCategory category);

    std::uint32_t id() const { return id_; }
    const std::string& title() const { return title_; }
    NodeCategory category() const { return category_; }

    void addPin(const std::string& name, PinKind kind);
    const std::vector<Pin>& pins() const { return pins_; }

    void setCode(std::string code) { code_ = std::move(code); }
    const std::string& code() const { return code_; }

private:
    std::uint32_t id_;
    std::string title_;
    NodeCategory category_;
    std::vector<Pin> pins_;
    std::string code_;
    std::uint32_t nextPinId_{1};
};

struct Connection {
    std::uint32_t fromNode;
    std::uint32_t fromPin;
    std::uint32_t toNode;
    std::uint32_t toPin;
};

class VisualScriptGraph {
public:
    NodeBlock& addNode(const std::string& title, NodeCategory category);
    bool connect(std::uint32_t fromNode, std::uint32_t fromPin, std::uint32_t toNode, std::uint32_t toPin);

    const std::vector<NodeBlock>& nodes() const { return nodes_; }
    const std::vector<Connection>& connections() const { return connections_; }

    std::string debugSummary() const;

private:
    std::vector<NodeBlock> nodes_;
    std::vector<Connection> connections_;
    std::uint32_t nextNodeId_{1};
};

}  // namespace kylie::visual
