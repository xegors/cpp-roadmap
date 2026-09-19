FROM mcr.microsoft.com/devcontainers/cpp:1-debian

RUN apt-get update && apt-get install -y --no-install-recommends \
        clang \
        clang-format \
        clangd \
        cppcheck \
        python3 \
    && rm -rf /var/lib/apt/lists/*