#include "pika/Module.hpp"

#include <iostream>

namespace pika::modules {

bool ModuleRegistry::registerModule(const std::shared_ptr<IModule>& module) {
    if (!module) {
        return false;
    }
    const auto key = module->name();
    if (modules_.count(key) != 0) {
        std::cerr << "[ModuleRegistry] Module already registered: " << key << "\n";
        return false;
    }
    modules_.emplace(key, module);
    module->onRegister(*this);
    std::cout << "[ModuleRegistry] Registered module: " << key << "\n";
    return true;
}

std::shared_ptr<IModule> ModuleRegistry::getModule(const std::string& name) const {
    auto it = modules_.find(name);
    if (it != modules_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::string> ModuleRegistry::listModules() const {
    std::vector<std::string> names;
    names.reserve(modules_.size());
    for (const auto& kv : modules_) {
        names.push_back(kv.first);
    }
    return names;
}

void ModuleRegistry::updateAll(float deltaTime) {
    for (auto& kv : modules_) {
        kv.second->onUpdate(deltaTime);
    }
}

}  // namespace pika::modules
