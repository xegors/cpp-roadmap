# AGENTS.md

## What this repo is

Personal C++ practice — standalone solutions to Yandex C++ Handbook problems. Each `.cpp` file is a self-contained program with its own `main()`. No build system, no shared code, no tests.

## Structure

```
tasks/
  yandex-handbook/
    first-steps/      # basic I/O
    types/            # type conversions, arithmetic
    cond-and-loops/   # conditionals, loops
  leetcode/           # empty (placeholder)
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
- No trailing `return 0;` is consistent in some files, not others — follow the existing pattern per file.
- A few files contain Russian inline comments (e.g. `printing-calendar.cpp`) — don't edit them or treat them as noise; they explain intent.
