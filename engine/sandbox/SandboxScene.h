#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace kylie::sandbox {

class SandboxScene {
public:
    bool loadFromFile(const std::filesystem::path& path);
    void update(float deltaSeconds);

    const std::vector<std::string>& entities() const { return entities_; }
    const std::string& name() const { return name_; }

private:
    std::string name_{"Untitled Scene"};
    std::vector<std::string> entities_;
};

}  // namespace kylie::sandbox
