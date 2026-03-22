// Plugin interface for dynamically loaded modules
#pragma once

#include "kylie/Module.hpp"

namespace kylie::plugins {

// Factory function signature that plugins should export.
using CreatePluginFn = std::shared_ptr<modules::IModule> (*)();

}  // namespace kylie::plugins
