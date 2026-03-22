#include "EditorApp.h"
#include "core/EngineApp.h"
#include "sandbox/SandboxScene.h"

#include "imgui.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace {
int runSandboxInline() {
    pika::core::EngineConfig config;
    config.title = "Pika Engine Sandbox";
    config.enableDocking = false;
    config.enableViewports = false;

    pika::core::EngineApp engine;
    if (!engine.init(config)) {
        return 1;
    }

    pika::sandbox::SandboxScene scene;
    const std::filesystem::path scenePath{"assets/scenes/test.scene"};
    scene.loadFromFile(scenePath);

    auto onUpdate = [&](float dt) {
        scene.update(dt);
    };

    auto onGui = [&](float dt) {
        (void)dt;
        ImGui::Begin("Sandbox");
        ImGui::Text("Scene: %s", scene.name().c_str());
        ImGui::Separator();
        for (const auto& e : scene.entities()) {
            ImGui::BulletText("%s", e.c_str());
        }
        ImGui::End();
    };

    engine.run(onUpdate, onGui);
    engine.shutdown();
    return 0;
}
}  // namespace

int main(int argc, char** argv) {
    bool sandbox = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--sandbox" || arg == "-s") sandbox = true;
    }

    if (sandbox) {
        std::cout << "[Launcher] Starting sandbox mode\n";
        return runSandboxInline();
    }

    std::cout << "[Launcher] Starting editor mode\n";
    return pika::editor::RunEditor();
}
