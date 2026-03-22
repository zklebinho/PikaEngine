// Core application runner for KylieEngine
#pragma once

#include "kylie/Module.hpp"

#include <functional>
#include <memory>
#include <queue>

namespace kylie::core {

struct Event {
    std::string type;
};

class Engine {
public:
    using UpdateCallback = std::function<void(float)>;
    using RenderCallback = std::function<void()>;

    Engine();

    void addModule(const std::shared_ptr<modules::IModule>& module);
    void setUpdateCallback(UpdateCallback cb);
    void setRenderCallback(RenderCallback cb);

    void run(int maxFrames = 120, float fixedDeltaSeconds = 1.0f / 60.0f);
    void stop();

private:
    bool running_{false};
    modules::ModuleRegistry registry_;
    UpdateCallback updateCb_;
    RenderCallback renderCb_;
    std::queue<Event> eventQueue_;

    void pollEvents();       // placeholder for platform event pump
    void dispatchEvents();   // placeholder to route queued events
};

}  // namespace kylie::core
