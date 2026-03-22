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

namespace kylie::plugins {

namespace {

#if defined(_WIN32)
inline void* loadLibrary(const std::filesystem::path& p) { return reinterpret_cast<void*>(LoadLibraryW(p.wstring().c_str())); }
inline void closeLibrary(void* h) { if (h) FreeLibrary(reinterpret_cast<HMODULE>(h)); }
inline void* loadSymbol(void* h, const char* name) { return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(h), name)); }
#else
inline void* loadLibrary(const std::filesystem::path& p) { return dlopen(p.string().c_str(), RTLD_NOW); }
inline void closeLibrary(void* h) { if (h) dlclose(h); }
inline void* loadSymbol(void* h, const char* name) { return dlsym(h, name); }
#endif

}  // namespace

PluginManager::~PluginManager() { unloadAll(); }

bool PluginManager::load(const std::filesystem::path& path, const char* symbol) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "[PluginManager] File not found: " << path << "\n";
            return false;
        }
        void* lib = loadLibrary(path);
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

}  // namespace kylie::plugins
