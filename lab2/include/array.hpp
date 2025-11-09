#pragma once

#include <cstddef>
#include <string>
#include <initializer_list>
#include <stdexcept>

namespace Array{
class Array{
    private:
        std::size_t _capacity = 0;
        std::size_t _size = 0;
        unsigned char* _data = nullptr;
    public:
        Array();
        Array(const size_t & n, unsigned char t = 0);
        Array(const std::initializer_list<unsigned char> &t);
        Array(const std::string &t);

        Array(const Array& other);
        Array(Array&& other) noexcept;

        size_t Size() const noexcept;
        size_t Capacity() const noexcept;
        const unsigned char* data() const noexcept;
        unsigned char at(std::size_t index) const;
        bool IsEmpty() const noexcept;

        const unsigned char& Get_by_index(size_t pos) const;
        const unsigned char& Front() const;
        const unsigned char& Back() const;

        void PushBack(unsigned char value);
        void PopBack();
        void PopFront();
        void Clear() noexcept;
        void Resize(std::size_t new_size, unsigned char value = 0);
        void Swap(Array& other) noexcept;
        
        void Set(std::size_t index, unsigned char value);

        Array& operator=(const Array& other);
        Array& operator=(Array&& other) noexcept;

        ~Array() noexcept;
    };
}