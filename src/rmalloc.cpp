#include "rmalloc/rmalloc.h"
#include <cstdlib>
#include <cstring>
#include <cassert>

using BlockMeta = Rmalloc::BlockMeta;

BlockMeta* Rmalloc::findFreeBlock(BlockMeta*& last, std::size_t size) {
    BlockMeta* current = head;
    while (current && !(current->free && current->size >= size)) {
        last = current;
        current = current->next;
    }
    return current;
}

BlockMeta* Rmalloc::requestSpace(BlockMeta* last, std::size_t size) {
    void* raw = std::malloc(sizeof(BlockMeta) + size);
    if (!raw) return nullptr;

    auto* block = static_cast<BlockMeta*>(raw);
    block->size = size;
    block->next = nullptr;
    block->free = false;
    block->magic = BlockMeta::MAGIC_NEW;

    if (last) {
        last->next = block;
    }

    return block;
}

BlockMeta* Rmalloc::getBlockPtr(void* userPtr) {
    return static_cast<BlockMeta*>(userPtr) - 1;
}

void* Rmalloc::allocate(std::size_t size) {
    if (size == 0) return nullptr;

    BlockMeta* block = nullptr;

    if (!head) {
        block = requestSpace(nullptr, size);
        if (!block) return nullptr;
        head = block;
    } else {
        BlockMeta* last = head;
        block = findFreeBlock(last, size);
        if (!block) {
            block = requestSpace(last, size);
            if (!block) return nullptr;
        } else {
            block->free = false;
            block->magic = BlockMeta::MAGIC_USED;
        }
    }

    return block + 1;
}

void Rmalloc::deallocate(void* ptr) {
    if (!ptr) return;

    BlockMeta* block = getBlockPtr(ptr);
    assert(!block->free);
    assert(block->magic == BlockMeta::MAGIC_USED || block->magic == BlockMeta::MAGIC_NEW);

    block->free = true;
    block->magic = BlockMeta::MAGIC_FREE;
}

void* Rmalloc::reallocate(void* ptr, std::size_t size) {
    if (!ptr) return allocate(size);

    BlockMeta* block = getBlockPtr(ptr);
    if (block->size >= size) return ptr;

    void* newPtr = allocate(size);
    if (!newPtr) return nullptr;

    std::memcpy(newPtr, ptr, block->size);
    deallocate(ptr);
    return newPtr;
}

void* Rmalloc::allocateZeroed(std::size_t nelem, std::size_t elsize) {
    std::size_t size = nelem * elsize;
    void* ptr = allocate(size);
    if (ptr) std::memset(ptr, 0, size);
    return ptr;
}

Rmalloc::~Rmalloc() {
    BlockMeta* current = head;
    while (current) {
        BlockMeta* next = current->next;
        std::free(current);
        current = next;
    }
}
