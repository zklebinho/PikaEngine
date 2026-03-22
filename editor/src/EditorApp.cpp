#include "EditorApp.h"

#include "core/EngineApp.h"
#include "ui/EditorUI.h"
#include "sandbox/SandboxScene.h"

#include <filesystem>
#include <iostream>

namespace pika::editor {

int RunEditor() {
    pika::core::EngineConfig config;
    config.title = "Pika Engine Editor";
    config.enableDocking = true;
    config.enableViewports = true;

    pika::core::EngineApp engine;
    if (!engine.init(config)) {
        return 1;
    }

    // Load sandbox scene for preview data
    pika::sandbox::SandboxScene scene;
    const std::filesystem::path scenePath{"assets/scenes/test.scene"};
    scene.loadFromFile(scenePath);

    EditorUI ui{"assets"};
    ui.pushLog("Pika Engine started successfully");
    ui.pushLog("Loaded scene: " + scene.name());

    auto onUpdate = [&](float dt) {
        (void)dt;
        scene.update(dt);
    };

    auto onGui = [&](float dt) {
        ui.draw(scene.name(), scene.entities(), dt);
    };

    engine.run(onUpdate, onGui);
    engine.shutdown();
    return 0;
}

}  // namespace pika::editor
