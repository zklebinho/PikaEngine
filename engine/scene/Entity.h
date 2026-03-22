#pragma once

#include <cstdint>
#include <string>

namespace kylie::scene {

class Entity {
public:
    Entity(std::uint32_t id, std::string name);

    std::uint32_t id() const { return id_; }
    const std::string& name() const { return name_; }
    void setName(std::string name) { name_ = std::move(name); }

private:
    std::uint32_t id_;
    std::string name_;
};

}  // namespace kylie::scene
