# MiniKV

A small key-value database written in C++17. It keeps data in memory in a hash table and saves every change to an append-only log file, so data survives restarts.

## Features
- Commands: SET, GET, DEL, EXISTS, SIZE, QUIT
- Values may contain spaces
- Persistence through an append-only log that is replayed on startup
- Recovery from a half-written last log line (for example after a crash)
- Unit tests with Catch2 (store, command parser, restart behavior)

## Build and run
~~~
cmake -B build
cmake --build build
./build/minikv            # uses minikv.log in the current folder
./build/minikv my.log     # or a log file of your choice
~~~

## Example session
~~~
> SET name Rihem Zorgui
OK
> GET name
Rihem Zorgui
> DEL name
1
> GET name
(nil)
> QUIT
~~~

## Run the tests
~~~
./build/minikv_tests
~~~

## Project structure
- src/kvstore.* : the database and the log
- src/parser.* : command parsing
- src/main.cpp : interactive command line
- tests/ : Catch2 unit tests

## Status
Core features and tests are done. Planned next: a TCP server mode and a Dockerfile.
