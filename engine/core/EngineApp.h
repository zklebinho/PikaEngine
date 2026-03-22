#pragma once

#include "kylie/Module.hpp"
#include "ecs/Registry.h"
#include "renderer/Renderer.h"
#include "scripting/ScriptSystem.h"
#include "scripting/PythonBridge.h"
#include "plugins/PluginManager.h"
#include "ai/AIStub.h"
#include "scene/SceneManager.h"
#include "dimensions/Dimensions.h"

#include <filesystem>
#include <functional>
#include <memory>
#include <string>

struct ImGuiContext;

namespace kylie::core {

struct EngineConfig {
    int width{1280};
    int height{720};
    std::string title{"Kylie Engine Editor"};
    bool enableDocking{true};
    bool enableViewports{true};
    bool enablePlugins{false};
    std::vector<std::filesystem::path> pluginPaths;
};

class EngineApp {
public:
    EngineApp();
    ~EngineApp();

    bool init(const EngineConfig& config);
    void run(const std::function<void(float)>& onUpdate,
             const std::function<void(float)>& onGui);
    void shutdown();

    modules::ModuleRegistry& modules() { return registry_; }
    ecs::Registry& ecs() { return ecs_; }
    scripting::ScriptSystem& scripting() { return scriptSystem_; }
    plugins::PluginManager& pluginManager() { return pluginManager_; }
    scene::SceneManager& scenes() { return sceneManager_; }

    void setClearColor(float r, float g, float b) { if (renderer_) renderer_->setClearColor(r, g, b, 1.0f); }

private:
    EngineConfig config_{};
    std::unique_ptr<renderer::Renderer> renderer_;
    scripting::ScriptSystem scriptSystem_;
    scripting::PythonBridge pythonBridge_;
    plugins::PluginManager pluginManager_;
    modules::ModuleRegistry registry_;
    ecs::Registry ecs_;
    ai::AIStub aiStub_;
    scene::SceneManager sceneManager_;
    dimensions::Dimension3D defaultDimension_;

    bool imguiInitialized_{false};

    void beginFrame();
    void endFrame();
    void loadPlugins();
};

}  // namespace kylie::core
