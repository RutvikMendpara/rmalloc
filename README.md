# Custom Memory Allocator (Unix, C++)

A low-level memory allocator built from scratch for Unix-like systems in C++. Supports:

- First-fit allocation strategy
- Block splitting and coalescing
- Page-level memory management via `mmap`
- LD_PRELOAD-compatible replacement for `malloc` and `free`
- Arena allocator for fixed-size allocations

### Build & Run

```bash
cmake -B build
cmake --build build
./build/memory_allocator_test
