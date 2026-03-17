#include "pika/Scripting.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace pika::scripting {

bool ScriptingEngine::runScript(std::string_view code) { return run("memory", code); }

bool ScriptingEngine::runFile(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        std::cerr << "[Scripting] File not found: " << path << "\n";
        return false;
    }
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return run(path.string(), buffer.str());
}

bool ScriptingEngine::run(std::string_view label, std::string_view code) {
#ifdef PIKA_ENABLE_LUA
    std::cout << "[Scripting] (Lua stub) Executing script: " << label << "\n";
    (void)code;
    // Real Lua integration will live here.
    return true;
#else
    std::cout << "[Scripting] Lua disabled. Skipping script: " << label << "\n";
    (void)code;
    return false;
#endif
}

}  // namespace pika::scripting
