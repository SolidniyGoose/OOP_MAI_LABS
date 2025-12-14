#include "DynamicMemory.hpp"
#include <new>
#include <algorithm>

DynamicListMemory::DynamicListMemory() = default;

DynamicListMemory::~DynamicListMemory() {
    for (void* ptr : allocated_blocks_) {
        ::operator delete(ptr);
    }
    allocated_blocks_.clear();
}

void* DynamicListMemory::do_allocate(std::size_t bytes, std::size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks_.push_back(ptr);
    return ptr;
}

void DynamicListMemory::do_deallocate(void* p, std::size_t, std::size_t alignment) {
    auto it = std::find(allocated_blocks_.begin(), allocated_blocks_.end(), p);
    if (it != allocated_blocks_.end()) {
        ::operator delete(p, std::align_val_t(alignment));
        allocated_blocks_.erase(it);
    }
}

bool DynamicListMemory::do_is_equal(
    const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
