#pragma once

#include "array.hpp"
#include <algorithm>

template <typename T>
Array<T>::Array() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Array<T>::Array(size_t n) : size_(n), capacity_(n) {
    if (n == 0) {
        data_.reset();
        return;
    }
    data_ = std::shared_ptr<T[]>(new T[n], std::default_delete<T[]>());
}

template <typename T>
Array<T>::Array(const Array& other)
    : size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ == 0) {
        data_.reset();
        return;
    }
    data_ = std::shared_ptr<T[]>(new T[capacity_], std::default_delete<T[]>());
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
Array<T>::Array(Array&& other) noexcept
    : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Array<T>::~Array() {
    Clear();
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        Array tmp(other);
        *this = std::move(tmp);
    }
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
size_t Array<T>::Size() const noexcept { return size_; }

template <typename T>
size_t Array<T>::Capacity() const noexcept { return capacity_; }

template <typename T>
bool Array<T>::Empty() const noexcept { return size_ == 0; }

template <typename T>
T& Array<T>::operator[](size_t index) { return data_[index]; }

template <typename T>
const T& Array<T>::operator[](size_t index) const { return data_[index]; }

template <typename T>
T& Array<T>::At(size_t index) {
    if (index >= size_) throw std::out_of_range("Array index out of range");
    return data_[index];
}

template <typename T>
const T& Array<T>::At(size_t index) const {
    if (index >= size_) throw std::out_of_range("Array index out of range");
    return data_[index];
}

template <typename T>
void Array<T>::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) return;

    std::shared_ptr<T[]> new_data(new T[new_capacity], std::default_delete<T[]>());
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    data_ = std::move(new_data);
    capacity_ = new_capacity;
}

template <typename T>
void Array<T>::PushBack(const T& value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

template <typename T>
void Array<T>::PushBack(T&& value) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template <typename T>
void Array<T>::PopBack() {
    if (size_ == 0) return;
    --size_;
}

template <typename T>
void Array<T>::Erase(size_t index) {
    if (index >= size_) throw std::out_of_range("Array index out of range");
    for (size_t i = index; i + 1 < size_; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

template <typename T>
void Array<T>::Clear() {
    data_.reset();
    size_ = 0;
    capacity_ = 0;
}
