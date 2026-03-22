# KylieEngine

Modular C++20 game engine + visual editor (GLFW + OpenGL + Dear ImGui) renamed from PikaEngine to **Kylie Engine**.

## What's inside
- `engine/` core runtime (modules, ECS stub, scripting stubs, renderer/window, scene system, visual scripting graph, dimensions config, AI placeholder)
- `engine/scene/` Scene/Entity/Component/SceneManager with create/load/save/switch
- `engine/visual_scripting/` node-based graph stubs (event/logic/math/game-object nodes, editable code per block)
- `engine/dimensions/` Dimension1D/2D/3D presets (camera/physics/rendering)
- `editor/` ImGui editor UI (dockspace + Top Menu, Toolbar, Scene View, Hierarchy, Inspector, Assets Browser, Console, Game Preview panels)
- `assets/` starter content (`scenes/test.scene`, models/, textures/, audio/, scripts/)
- `plugins/` sample plugin + runtime loader
- `launcher/` CLI entry (editor by default, sandbox with `--sandbox`)

## Build (Windows, CMake >= 3.20)
```bash
cmake -S . -B build
cmake --build build --target kylieeditor kylie_sandbox kylie_launcher
```

Run targets (from repo root or `build/` depending on your generator):
```bash
./build/kylieeditor       # editor UI
./build/kylie_sandbox     # sandbox scene viewer
./build/kylie_launcher    # launcher (defaults to editor, use --sandbox for sandbox)
```

Options (see `cmake/KylieOptions.cmake`):
- `KYLIE_ENABLE_RENDERER` (ON) ? GLFW/GLAD/ImGui renderer
- `BUILD_EDITOR` (ON), `BUILD_SANDBOX` (ON), `BUILD_LAUNCHER` (ON)
- `BUILD_PLUGINS`, `BUILD_EXAMPLES`, `KYLIE_ENABLE_LUA`, `KYLIE_ENABLE_PYTHON`

## Editor UI
- Dockspace main window with menus: File, Edit, Project, Window, Help
- Toolbar with Play/Stop/Pause/Build
- Panels: Scene View, Hierarchy, Inspector, Assets Browser, Console, Game Preview + FPS status line

## Scene & Sandbox
- Scene system with load/save (`assets/scenes/test.scene`) and auto sandbox creation on startup.
- Sandbox and launcher visualize the active scene and entities.

## Notes
- Renderer uses GLFW + GLAD + Dear ImGui (via FetchContent). No external installs required on Windows/MSVC.
- Console prints `Kylie Engine started successfully` on startup.

## Contributing
See `docs/contributing.md`.
