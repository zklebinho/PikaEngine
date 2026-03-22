#include "Scene.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

namespace kylie::scene {

Scene::Scene(std::string name) : name_(std::move(name)) {}

Entity& Scene::createEntity(const std::string& name) {
    entities_.emplace_back(nextId_++, name);
    return entities_.back();
}

bool Scene::removeEntity(std::uint32_t id) {
    auto it = std::find_if(entities_.begin(), entities_.end(), [&](const Entity& e) { return e.id() == id; });
    if (it == entities_.end()) return false;
    entities_.erase(it);
    return true;
}

bool Scene::loadFromFile(const std::filesystem::path& path) {
    entities_.clear();
    nextId_ = 1;
    name_ = "Untitled Scene";

    if (!std::filesystem::exists(path)) {
        std::cerr << "[Scene] File not found: " << path << "\n";
        return false;
    }

    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        auto first = line.find_first_not_of(" \t");
        if (first == std::string::npos) continue;
        std::string trimmed = line.substr(first);
        if (trimmed.rfind("scene:", 0) == 0) {
            auto pos = trimmed.find(':');
            if (pos != std::string::npos && pos + 1 < trimmed.size()) {
                name_ = trimmed.substr(pos + 1);
                if (!name_.empty() && name_[0] == ' ') name_.erase(0, 1);
            }
        } else if (trimmed.rfind("-", 0) == 0) {
            auto entity = trimmed.substr(1);
            if (!entity.empty() && entity[0] == ' ') entity.erase(0, 1);
            if (!entity.empty()) {
                createEntity(entity);
            }
        }
    }

    std::cout << "[Scene] Loaded scene: " << name_ << " with " << entities_.size() << " entities\n";
    return true;
}

bool Scene::saveToFile(const std::filesystem::path& path) const {
    std::ofstream out(path);
    if (!out.is_open()) {
        std::cerr << "[Scene] Failed to save to: " << path << "\n";
        return false;
    }
    out << "scene: " << name_ << "\n";
    out << "entities:\n";
    for (const auto& e : entities_) {
        out << "  - " << e.name() << "\n";
    }
    return true;
}

}  // namespace kylie::scene
