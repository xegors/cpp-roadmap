# AGENTS.md

## What this repo is

Personal C++ practice — standalone solutions to Yandex C++ Handbook problems plus small
learning projects. Each `.cpp` file is a self-contained program with its own `main()`.
No build system, no shared code, no tests.

Repo docs: `README.md` (Russian, user-facing overview + progress), `LICENSE` (MIT).

## Structure

```
tasks/
  yandex-handbook/
    first-steps/         # basic I/O
    types/               # type conversions, arithmetic
    cond-and-loops/      # conditionals, loops
    vectors-and-strings/ # vectors and strings
    functions/           # functions
projects/
  shop-catalog/          # learning project: product catalog (struct, enum, refs, pointers);
                         # all task statements consolidated in TASKS.md
README.md                # Russian overview, build instructions, progress
LICENSE                  # MIT
.clang-format            # Yandex C++ style (see Conventions); whole repo conforms
.clangd                  # clangd fallback flags (-std=c++20) — there is no build system
.editorconfig            # tabs->spaces, 4-space indent, trim trailing whitespace
.vscode/                 # VS Code: format-on-save via clangd + extension recommendation
.devcontainer/           # Dev Container: clang/clangd/clang-format/cppcheck/python3
tools/style-check.py     # style checker (a local replacement for `ya style`)
```

## Style checking

`tools/style-check.py` checks the whole repo (or explicit files) against
Yandex style:

```
tools/style-check.py              # report violations, exit 1 if any
tools/style-check.py --fix        # auto-format (clang-format -i + strip trailing ws)
tools/style-check.py <file>...    # targeted check
```

Checks: formatting conformance via `clang-format --dry-run --Werror`, no tabs /
trailing whitespace, and naming heuristics (types `T`/`E`, uppercase functions
and struct members, `main()` and libc-like functions exempt). The naming rules
are line-shape heuristics, not a full C++ parser — review every flag manually.
Requires `clang-format` on PATH.

## Compile and run

Compile individual files with clang++. No CMake, Makefile, or build config:

```
clang++ -lm -O2 -std=c++20 -x c++
```

Leftover `a.out` binaries sit next to sources but are already gitignored (`*.out`) — don't worry about them.

## Editor tooling

- `.vscode/settings.json` + `extensions.json` — format-on-save via the clangd
  extension (`llvm-vs-code-extensions.vscode-clangd`), 4-space indent, trim
  trailing whitespace.
- `.clangd` — clangd fallback flags (`-std=c++20 -Wall -Wextra`), needed because
  there is no build system / `compile_commands.json`.
- `.devcontainer/` — reproducible environment (clang, clang-format, clangd,
  cppcheck, python3) for VS Code Dev Containers; identical on any machine.
  Requires only Docker on the host.

## Conventions

- Each file is a single `main()` — no headers, no classes, no build targets.
  (Exception: `tasks/yandex-handbook/functions/` has a few helper-only `.cpp` without `main`.)
- Code follows the **Yandex C++ Style Guide**:
  https://github.com/yandex/CMICOT/blob/master/CPP_STYLE_GUIDE.md
  Formatting is enforced by `.clang-format` (1TBS, 4-space indent, no tabs,
  bodies always start on a new line). Naming is checked manually — key rules:
  - Functions and class/struct members start with a capital letter: `FindByName()`, `Name`, `Price`.
  - Type names get the `T` prefix, `enum class` gets the `E` prefix: `TProduct`, `ECategory`.
  - Local variables and arguments start with a lowercase letter: `catalog`, `name`.
  - Constants and macros are fully capitalized with underscores: `VALUE_NAME`.
  - Always use `nullptr`, never `NULL`/`0`.
- Style is enforced by `tools/style-check.py` (see above); the whole repo passes.
  When editing, format with `clang-format` from the repo root and re-run the checker.
- No trailing `return 0;` is consistent in some files, not others — follow the existing pattern per file.
- A few files contain Russian inline comments (e.g. `printing-calendar.cpp`) — don't edit them or treat them as noise; they explain intent.
