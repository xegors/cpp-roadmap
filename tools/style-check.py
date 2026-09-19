#!/usr/bin/env python3
"""Check (and fix) Yandex C++ style across this repo.

Usage:
    tools/style-check.py [--fix] [--no-naming] [<file>...]

Default: report style violations for every `.cpp`/`.h` under the repo root (or
only the given files) and exit 1 if any violation is found. With `--fix`,
clang-format -i is run and trailing whitespace is stripped, then whatever
cannot be fixed automatically (naming) is reported.

Checks:
  * formatting — conformance with the repo's `.clang-format`
                 (clang-format --dry-run --Werror --style=file)
  * whitespace — no tabs, no trailing whitespace
  * naming     — regex heuristics, NOT a full C++ parser:
      - struct/class/union types start with T, enum/enum class with E
      - function declarations start uppercase (main() and libc-like
        functions are allowed exceptions)
      - struct members start uppercase

Any naming flag must be reviewed manually: the heuristics look at line shape,
so a lowercase *call* after an assignment or `<<` may be mistaken for a
declaration. When in doubt, compile and check the line.

Requires `clang-format` on PATH.
"""

import argparse
import pathlib
import re
import subprocess

REPO_ROOT = pathlib.Path(__file__).resolve().parent.parent

SOURCE_EXTS = (".cpp", ".h", ".cc", ".cxx", ".hpp")
SKIP_DIRS = {".git", ".cache", ".devcontainer", "node_modules"}

KEYWORDS = {
    "auto", "bool", "catch", "char", "const", "delete", "do", "double", "dynamic_cast",
    "float", "for", "goto", "if", "int", "long", "new", "noexcept", "operator",
    "reinterpret_cast", "return", "short", "signed", "sizeof", "static_assert",
    "static_cast", "switch", "throw", "typeof", "unsigned", "void", "volatile",
    "wchar_t", "while", "int8_t", "int16_t", "int32_t", "int64_t", "uint8_t",
    "uint16_t", "uint32_t", "uint64_t", "size_t",
}

# Functions mirroring libc/STL keep their library naming (guide exception).
ALLOWED_FUNC_NAMES = {
    "main", "printf", "fprintf", "sprintf", "snprintf", "scanf", "sscanf",
    "getchar", "putchar", "getline", "gets", "puts", "abs", "pow", "atan2",
    "floor", "ceil", "round", "fmod", "memcpy", "memset", "memmove", "strlen",
    "strcmp", "strcpy", "malloc", "calloc", "free", "exit", "abort", "system",
    "atexit", "isalpha", "isdigit", "toupper", "tolower", "time",
}

TYPE_DECL_RE = re.compile(r"(?:struct|class|union|enum(?:\s+class)?)\s+(\w+)")

# A member line: indented, an identifier (maybe a sized array) then `;` and the
# line may carry an initializer: `int Qty = 3;`, `std::string Name;`.
MEMBER_LINE_RE = re.compile(
    r"^\s+[\w:<>,\s*&]*?\s(\w+)(?:\s*\[[^\]]*\])?\s*(?:=[^;]*)?;"
)

FUNC_DECL_RE = re.compile(r"(\w+)\s*\(")


def discover_files(arg_paths):
    if arg_paths:
        files = []
        for arg in arg_paths:
            p = pathlib.Path(arg)
            if p.is_dir():
                files.extend(f for f in p.rglob("*") if f.is_file() and f.suffix in SOURCE_EXTS)
            elif p.suffix in SOURCE_EXTS:
                files.append(p)
        return sorted({f.resolve() for f in files})
    return sorted(
        f for f in REPO_ROOT.rglob("*")
        if f.is_file() and f.suffix in SOURCE_EXTS
        and not any(part in SKIP_DIRS for part in f.parts)
    )


def check_formatting(path):
    res = subprocess.run(
        ["clang-format", "--dry-run", "--Werror", "--style=file", str(path)],
        capture_output=True, text=True,
    )
    return [] if res.returncode == 0 else ["clang-format would reformat"]


def check_whitespace(path):
    issues = []
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for i, line in enumerate(f, 1):
            if "\t" in line:
                issues.append(f"{i}: tab character")
            if line.rstrip("\r\n") != line.rstrip():
                issues.append(f"{i}: trailing whitespace")
    return issues


