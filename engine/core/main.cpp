#include "Engine.h"

#include "pika/Module.hpp"

#include <iostream>
#include <memory>

// Minimal inline module to demonstrate modular architecture.
class LoggerModule : public pika::modules::IModule {
public:
    std::string name() const override { return "LoggerModule"; }
    void onUpdate(float dt) override { std::cout << "[LoggerModule] dt=" << dt << "\n"; }
};

int main() {
    std::cout << "PikaEngine core demo\n";

    pika::core::Engine engine;
    engine.addModule(std::make_shared<LoggerModule>());

    engine.setUpdateCallback([](float dt) { std::cout << "[App] Update dt=" << dt << "\n"; });
    engine.setRenderCallback([] { std::cout << "[App] Render\n"; });

    engine.run(3);
    return 0;
}
