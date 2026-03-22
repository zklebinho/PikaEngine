#include "kylie/Engine.hpp"
#include "kylie/Module.hpp"
#include "kylie/NodeGraph.hpp"
#include "kylie/Scripting.hpp"

#include <iostream>
#include <memory>

int main() {
    std::cout << "KylieEngine minimal example\n";
    kylie::Engine engine;

#ifdef WITH_SAMPLE_PLUGIN
    // Forward declaration from sample_plugin to avoid an extra header.
    namespace kylie::plugins {
    std::shared_ptr<kylie::modules::IModule> createSamplePlugin();
    }

    // Register sample plugin if available.
    if (auto plugin = kylie::plugins::createSamplePlugin()) {
        engine.modules().registerModule(plugin);
    }
#else
    std::cout << "Sample plugin not built; skipping plugin registration.\n";
#endif

    // Set a tick callback to demonstrate engine loop.
    engine.setTickCallback([](float dt) {
        std::cout << "[Engine] Tick callback dt=" << dt << "\n";
    });

    // Visual node graph demo.
    kylie::graph::NodeGraph graph;
    auto nodeA = graph.addNode("Input");
    auto nodeB = graph.addNode("Output");
    graph.addOutputPin(nodeA, "value");
    graph.addInputPin(nodeB, "value");
    graph.connect(nodeA, 1, nodeB, 2);
    std::cout << "[Graph] " << graph.toJsonLike() << "\n";

    // Scripting demo (stubbed).
    kylie::scripting::ScriptingEngine scripting;
    scripting.runScript("print('hello from lua')");

    // Run a few frames.
    engine.runFrames(3);

    std::cout << "Example finished.\n";
    return 0;
}
