#include "FigureArray.hpp"
#include "Figure.hpp"

FigureArray::FigureArray() : _data(nullptr), _size(0), _capacity(0) {}

FigureArray::FigureArray(const size_t &n, Figure* value) : _size(n), _capacity(n) {
    if (n > 0) {
        try {
            _data = new Figure*[n];
            for (size_t i = 0; i < n; ++i) {
                _data[i] = value ? value->Copy() : nullptr;
            }
        } catch (const std::bad_alloc& e) {
            _size = 0;
            _capacity = 0;
            _data = nullptr;
            throw;
        }
    } else {
        _data = nullptr;
    }
}

FigureArray::FigureArray(const FigureArray& other) : _size(other._size), _capacity(other._capacity) {
    if (_size > 0) {
        try {
            _data = new Figure*[_size];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i] ? other._data[i]->Copy() : nullptr;
            }
        } catch (const std::bad_alloc& e) {
            _size = 0;
            _capacity = 0;
            _data = nullptr;
            throw;
        }
    } else {
        _data = nullptr;
    }
}

FigureArray::FigureArray(FigureArray&& other) noexcept 
    : _data(other._data), _size(other._size), _capacity(other._capacity) {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

FigureArray::~FigureArray() {
    for (size_t i = 0; i < _size; ++i) {
        delete _data[i];
    }
    delete[] _data;
}

FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this == &other) {
        return *this;
    }
    
    FigureArray temp(other);
    Swap(temp);
    return *this;
}

FigureArray& FigureArray::operator=(FigureArray&& other) noexcept {
    if (this != &other) {
        Clear();
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

size_t FigureArray::Size() const noexcept {
    return _size;
}

size_t FigureArray::Capacity() const noexcept {
    return _capacity;
}

bool FigureArray::IsEmpty() const noexcept {
    return _size == 0;
}

Figure*& FigureArray::operator[](size_t index) {
    return _data[index];
}

const Figure* FigureArray::operator[](size_t index) const {
    return _data[index];
}

Figure*& FigureArray::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

const Figure* FigureArray::at(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

void FigureArray::PushBack(Figure* value) {
    if (_size >= _capacity) {
        size_t new_capacity;
        if (_capacity == 0) {
            new_capacity = 1;
        } else {
            new_capacity = _capacity * 2;
        }
        
        try {
            Figure** new_data = new Figure*[new_capacity];
            
            for (size_t i = 0; i < new_capacity; ++i) {
                new_data[i] = nullptr;
            }
            
            if (_data != nullptr) {
                for (size_t i = 0; i < _size; ++i) {
                    new_data[i] = _data[i];
                }
                delete[] _data;
            }
            _data = new_data;
            _capacity = new_capacity;
        } catch (const std::bad_alloc& e) {
            throw;
        }
    }
    
    _data[_size] = value;
    _size++;
}

void FigureArray::PopBack() {
    if (_size > 0) {
        delete _data[_size - 1];
        _size--;
    }
}

void FigureArray::Erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    
    delete _data[index];
    
    for (size_t i = index; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
    }
    _size--;
}

void FigureArray::Clear() noexcept {
    for (size_t i = 0; i < _size; ++i) {
        delete _data[i];
    }
    
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
    _size = 0;
    _capacity = 0;
}

void FigureArray::Resize(size_t new_size, Figure* value) {
    if (new_size <= _size) {
        for (size_t i = new_size; i < _size; ++i) {
            delete _data[i];
            _data[i] = nullptr;
        }
        _size = new_size;
    } else if (new_size <= _capacity) {
        for (size_t i = _size; i < new_size; ++i) {
            _data[i] = value ? value->Copy() : nullptr;
        }
        _size = new_size;
    } else {
        size_t new_capacity = new_size;
        Figure** new_data = new Figure*[new_capacity];

        for (size_t i = 0; i < new_capacity; ++i) {
            new_data[i] = nullptr;
        }
        
        if (_data != nullptr) {
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = _data[i];
            }
            delete[] _data;
        }
        
        for (size_t i = _size; i < new_size; ++i) {
            new_data[i] = value ? value->Copy() : nullptr;
        }
        
        _data = new_data;
        _size = new_size;
        _capacity = new_capacity;
    }
}
void FigureArray::Swap(FigureArray& other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
}

Figure*& FigureArray::Front() {
    if (_size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return _data[0];
}

const Figure* FigureArray::Front() const {
    if (_size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return _data[0];
}

Figure*& FigureArray::Back() {
    if (_size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return _data[_size - 1];
}

const Figure* FigureArray::Back() const {
    if (_size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return _data[_size - 1];
}