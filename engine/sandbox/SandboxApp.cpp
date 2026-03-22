#include "core/EngineApp.h"

#include "imgui.h"

#include <filesystem>
#include <iostream>

int main() {
    kylie::core::EngineConfig config;
    config.title = "Kylie Engine Sandbox";
    config.enableDocking = false;
    config.enableViewports = false;

    kylie::core::EngineApp engine;
    if (!engine.init(config)) {
        return 1;
    }

    auto onUpdate = [&](float dt) {
        (void)dt;
    };

    auto onGui = [&](float dt) {
        (void)dt;
        ImGui::Begin("Sandbox");
        auto active = engine.scenes().activeScene();
        const auto sceneName = active ? active->name() : "No Scene";
        ImGui::Text("Scene: %s", sceneName.c_str());
        ImGui::Separator();
        if (active) {
            for (const auto& e : active->entities()) {
                ImGui::BulletText("%s", e.name().c_str());
            }
        }
        ImGui::End();
    };

    engine.run(onUpdate, onGui);
    engine.shutdown();
    return 0;
}
