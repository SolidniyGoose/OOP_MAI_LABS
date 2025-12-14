#pragma once

#include <memory_resource>
#include <list>
#include <cstddef>

class DynamicListMemory : public std::pmr::memory_resource {
public:
    DynamicListMemory();
    ~DynamicListMemory() override;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void  do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool  do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    std::list<void*> allocated_blocks_;
};
