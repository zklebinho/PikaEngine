#include "SceneManager.h"

#include <iostream>

namespace kylie::scene {

std::shared_ptr<Scene> SceneManager::createScene(const std::string& name) {
    auto scene = std::make_shared<Scene>(name);
    scenes_[name] = scene;
    activeScene_ = scene;
    return scene;
}

bool SceneManager::loadScene(const std::string& name, const std::filesystem::path& path) {
    auto scene = std::make_shared<Scene>(name);
    if (!scene->loadFromFile(path)) {
        return false;
    }
    scenes_[name] = scene;
    activeScene_ = scene;
    std::cout << "[SceneManager] Active scene: " << name << "\n";
    return true;
}

bool SceneManager::saveScene(const std::string& name, const std::filesystem::path& path) {
    auto it = scenes_.find(name);
    if (it == scenes_.end()) return false;
    return it->second->saveToFile(path);
}

bool SceneManager::switchTo(const std::string& name) {
    auto it = scenes_.find(name);
    if (it == scenes_.end()) return false;
    activeScene_ = it->second;
    return true;
}

std::vector<std::string> SceneManager::sceneNames() const {
    std::vector<std::string> names;
    names.reserve(scenes_.size());
    for (const auto& kv : scenes_) names.push_back(kv.first);
    return names;
}

}  // namespace kylie::scene
