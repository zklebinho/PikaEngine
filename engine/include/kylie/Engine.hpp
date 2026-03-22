// KylieEngine - Core engine loop
#pragma once

#include "Module.hpp"

#include <chrono>
#include <functional>
#include <string>

namespace kylie {

class Engine {
public:
    using TickCallback = std::function<void(float)>;  // dt in seconds

    Engine();
    ~Engine();

    // Inject callbacks and modules before running
    void setTickCallback(TickCallback cb);
    modules::ModuleRegistry& modules();

    // Run for a number of frames (stub main loop)
    void runFrames(int frameCount, float fixedDeltaSeconds = 1.0f / 60.0f);

private:
    modules::ModuleRegistry registry_;
    TickCallback tickCallback_;
};

}  // namespace kylie
