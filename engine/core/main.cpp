#include "Engine.h"

#include "pika/Module.hpp"
#include "renderer/Renderer.h"

#include <iostream>
#include <memory>

// Minimal inline module to demonstrate modular architecture.
class LoggerModule : public pika::modules::IModule {
public:
    std::string name() const override { return "LoggerModule"; }
    void onUpdate(float dt) override { std::cout << "[LoggerModule] dt=" << dt << "\n"; }
};

int main() {
    std::cout << "Pika Engine started\n";

    // Engine loop
    pika::core::Engine engine;
    engine.addModule(std::make_shared<LoggerModule>());
    engine.setUpdateCallback([](float dt) { std::cout << "[App] Update dt=" << dt << "\n"; });
    engine.setRenderCallback([] { std::cout << "[App] Render\n"; });

    // Window + renderer (clears screen a few frames then exits)
    pika::renderer::Renderer renderer(800, 600, "Pika Engine");
    if (renderer.init()) {
        renderer.loopFrames(5);
    } else {
        std::cerr << "Renderer init failed; skipping render loop\n";
    }

    engine.run(3);
    return 0;
}
