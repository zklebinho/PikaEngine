// PluginManager handles dynamic loading of plugin shared libraries
#pragma once

#include "plugins/IPlugin.h"

#include <filesystem>
#include <memory>
#include <vector>

namespace pika::plugins {

class PluginManager {
public:
    ~PluginManager();

    // symbol defaults to "createPlugin"; override to match plugin export
    bool load(const std::filesystem::path& path, const char* symbol = "createPlugin");
    void unloadAll();

    std::vector<std::shared_ptr<modules::IModule>> modules() const;

private:
    struct PluginHandle;
    std::vector<PluginHandle> plugins_;
};

}  // namespace pika::plugins
