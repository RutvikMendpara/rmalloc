#pragma once

#include <cstddef>
#include <cstdint>

class Rmalloc {
public:
    void* allocate(std::size_t size);
    void* allocateZeroed(std::size_t count, std::size_t size);
    void* reallocate(void* ptr, std::size_t size);
    void  deallocate(void* ptr);
    ~Rmalloc();

    struct BlockMeta {
        std::size_t size;
        bool free;
        BlockMeta* next;
        std::uint32_t magic;

        static constexpr std::uint32_t MAGIC_USED = 0x77777777;
        static constexpr std::uint32_t MAGIC_FREE = 0x55555555;
        static constexpr std::uint32_t MAGIC_NEW  = 0x12345678;
    };

    BlockMeta* head = nullptr;

    BlockMeta* findFreeBlock(BlockMeta*& last, std::size_t size);
    BlockMeta* requestSpace(BlockMeta* last, std::size_t size);
    BlockMeta* getBlockPtr(void* ptr);
};
