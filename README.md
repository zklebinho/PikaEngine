# PikaEngine

A tiny, modular C++20 game engine + editor prototype inspired by Godot/Unreal. This repo now includes a runnable editor, sandbox scene loader, plugin/AI placeholders, and a GLFW/OpenGL/ImGui rendering stack.

## What's inside
- `engine/` core runtime (modules, ECS stub, scripting stubs, renderer/window, sandbox scene loader, AI placeholder)
- `editor/` ImGui editor UI (dockspace + Scene/Hierarchy/Inspector/Assets/Console/Viewport panels)
- `assets/` starter content (`scenes/test.scene`, models/, textures/, scripts/)
- `plugins/` sample plugin + plugin manager
- `launcher/` CLI entry that can start editor (default) or sandbox mode

## Build (Windows, CMake = 3.20)
```bash
cmake -S . -B build
cmake --build build --target pikaeditor pika_sandbox pika_launcher
```

Run targets (from repo root or `build/` depending on your generator):
```bash
./build/pikaeditor        # editor UI with docked panels
./build/pika_sandbox      # sandbox scene viewer
./build/pika_launcher     # launcher (defaults to editor, use --sandbox for sandbox)
```

Options (see `cmake/PikaOptions.cmake`):
- `PIKA_ENABLE_RENDERER` (ON) — GLFW/GLAD/ImGui renderer
- `BUILD_EDITOR` (ON), `BUILD_SANDBOX` (ON), `BUILD_LAUNCHER` (ON)
- `BUILD_PLUGINS`, `BUILD_EXAMPLES`, `PIKA_ENABLE_LUA`, `PIKA_ENABLE_PYTHON`

## Editor UI
- Dockspace main window with menus: File, Edit, Project, Window, Help
- Panels: Scene, Hierarchy, Inspector, Assets, Console, Viewport + FPS status line
- Colored OpenGL background and ImGui rendering

## Sandbox
- Loads `assets/scenes/test.scene` (simple YAML/JSON-like list) and shows entities in an ImGui panel.

## Notes
- Renderer uses GLFW + GLAD + Dear ImGui (via FetchContent). No external installs required on Windows/MSVC.
- Console prints `Pika Engine started successfully` on startup.

## Contributing
See `docs/contributing.md`.
