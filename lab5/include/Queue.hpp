#pragma once

#include <memory_resource>
#include <iterator>

template <typename T>
class Queue {
private:
    struct Node {
        T value;
        Node* next;
    };

public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        explicit Iterator(Node* node);

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* current_;
    };

public:
    explicit Queue(std::pmr::memory_resource* mr = std::pmr::get_default_resource());
    ~Queue();

    void push(const T& value);
    void pop();

    T& front();
    bool empty() const;

    Iterator begin();
    Iterator end();

private:
    Node* head_;
    Node* tail_;
    std::pmr::polymorphic_allocator<Node> allocator_;
};

#include "Queue.ipp"
