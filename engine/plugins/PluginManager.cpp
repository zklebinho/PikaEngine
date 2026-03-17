#include "plugins/PluginManager.h"

#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>

#if defined(_WIN32)
    #include <Windows.h>
#else
    #include <dlfcn.h>
#endif

namespace pika::plugins {

namespace {

#if defined(_WIN32)
using LibHandle = HMODULE;
inline LibHandle loadLibrary(const std::filesystem::path& p) { return LoadLibraryW(p.wstring().c_str()); }
inline void closeLibrary(LibHandle h) { if (h) FreeLibrary(h); }
inline void* loadSymbol(LibHandle h, const char* name) { return reinterpret_cast<void*>(GetProcAddress(h, name)); }
#else
using LibHandle = void*;
inline LibHandle loadLibrary(const std::filesystem::path& p) { return dlopen(p.string().c_str(), RTLD_NOW); }
inline void closeLibrary(LibHandle h) { if (h) dlclose(h); }
inline void* loadSymbol(LibHandle h, const char* name) { return dlsym(h, name); }
#endif

}  // namespace

struct PluginManager::PluginHandle {
    std::filesystem::path path;
    std::shared_ptr<modules::IModule> module;
    LibHandle handle{nullptr};
};

PluginManager::~PluginManager() { unloadAll(); }

bool PluginManager::load(const std::filesystem::path& path, const char* symbol) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "[PluginManager] File not found: " << path << "\n";
            return false;
        }
        LibHandle lib = loadLibrary(path);
        if (!lib) {
            std::cerr << "[PluginManager] Failed to load: " << path << "\n";
            return false;
        }

        auto* fnPtr = reinterpret_cast<CreatePluginFn>(loadSymbol(lib, symbol));
        if (!fnPtr) {
            std::cerr << "[PluginManager] Symbol not found: " << symbol << " in " << path << "\n";
            closeLibrary(lib);
            return false;
        }

        auto module = fnPtr();
        if (!module) {
            std::cerr << "[PluginManager] Factory returned null for " << path << "\n";
            closeLibrary(lib);
            return false;
        }

        PluginHandle handle{path, std::move(module), lib};
        plugins_.push_back(std::move(handle));
        return true;
    }

void PluginManager::unloadAll() {
        for (auto& p : plugins_) {
            p.module.reset();
            closeLibrary(p.handle);
        }
        plugins_.clear();
    }

std::vector<std::shared_ptr<modules::IModule>> PluginManager::modules() const {
        std::vector<std::shared_ptr<modules::IModule>> result;
        result.reserve(plugins_.size());
        for (const auto& p : plugins_) {
            result.push_back(p.module);
        }
        return result;
    }

}  // namespace pika::plugins
