#include "SandboxScene.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace kylie::sandbox {

bool SandboxScene::loadFromFile(const std::filesystem::path& path) {
    entities_.clear();
    name_ = "Untitled Scene";

    if (!std::filesystem::exists(path)) {
        std::cerr << "[Sandbox] Scene file not found: " << path << "\n";
        return false;
    }

    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        // Trim leading spaces
        auto first = line.find_first_not_of(" \t");
        if (first == std::string::npos) continue;
        std::string trimmed = line.substr(first);

        if (trimmed.rfind("scene:", 0) == 0) {
            auto pos = trimmed.find(':');
            if (pos != std::string::npos && pos + 1 < trimmed.size()) {
                name_ = trimmed.substr(pos + 1);
                // strip leading space
                if (!name_.empty() && name_[0] == ' ') name_.erase(0, 1);
            }
        } else if (trimmed.rfind("-", 0) == 0) {
            // entity line like: - Player
            auto entity = trimmed.substr(1);
            if (!entity.empty() && entity[0] == ' ') entity.erase(0, 1);
            if (!entity.empty()) {
                entities_.push_back(entity);
            }
        }
    }

    std::cout << "[Sandbox] Loaded scene: " << name_ << " with " << entities_.size() << " entities\n";
    return true;
}

void SandboxScene::update(float deltaSeconds) {
    (void)deltaSeconds;
    // Placeholder for future simulation logic
}

}  // namespace kylie::sandbox
