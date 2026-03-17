#include "pika/Module.hpp"

#include <iostream>
#include <memory>

namespace pika::plugins {

#if defined(_WIN32)
#define PIKA_PLUGIN_EXPORT __declspec(dllexport)
#else
#define PIKA_PLUGIN_EXPORT
#endif

class SamplePlugin : public modules::IModule {
public:
    std::string name() const override { return "SamplePlugin"; }

    void onRegister(modules::ModuleRegistry& registry) override {
        std::cout << "[SamplePlugin] Registered with registry\n";
        (void)registry;
    }

    void onUpdate(float deltaTime) override {
        std::cout << "[SamplePlugin] Tick dt=" << deltaTime << "\n";
    }

    void onShutdown() override { std::cout << "[SamplePlugin] Shutdown\n"; }
};

PIKA_PLUGIN_EXPORT std::shared_ptr<modules::IModule> createSamplePlugin() {
    return std::make_shared<SamplePlugin>();
}

// Generic factory name so PluginManager can find it by default.
PIKA_PLUGIN_EXPORT std::shared_ptr<modules::IModule> createPlugin() {
    return createSamplePlugin();
}

}  // namespace pika::plugins
