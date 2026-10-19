# MiniKV

A small key-value database written in C++17.

**Status:** in progress (day 1 of 7)

## Features
- `set`, `get`, `del`, `exists` on an in-memory hash map

## Build and run

    cmake -B build
    cmake --build build
    ./build/minikv

## Planned
- Command-line interface (SET / GET / DEL)
- Persistence with an append-only log
- Unit tests
- TCP server and Dockerfile
