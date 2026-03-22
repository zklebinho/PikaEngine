#include "EditorApp.h"

#include "core/EngineApp.h"
#include "EditorUI.h"
#include "visual_scripting/Graph.h"

#include <filesystem>
#include <iostream>

namespace kylie::editor {

int RunEditor() {
    kylie::core::EngineConfig config;
    config.title = "Kylie Engine Editor";
    config.enableDocking = true;
    config.enableViewports = true;

    kylie::core::EngineApp engine;
    if (!engine.init(config)) {
        return 1;
    }

    EditorUI ui{"assets"};
    ui.pushLog("Kylie Engine started successfully");
    if (auto active = engine.scenes().activeScene()) {
        ui.pushLog("Loaded scene: " + active->name());
    }
    // Build a tiny visual scripting sample graph
    kylie::visual::VisualScriptGraph graph;
    auto& eventNode = graph.addNode("OnStart", kylie::visual::NodeCategory::Event);
    eventNode.addPin("Out", kylie::visual::PinKind::Output);
    auto& logicNode = graph.addNode("Print", kylie::visual::NodeCategory::Logic);
    logicNode.addPin("In", kylie::visual::PinKind::Input);
    logicNode.setCode("print('Hello from visual script')");
    graph.connect(eventNode.id(), 1, logicNode.id(), 1);
    ui.pushLog("[VisualScript] " + graph.debugSummary());

    auto onUpdate = [&](float dt) {
        (void)dt;
        // Scene-specific simulation would go here.
    };

    auto onGui = [&](float dt) {
        auto active = engine.scenes().activeScene();
        std::vector<std::string> ents;
        if (active) {
            ents.reserve(active->entities().size());
            for (const auto& e : active->entities()) {
                ents.push_back(e.name());
            }
        }
        const std::string sceneName = active ? active->name() : "No Scene";
        ui.draw(sceneName, ents, dt);
    };

    engine.run(onUpdate, onGui);
    engine.shutdown();
    return 0;
}

}  // namespace kylie::editor
