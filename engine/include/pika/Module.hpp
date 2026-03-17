// PikaEngine - Module interface and registry
#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pika::modules {

class ModuleRegistry;

class IModule {
public:
    virtual ~IModule() = default;

    virtual std::string name() const = 0;
    virtual void onRegister(ModuleRegistry& registry) { (void)registry; }
    virtual void onUpdate(float /*deltaTime*/) {}
    virtual void onShutdown() {}
};

class ModuleRegistry {
public:
    bool registerModule(const std::shared_ptr<IModule>& module);
    std::shared_ptr<IModule> getModule(const std::string& name) const;
    std::vector<std::string> listModules() const;

    // Called by Engine each tick
    void updateAll(float deltaTime);

private:
    std::unordered_map<std::string, std::shared_ptr<IModule>> modules_;
};

}  // namespace pika::modules
