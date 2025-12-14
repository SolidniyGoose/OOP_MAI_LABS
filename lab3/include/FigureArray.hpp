#pragma once
#include <cstddef>
#include <stdexcept>

class Figure;

class FigureArray {
private:
    Figure** _data;
    size_t _size;
    size_t _capacity;

public:
    FigureArray();
    FigureArray(const size_t &n, Figure* value = nullptr);
    FigureArray(const FigureArray& other);
    FigureArray(FigureArray&& other) noexcept;
    ~FigureArray();
    
    FigureArray& operator=(const FigureArray& other);
    FigureArray& operator=(FigureArray&& other) noexcept;
    
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool IsEmpty() const noexcept;
    
    Figure*& operator[](size_t index);
    const Figure* operator[](size_t index) const;
    
    Figure*& at(size_t index);
    const Figure* at(size_t index) const;
    
    void PushBack(Figure* value);
    void PopBack();
    void Erase(size_t index);
    void Clear() noexcept;
    void Resize(size_t new_size, Figure* value = nullptr);
    void Swap(FigureArray& other) noexcept;
    
    Figure*& Front();
    const Figure* Front() const;
    Figure*& Back();
    const Figure* Back() const;
};