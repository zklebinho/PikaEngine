// Plugin interface for dynamically loaded modules
#pragma once

#include "pika/Module.hpp"

namespace pika::plugins {

// Factory function signature that plugins should export.
using CreatePluginFn = std::shared_ptr<modules::IModule> (*)();

}  // namespace pika::plugins
