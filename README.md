# Custom Memory Allocator (C++)

A basic memory allocator written in C++ for Unix systems.

### Features

* First-fit allocation
* Manual `malloc`, `calloc`, `realloc`, and `free`
* Metadata tracking with free list
* Debug-friendly (asserts + magic headers)

### Build

```bash
cmake -B build
cmake --build build
./build/test_main  # Runs the test from test/main.cpp
```
