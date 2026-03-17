// Script system allowing C++ and Python scripts to control entities
#pragma once

#include "ecs/Registry.h"

#include <functional>
#include <string>

namespace pika::scripting {

class PythonBridge;

enum class ScriptLanguage { Cpp, Python };

struct ScriptComponent {
    ScriptLanguage language{ScriptLanguage::Cpp};
    std::function<void(ecs::Entity, ecs::Registry&, float)> cppUpdate;
    std::string pythonModule;
    std::string pythonFunction;
};

class ScriptSystem {
public:
    void setPythonBridge(PythonBridge* bridge) { pythonBridge_ = bridge; }

    void attachCppScript(ecs::Registry& registry,
                         ecs::Entity entity,
                         std::function<void(ecs::Entity, ecs::Registry&, float)> onUpdate);

    void attachPythonScript(ecs::Registry& registry,
                            ecs::Entity entity,
                            std::string module,
                            std::string function);

    void update(ecs::Registry& registry, float deltaSeconds);

private:
    PythonBridge* pythonBridge_{nullptr};  // non-owning
};

}  // namespace pika::scripting
