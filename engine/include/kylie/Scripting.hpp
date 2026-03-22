// KylieEngine - Scripting hook (Lua-ready stub)
#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace kylie::scripting {

class ScriptingEngine {
public:
    bool runScript(std::string_view code);
    bool runFile(const std::filesystem::path& path);

private:
    bool run(std::string_view label, std::string_view code);
};

}  // namespace kylie::scripting
