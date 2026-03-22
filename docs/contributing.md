# Contributing

## Workflow
1) Fork and branch per feature/bug.
2) Prefer small, focused PRs; include context in description.
3) Keep warnings clean (`-Wall -Wextra -Wpedantic`, `/W4`); enable `KYLIE_STRICT_WARNINGS` (default ON).
4) Update/ add examples or tests when behavior changes.
5) Document public APIs and options (`docs/`, `README.md`).

## Code Style
- C++20, modern std first; minimize dependencies.
- Headers should be lightweight and self-contained.
- Prefer sparse-set patterns for ECS; keep data layouts cache-aware.
- Renderer gated by `KYLIE_ENABLE_RENDERER`; avoid hard deps when OFF.

## Testing & Builds
- Desktop: `cmake --preset windows-msvc` or `linux-gcc`; `cmake --build --preset <name>`.
- Wasm: `cmake --preset wasm-emscripten` (core only by default).
- Run sample executables in `build/examples/...`; editor at `build/editor/kylieeditor`.

## Plugins & Scripts
- Plugins export `createPlugin()` returning `std::shared_ptr<IModule>`.
- Python bridge requires `KYLIE_ENABLE_PYTHON=ON` and Python dev headers.

## Commit Hygiene
- Use present-tense, concise messages (e.g., `feat: add ecs registry`).
- Avoid committing generated files or local build artifacts.
