# Getting Started

## Prerequisites
- CMake = 3.20, Ninja recommended
- C++20 toolchain (MSVC, GCC, or Clang)
- Optional: Python dev headers (`PIKA_ENABLE_PYTHON`), Emscripten SDK for wasm

## Configure & Build (desktop)
```bash
cmake --preset windows-msvc   # or linux-gcc
cmake --build --preset windows
```
Manual example:
```bash
cmake -S . -B build -DPIKA_ENABLE_RENDERER=ON -DPIKA_ENABLE_PYTHON=OFF
cmake --build build
```

## Run samples
- Minimal: `build/examples/minimal/pika_example_minimal`
- 2D platformer: `build/examples/platformer2d/pika_example_platformer2d`
- FPS: `build/examples/fps/pika_example_fps`
- Empty: `build/examples/empty/pika_example_empty`
- Editor (ImGui): `build/editor/pikaeditor`

## Enable Python scripting
```bash
cmake -S . -B build -DPIKA_ENABLE_PYTHON=ON
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
- `PIKA_ENABLE_RENDERER` ON/OFF
- `BUILD_EDITOR`, `BUILD_EXAMPLES`, `BUILD_PLUGINS`
- `PIKA_ENABLE_LUA`, `PIKA_ENABLE_PYTHON`