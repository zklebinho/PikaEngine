// Lightweight Python bridge (stubbed when KYLIE_ENABLE_PYTHON is OFF)
#pragma once

#include "ecs/Registry.h"

#include <string>

namespace kylie::scripting {

class PythonBridge {
public:
    bool initialize();
    void shutdown();
    bool callEntityUpdate(const std::string& module,
                          const std::string& function,
                          ecs::Entity entity,
                          ecs::Registry& registry,
                          float deltaSeconds);
};

}  // namespace kylie::scripting
