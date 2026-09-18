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
                         # task statements live next to code in *.md files (see TASKS.md)
README.md                # Russian overview, build instructions, progress
LICENSE                  # MIT
.clang-format            # shared minimum style (LLVM base, 4-space indent); existing files
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
- Style varies slightly between files; match the style of the file you're editing.
  Use `.clang-format` for new code (LLVM base, 4-space indent, 100-col limit).
- No trailing `return 0;` is consistent in some files, not others — follow the existing pattern per file.
- A few files contain Russian inline comments (e.g. `printing-calendar.cpp`) — don't edit them or treat them as noise; they explain intent.
