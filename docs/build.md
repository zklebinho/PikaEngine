# Build & Export

## Prereqs
- CMake ≥ 3.20
- Ninja (recommended)
- C++20 toolchain for your platform
- Optional: Python dev headers (`PIKA_ENABLE_PYTHON`), Emscripten SDK for WebAssembly

## Presets
Use CMake presets for one-command builds:

```bash
# Windows (MSVC)
cmake --preset windows-msvc
cmake --build --preset windows

# Linux (GCC/Clang)
cmake --preset linux-gcc
cmake --build --preset linux

# WebAssembly (Emscripten)
cmake --preset wasm-emscripten
cmake --build --preset wasm
```

### WebAssembly notes
- Requires Emscripten on PATH (`emcc`, `em++`) or `EMSCRIPTEN` env pointing to the toolchain.
- Renderer/editor/plugins/examples are disabled in this preset to keep the build lean; you get the core engine library. Enable components progressively once WebGL/ports are wired.

## Custom options
- `PIKA_ENABLE_RENDERER` (ON/OFF) — toggle OpenGL renderer deps.
- `BUILD_EDITOR`, `BUILD_EXAMPLES`, `BUILD_PLUGINS` — component toggles.
- `PIKA_ENABLE_LUA`, `PIKA_ENABLE_PYTHON` — scripting bridges.

Example Linux debug build with renderer off:
```bash
cmake -S . -B build/debug -DPIKA_ENABLE_RENDERER=OFF -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug
```
