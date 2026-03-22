#pragma once

#include "Scene.h"

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace kylie::scene {

class SceneManager {
public:
    std::shared_ptr<Scene> createScene(const std::string& name);
    bool loadScene(const std::string& name, const std::filesystem::path& path);
    bool saveScene(const std::string& name, const std::filesystem::path& path);
    bool switchTo(const std::string& name);

    std::shared_ptr<Scene> activeScene() const { return activeScene_; }
    std::vector<std::string> sceneNames() const;

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_;
    std::shared_ptr<Scene> activeScene_;
};

}  // namespace kylie::scene
