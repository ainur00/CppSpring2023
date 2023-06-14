#pragma once

struct Chunk {
    Chunk* next;
};

class PoolAllocator {
public:
    PoolAllocator(size_t chunksPerBlock) : chunksPerBlock_(chunksPerBlock), alloc_(nullptr) { }

    void* allocate(size_t size) {
        if (alloc_ == nullptr) {
            alloc_ = allocateBlock(size);
        }
        Chunk* toAlloc = alloc_;
        alloc_ = alloc_->next;
        return reinterpret_cast<void*>(toAlloc);
    }

    void deallocate(void* chunk, size_t size) {
        reinterpret_cast<Chunk*>(chunk)->next = alloc_->next;
        alloc_->next = reinterpret_cast<Chunk*>(chunk);
    }

private:
    size_t chunksPerBlock_;
    Chunk* alloc_;

private:
    Chunk* allocateBlock(size_t chunkSize) {
        int8_t* memoryBlock = new int8_t[chunkSize * chunksPerBlock_];
        Chunk* rootChunk = nullptr;
        for (size_t i = 0; i < chunksPerBlock_; ++i) {
        	Chunk* currentChunk = reinterpret_cast<Chunk*>(memoryBlock + chunkSize * (chunksPerBlock_ - (i + 1)));
        	currentChunk->next = rootChunk;
        	rootChunk = currentChunk;
        }
        return rootChunk;
    }
};
