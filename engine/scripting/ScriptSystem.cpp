#include "ScriptSystem.h"

#include "PythonBridge.h"

#include <iostream>

namespace pika::scripting {

void ScriptSystem::attachCppScript(ecs::Registry& registry,
                                   ecs::Entity entity,
                                   std::function<void(ecs::Entity, ecs::Registry&, float)> onUpdate) {
    registry.emplace<ScriptComponent>(entity, ScriptComponent{
                                                     .language = ScriptLanguage::Cpp,
                                                     .cppUpdate = std::move(onUpdate),
                                                 });
}

void ScriptSystem::attachPythonScript(ecs::Registry& registry,
                                      ecs::Entity entity,
                                      std::string module,
                                      std::string function) {
    registry.emplace<ScriptComponent>(entity, ScriptComponent{
                                                     .language = ScriptLanguage::Python,
                                                     .pythonModule = std::move(module),
                                                     .pythonFunction = std::move(function),
                                                 });
}

void ScriptSystem::update(ecs::Registry& registry, float deltaSeconds) {
    registry.forEach<ScriptComponent>([&](ecs::Entity e, ScriptComponent& script) {
        switch (script.language) {
            case ScriptLanguage::Cpp:
                if (script.cppUpdate) {
                    script.cppUpdate(e, registry, deltaSeconds);
                }
                break;
            case ScriptLanguage::Python:
                if (pythonBridge_) {
                    pythonBridge_->callEntityUpdate(script.pythonModule, script.pythonFunction, e, registry, deltaSeconds);
                } else {
                    std::cerr << "[ScriptSystem] PythonBridge not set; skipping python script\n";
                }
                break;
        }
    });
}

}  // namespace pika::scripting
