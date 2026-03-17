#include "pika/Engine.hpp"
#include "pika/Module.hpp"
#include "pika/NodeGraph.hpp"
#include "pika/Scripting.hpp"

#include <iostream>
#include <memory>

int main() {
    std::cout << "PikaEngine minimal example\n";
    pika::Engine engine;

#ifdef WITH_SAMPLE_PLUGIN
    // Forward declaration from sample_plugin to avoid an extra header.
    namespace pika::plugins {
    std::shared_ptr<pika::modules::IModule> createSamplePlugin();
    }

    // Register sample plugin if available.
    if (auto plugin = pika::plugins::createSamplePlugin()) {
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
    pika::graph::NodeGraph graph;
    auto nodeA = graph.addNode("Input");
    auto nodeB = graph.addNode("Output");
    graph.addOutputPin(nodeA, "value");
    graph.addInputPin(nodeB, "value");
    graph.connect(nodeA, 1, nodeB, 2);
    std::cout << "[Graph] " << graph.toJsonLike() << "\n";

    // Scripting demo (stubbed).
    pika::scripting::ScriptingEngine scripting;
    scripting.runScript("print('hello from lua')");

    // Run a few frames.
    engine.runFrames(3);

    std::cout << "Example finished.\n";
    return 0;
}
