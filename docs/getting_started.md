# Getting Started

## Prerequisites
- CMake = 3.20, Ninja recommended
- C++20 toolchain (MSVC, GCC, or Clang)
- Optional: Python dev headers (`KYLIE_ENABLE_PYTHON`), Emscripten SDK for wasm

## Configure & Build (desktop)
```bash
cmake --preset windows-msvc   # or linux-gcc
cmake --build --preset windows
```
Manual example:
```bash
cmake -S . -B build -DKYLIE_ENABLE_RENDERER=ON -DKYLIE_ENABLE_PYTHON=OFF
cmake --build build
```

## Run samples
- Minimal: `build/examples/minimal/KYLIE_example_minimal`
- 2D platformer: `build/examples/platformer2d/KYLIE_example_platformer2d`
- FPS: `build/examples/fps/KYLIE_example_fps`
- Empty: `build/examples/empty/KYLIE_example_empty`
- Editor (ImGui): `build/editor/kylieeditor`

## Enable Python scripting
```bash
cmake -S . -B build -DKYLIE_ENABLE_PYTHON=ON
cmake --build build
```
Ensure Python dev headers/libs are discoverable.

## WebAssembly (headless core)
```bash
cmake --preset wasm-emscripten
cmake --build --preset wasm
```
Renderer/editor/plugins/examples disabled by default for wasm; enable progressively once WebGL bindings are ready.

## Common Options
- `KYLIE_ENABLE_RENDERER` ON/OFF
- `BUILD_EDITOR`, `BUILD_EXAMPLES`, `BUILD_PLUGINS`
- `KYLIE_ENABLE_LUA`, `KYLIE_ENABLE_PYTHON`