def check_naming(path):
    issues = []
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        lines = f.read().splitlines()

    in_region = False
    region_depth = 0

    for lineno, line in enumerate(lines, 1):
        stripped = line.strip()

        if not stripped or stripped.startswith("//") or stripped.startswith("#"):
            continue

        if in_region:
            region_depth += line.count("{") - line.count("}")
            if region_depth <= 0:
                in_region = False
                continue

            if stripped.startswith(("struct", "class", "union", "enum")):
                continue
            if stripped in ("public:", "private:", "protected:"):
                continue
            if "{" in line and "}" not in line:
                continue

            m = MEMBER_LINE_RE.match(line)
            if m:
                name = m.group(1)
                if name and not name[0].isupper():
                    issues.append(f"{lineno}: struct member `{name}` must start uppercase")
            continue

        type_m = TYPE_DECL_RE.search(stripped)
        if type_m and not stripped.startswith("template"):
            name = type_m.group(1)
            if "enum" in stripped:
                ok = name.startswith("E")
                kind = "enum/enum class"
            else:
                ok = name.startswith("T")
                kind = "struct/class/union"
            if not ok and not name.startswith(("std", "_")):
                issues.append(f"{lineno}: type `{name}` must start with "
                              f"{'E' if kind != 'struct/class/union' else 'T'} ({kind})")
            if "{" in stripped and ("struct" in stripped and "enum" not in stripped):
                in_region = True
                region_depth = line.count("{") - line.count("}")
            continue

        for m in FUNC_DECL_RE.finditer(line):
            name = m.group(1)
            if name in KEYWORDS or name in ALLOWED_FUNC_NAMES or name[0].isupper():
                continue

            prefix = line[: m.start()]
            if not prefix.strip():
                continue  # bare call at line start
            if prefix.rstrip().endswith((".", "->", ":", "::", "=", "(", ";", "{", "}", ",")):
                continue  # member call, namespace call, assignment, etc.
            if prefix.rstrip().endswith("<<"):
                continue  # chained into cout
            if "=" in prefix or "return" in prefix:
                continue  # call inside an expression / return
            if name.startswith(("std::", "_")):
                continue
            # `std::vector<std::pair<int, int>> points(...)` — a
            # constructor-style variable declaration, not a function
            # declaration (could not tell them apart otherwise).
            if "<" in prefix and prefix.rstrip().endswith(">"):
                continue

            issues.append(f"{lineno}: function declaration `{name}` must start uppercase")

    return issues


def strip_trailing_whitespace(path):
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        original = f.read()
    fixed = "\n".join(line.rstrip() for line in original.splitlines())
    if fixed != original:
        with open(path, "w", encoding="utf-8", errors="replace") as f:
            f.write(fixed)
        return True
    return False


def main():
    parser = argparse.ArgumentParser(description="Yandex C++ style checker")
    parser.add_argument("--fix", action="store_true", help="auto-fix formatting/whitespace")
    parser.add_argument("--no-naming", action="store_true", help="skip naming heuristics")
    parser.add_argument("files", nargs="*", help="files/dirs to check (default: whole repo)")
    args = parser.parse_args()

    clang_format = subprocess.run(
        ["clang-format", "--version"], capture_output=True, text=True)
    if clang_format.returncode != 0:
        print("ERROR: clang-format not found on PATH; install clang-tools",
              file=sys.stderr)
        return 2

    files = discover_files(args.files)
    if not files:
        print("No source files to check.")
        return 2

    failed = False
    for path in files:
        if args.fix:
            subprocess.run(
                ["clang-format", "-i", "--style=file", str(path)],
                check=True)
            strip_trailing_whitespace(path)

        formatting = check_formatting(path)
        ws = check_whitespace(path)
        naming = [] if args.no_naming else check_naming(path)

        issues = []
        issues += [f"    formatting: {m}" for m in formatting]
        issues += [f"    whitespace: {m}" for m in ws]
        issues += [f"    naming: {m}" for m in naming]

        if issues:
            failed = True
            marker = "FIXED" if (args.fix and not naming) else "FAIL"
            print(f"{marker} {path}")
            for issue in issues:
                print(issue)

    if args.fix and not failed:
        print("All clean after --fix.")
    elif not failed:
        print(f"OK ({len(files)} file(s))")
    return 1 if failed else 0


if __name__ == "__main__":
    import sys
    sys.exit(main())