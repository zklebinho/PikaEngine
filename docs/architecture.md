# Architecture

## Core loop
- `Engine` owns a `ModuleRegistry` and drives a simple tick (`update(float dt)`).
- Modules register themselves; engine iterates them each frame.
- Hooks exist for future lifecycle: initialize, update, shutdown.

## Modules
- Interface: `IModule` with `name()`, `onRegister(ModuleRegistry&)`, `onUpdate(float)`, `onShutdown()`.
- Registry tracks modules by string key; supports manual registration now; dynamic loading is stubbed.

## Scripting
- `ScriptingEngine` placeholder; when `KYLIE_ENABLE_LUA` is ON it toggles a compile-time path to integrate a Lua VM later.
- API: `runScript(std::string_view code)` and `runFile(const std::filesystem::path&)` returning success/failure.

## Visual blocks
- `NodeGraph` stores nodes, pins, connections in-memory.
- Minimal serialization stub to JSON-like text for debugging; swap to real JSON later.

## Editor
- CLI stub links `KylieEngine`, prints registered modules; ready to be swapped with GUI.

## Plugins
- `sample_plugin` implements `IModule` and registers itself with the registry; built as shared lib when `BUILD_PLUGINS` is ON.

## Examples
- `examples/minimal` spins the engine, registers the sample plugin, runs a few ticks, optionally executes a script.
