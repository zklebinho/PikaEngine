#include "Engine.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace pika::core {

Engine::Engine() = default;

void Engine::addModule(const std::shared_ptr<modules::IModule>& module) {
    registry_.registerModule(module);
}

void Engine::setUpdateCallback(UpdateCallback cb) { updateCb_ = std::move(cb); }
void Engine::setRenderCallback(RenderCallback cb) { renderCb_ = std::move(cb); }

void Engine::run(int maxFrames, float fixedDeltaSeconds) {
    running_ = true;
    for (int frame = 0; running_ && frame < maxFrames; ++frame) {
        pollEvents();
        dispatchEvents();

        if (updateCb_) {
            updateCb_(fixedDeltaSeconds);
        }
        registry_.updateAll(fixedDeltaSeconds);

        if (renderCb_) {
            renderCb_();
        } else {
            std::cout << "[Core] Render placeholder frame " << frame << "\n";
        }

        std::this_thread::sleep_for(std::chrono::duration<float>(fixedDeltaSeconds));
    }
}

void Engine::stop() { running_ = false; }

void Engine::pollEvents() {
    // Placeholder: push a fake tick event each frame for now.
    eventQueue_.push(Event{.type = "tick"});
}

void Engine::dispatchEvents() {
    while (!eventQueue_.empty()) {
        auto evt = eventQueue_.front();
        eventQueue_.pop();
        std::cout << "[Core] Event: " << evt.type << "\n";
    }
}

}  // namespace pika::core
