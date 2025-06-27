#include "rmalloc/rmalloc.h"
#include <cassert>
#include <cstring>
#include <iostream>

int main() {
    
    Rmalloc allocator;

    // Allocate 32 bytes
    void* ptr1 = allocator.allocate(32);
    assert(ptr1 != nullptr);
    std::memset(ptr1, 0xAB, 32);  // Fill with junk
    std::cout << "Allocation 1 OK\n";

    // Allocate another 64 bytes
    void* ptr2 = allocator.allocate(64);
    assert(ptr2 != nullptr);
    std::memset(ptr2, 0xCD, 64);
    std::cout << "Allocation 2 OK\n";

    // Free first block
    allocator.deallocate(ptr1);
    std::cout << "Deallocate 1 OK\n";

    // Reallocate second block to 128 bytes
    void* ptr2_re = allocator.reallocate(ptr2, 128);
    assert(ptr2_re != nullptr);
    std::cout << "Reallocation OK\n";

    // Calloc test
    void* ptr3 = allocator.allocateZeroed(10, 4); // 40 bytes
    assert(ptr3 != nullptr);
    for (int i = 0; i < 40; ++i) {
        assert(static_cast<unsigned char*>(ptr3)[i] == 0);
    }
    std::cout << "Zeroed allocation OK\n";

    // Clean exit
    allocator.deallocate(ptr2_re);
    allocator.deallocate(ptr3);
    std::cout << "All tests passed.\n";

    return 0;
}
