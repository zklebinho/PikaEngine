// Lightweight Python bridge (stubbed when PIKA_ENABLE_PYTHON is OFF)
#pragma once

#include "ecs/Registry.h"

#include <string>

namespace pika::scripting {

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

}  // namespace pika::scripting
