// PluginManager handles dynamic loading of plugin shared libraries (VS Code style extensions)
#pragma once

#include "plugins/IPlugin.h"

#include <filesystem>
#include <memory>
#include <vector>

namespace kylie::plugins {

class PluginManager {
public:
    ~PluginManager();

    // symbol defaults to "createPlugin"; override to match plugin export
    bool load(const std::filesystem::path& path, const char* symbol = "createPlugin");
    void unloadAll();

    std::vector<std::shared_ptr<modules::IModule>> modules() const;

private:
    struct PluginHandle {
        std::filesystem::path path;
        std::shared_ptr<modules::IModule> module;
        // Platform handle to shared library
        void* handle{nullptr};
    };
    std::vector<PluginHandle> plugins_;
};

}  // namespace kylie::plugins
