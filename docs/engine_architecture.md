# Engine Architecture

## Core
- `KylieEngine` static lib: main loop (`Engine`), module registry, scripting hooks, node graph.
- ECS: sparse-set registry (`ecs/Registry.h`), entities, components, systems.
- Plugins: `PluginManager` dynamically loads shared libs exporting `createPlugin()` -> `IModule`.
- Scripting: C++ callbacks + optional Python bridge (`KYLIE_ENABLE_PYTHON`); Lua stub (`KYLIE_ENABLE_LUA`).

## Rendering
- Optional OpenGL renderer (GLFW + glad + ImGui) behind `KYLIE_ENABLE_RENDERER`.
- Editor reuses renderer stack; ImGui UI hosts panels (project, scene view, hierarchy, inspector).

## Editor
- Built as `kylieeditor`; currently ImGui-only stub with dockspace + core panels.

## Examples/Templates
- `examples/minimal`: engine tick + node graph demo.
- `examples/platformer2d`, `examples/fps`, `examples/empty`: starter templates.

## Build/Targets
- Presets in `CMakePresets.json` for Windows, Linux, WebAssembly.
- Renderer/editor/plugins/examples can be toggled via CMake options (see `docs/build.md`).
