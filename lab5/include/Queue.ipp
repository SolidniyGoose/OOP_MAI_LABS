#pragma once
#include "Queue.hpp"
#include <stdexcept>

template <typename T>
Queue<T>::Iterator::Iterator(Node* node) : current_(node) {}

template <typename T>
typename Queue<T>::Iterator::reference
Queue<T>::Iterator::operator*() const {
    return current_->value;
}

template <typename T>
typename Queue<T>::Iterator::pointer
Queue<T>::Iterator::operator->() const {
    return &current_->value;
}

template <typename T>
typename Queue<T>::Iterator&
Queue<T>::Iterator::operator++() {
    current_ = current_->next;
    return *this;
}

template <typename T>
typename Queue<T>::Iterator
Queue<T>::Iterator::operator++(int) {
    Iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
bool Queue<T>::Iterator::operator==(const Iterator& other) const {
    return current_ == other.current_;
}

template <typename T>
bool Queue<T>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template <typename T>
Queue<T>::Queue(std::pmr::memory_resource* mr)
    : head_(nullptr), tail_(nullptr), allocator_(mr) {}

template <typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Queue<T>::push(const T& value) {
    Node* node = allocator_.allocate(1);
    allocator_.construct(node, Node{value, nullptr});

    if (tail_) {
        tail_->next = node;
    } else {
        head_ = node;
    }
    tail_ = node;
}

template <typename T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("empty queue");
    }

    Node* old = head_;
    head_ = head_->next;

    allocator_.destroy(old);
    allocator_.deallocate(old, 1);

    if (!head_) {
        tail_ = nullptr;
    }
}

template <typename T>
T& Queue<T>::front() {
    if (empty()) {
        throw std::runtime_error("empty queue");
    }
    return head_->value;
}

template <typename T>
bool Queue<T>::empty() const {
    return head_ == nullptr;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(head_);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(nullptr);
}
