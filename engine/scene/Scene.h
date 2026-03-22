#pragma once

#include "Entity.h"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace kylie::scene {

class Scene {
public:
    Scene() = default;
    explicit Scene(std::string name);

    Entity& createEntity(const std::string& name);
    bool removeEntity(std::uint32_t id);

    const std::vector<Entity>& entities() const { return entities_; }
    const std::string& name() const { return name_; }
    void setName(std::string name) { name_ = std::move(name); }

    // Simple text-based load/save for prototype
    bool loadFromFile(const std::filesystem::path& path);
    bool saveToFile(const std::filesystem::path& path) const;

private:
    std::string name_{"Untitled Scene"};
    std::vector<Entity> entities_;
    std::uint32_t nextId_{1};
};

}  // namespace kylie::scene
