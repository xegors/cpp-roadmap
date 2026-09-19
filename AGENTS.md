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
.clang-format            # Yandex C++ style fork (see Conventions); existing files
                         # are NOT reformatted to it on purpose — see Conventions
```

## Compile and run

Compile individual files with clang++. No CMake, Makefile, or build config:

```
clang++ -lm -O2 -std=c++20 -x c++
```

Leftover `a.out` binaries sit next to sources but are already gitignored (`*.out`) — don't worry about them.

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
- Style varies between older files; when editing such a file, match its style unless
  you're rewriting it — new/leaf code follows Yandex conventions.
- No trailing `return 0;` is consistent in some files, not others — follow the existing pattern per file.
- A few files contain Russian inline comments (e.g. `printing-calendar.cpp`) — don't edit them or treat them as noise; they explain intent.
