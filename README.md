# Novomatic Internship Tasks 2026

## Requirements
- CMake 3.10+
- C++17 compiler
- Internet connection (dependencies downloaded automatically via FetchContent)

## Task 1 — Ticket Machine System
A multithreaded client-server simulation of a ticket vending machine. The server manages a pool of tickets with reservation, confirmation, and cancellation logic protected by a mutex. Multiple clients run concurrently in separate threads, each simulating a full purchase flow including a coin change algorithm with limited denominations and an automatic timeout mechanism for expired reservations.

### Build & Run
```bash
cd task1
mkdir build && cd build
cmake ..
make
./Task1
ctest --output-on-failure or ./Task1Tests
```

## Task 2 — Blueprint Auto Layout
An algorithm that automatically assigns 2D coordinates to nodes in a directed graph (blueprint), making it readable. Uses BFS-based layered layout — nodes are assigned columns by depth and rows by position within each column. Includes a GUI visualizer built with ImGui + GLFW that renders nodes as boxes with edges between them.

### Build & Run
```bash
cd task2
mkdir build && cd build
cmake ..
make
./Task2
ctest --output-on-failure or ./Task2Tests
```

## Task 3 — Log Analyzer
A console application for parsing and filtering structured log files. Supports filtering by timestamp range, log level, source, and message substring in any combination. Includes a CLI query engine which can take an outside file to read, by default it uses a file provided within the codebase.

### Build & Run
```bash
cd task3
mkdir build && cd build
cmake ..
make
./Task3 <your_textfile_path>
ctest --output-on-failure or ./Task3Tests
```

### Query syntax
logLevel="ERROR"
source="AuthService"
message="Transaction"
logLevel="ERROR" timestampFrom="2023-10-25T10:00:00" timestampTo="2023-10-25T10:10:00"
exit

## Notes
- All dependencies (GTest, nlohmann/json, ImGui, GLFW) are downloaded automatically by CMake
- Tested on macOS (Apple Silicon) — should build on Linux and Windows without changes
- C++17 required
