#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>

template <typename T>
class Array {
public:
    Array();
    explicit Array(size_t n);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool Empty() const noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& At(size_t index);
    const T& At(size_t index) const;

    void PushBack(const T& value);
    void PushBack(T&& value);
    void PopBack();
    void Erase(size_t index);
    void Clear();

private:
    void Reserve(size_t new_capacity);

    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
};
#include "array.ipp"