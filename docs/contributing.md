# Contributing

## Workflow
1) Fork & branch per feature.
2) Format and keep warnings clean (`-Wall -Wextra -Werror` recommended).
3) Add/adjust tests or examples when behavior changes.
4) Keep changes small; document public API changes in `README` or `docs/`.

## Style
- C++20, prefer modern std facilities.
- Avoid heavy dependencies; keep build fast.
- Keep headers minimal and self-explanatory; add brief comments where non-obvious.

## PR checklist
- Builds on Windows/macOS/Linux.
- Examples compile.
- No new warnings.
- Update docs if behavior changes.