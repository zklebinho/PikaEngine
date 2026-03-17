# PikaEngine

A tiny, modular C++20 game engine inspired by Godot, Unreal Engine, and Scratch. The goal is to stay **extremely lightweight**, keep the core clear, and let modules, scripting, and visual blocks do the heavy lifting.

## Features (initial skeleton)
- C++20 core with a minimal main loop
- Module registry for engine extensions
- Optional Lua hook (stubbed) for scripting
- Visual block graph model (nodes, pins, connections)
- Sample plugin + minimal example app
- Editor CLI placeholder ready for a future GUI

## Directory layout
- `engine/` — core engine library (`pikaengine`): modules, scripting hook, node graph
- `editor/` — CLI editor stub linking `pikaengine`
- `plugins/` — sample plugin implementing `IModule`
- `examples/` — runnable samples; `minimal/` shows engine + plugin + scripting stub
- `docs/` — architecture, roadmap, contributing notes
- `cmake/` — build options and third-party stubs

## Build (CMake = 3.20)
```bash
cmake -S . -B build -DPIKA_ENABLE_LUA=OFF
cmake --build build
```

Enable the Lua hook (stubbed, no external deps yet):
```bash
cmake -S . -B build -DPIKA_ENABLE_LUA=ON
cmake --build build
```

Build sample plugin + example:
```bash
cmake --build build --target sample_plugin pika_example_minimal
```

Run example (path may vary per platform):
```bash
./build/examples/minimal/pika_example_minimal
```

## Roadmap
- Hook real Lua VM and script bindings
- GUI editor with node-based visual scripting
- Hot-reloadable plugin loader per platform
- Asset pipeline + scene format
- Automated tests and CI

## Contributing
See `docs/contributing.md`. PRs and issues welcome.