#include "kylie/Engine.hpp"

#include <iostream>
#include <thread>

namespace kylie {

Engine::Engine() = default;
Engine::~Engine() {
    for (auto& name : registry_.listModules()) {
        auto mod = registry_.getModule(name);
        if (mod) {
            mod->onShutdown();
        }
    }
}

void Engine::setTickCallback(TickCallback cb) { tickCallback_ = std::move(cb); }

modules::ModuleRegistry& Engine::modules() { return registry_; }

void Engine::runFrames(int frameCount, float fixedDeltaSeconds) {
    using namespace std::chrono_literals;
    for (int i = 0; i < frameCount; ++i) {
        if (tickCallback_) {
            tickCallback_(fixedDeltaSeconds);
        }
        registry_.updateAll(fixedDeltaSeconds);
        std::this_thread::sleep_for(std::chrono::duration<float>(fixedDeltaSeconds));
    }
}

}  // namespace kylie
