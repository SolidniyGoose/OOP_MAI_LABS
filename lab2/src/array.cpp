#include <array.hpp>

namespace Array{
    Array::Array() : _data(nullptr), _size(0), _capacity(0){}

    Array::Array(const size_t &n, unsigned char value) : _size(n), _capacity(n){
        if (n > 0) {
            try {
                _data = new unsigned char[n];
                for (size_t i = 0; i < n; ++i){
                    _data[i] = value;
                }
            }
            catch (const std::bad_alloc& e){
                _size = 0;
                _capacity = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }

    Array::Array(const std::initializer_list<unsigned char> &t) : _size(t.size()), _capacity(t.size()) {
        if (_size > 0){
            try {
                _data = new unsigned char[_size];
                size_t i = 0;
                for (const unsigned char& letter : t){
                    _data[i] = letter;
                    i++;
                }
            } catch (const std::bad_alloc& e){
                _size = 0;
                _capacity = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }

    Array::Array(const std::string &t) : _size(t.size()), _capacity(t.size()) {
        if (_size > 0){
            try {
                _data = new unsigned char[_size];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = static_cast<unsigned char>(t[i]);
                }
            } catch (const std::bad_alloc& e){
                _size = 0;
                _capacity = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }

    Array::Array(const Array& other) : _size(other._size), _capacity(other._capacity) {
        if (_size > 0) {
            try {
                _data = new unsigned char[_size];
                for (size_t i = 0; i < _size; ++i) {
                    _data[i] = other._data[i];
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

    Array::Array(Array&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data) {
        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
    }

    size_t Array::Size() const noexcept {
        return _size;
    }

    size_t Array::Capacity() const noexcept {
        return _capacity;
    }

    const unsigned char* Array::data() const noexcept {
        return _data;
    }

    unsigned char Array::at(std::size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    bool Array::IsEmpty() const noexcept {
        return _size == 0;
    }

    const unsigned char& Array::Get_by_index(size_t pos) const {
        if (pos >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[pos];
    }

    const unsigned char& Array::Front() const {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[0];
    }

    const unsigned char& Array::Back() const {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[_size - 1];
    }

    void Array::PushBack(unsigned char value) {
        if (_size >= _capacity) {
            std::size_t new_capacity;
            if (_capacity == 0) {
                new_capacity = 1;
            } else {
                new_capacity = _capacity * 2;
            }
            
            try {
                unsigned char* new_data = new unsigned char[new_capacity];
                if (_data != nullptr) {
                    for (std::size_t i = 0; i < _size; ++i) {
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


    void Array::PopBack() {
        if (_size > 0) {
            _size--;
        }
    }

    void Array::PopFront() {
        if (_size > 0) {
            for (std::size_t i = 1; i < _size; ++i) {
                _data[i - 1] = _data[i];
            }
            _size--;
        }
    }

    void Array::Clear() noexcept {
        if (_data != nullptr) {
            delete[] _data;
            _data = nullptr;
        }
        _size = 0;
        _capacity = 0;
    }

    void Array::Resize(std::size_t new_size, unsigned char value) {
        if (new_size <= _size) {
            _size = new_size;
        } else if (new_size <= _capacity) {
            for (std::size_t i = _size; i < new_size; ++i) {
                _data[i] = value;
            }
            _size = new_size;
        } else {
            std::size_t new_capacity = new_size;
            unsigned char* new_data = new unsigned char[new_capacity];

            if (_data != nullptr) {
                for (std::size_t i = 0; i < _size; ++i) {
                    new_data[i] = _data[i];
                }
                delete[] _data;
            }
            
            for (std::size_t i = _size; i < new_size; ++i) {
                new_data[i] = value;
            }
            
            _data = new_data;
            _size = new_size;
            _capacity = new_capacity;
        }
    }

    void Array::Swap(Array& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    void Array::Set(std::size_t index, unsigned char value) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        _data[index] = value;
    }

    Array& Array::operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }
        
        Array temp(other);
        Swap(temp);
        return *this;
    }

    Array& Array::operator=(Array&& other) noexcept {
        if (this != &other) {
            Clear();
            _size = other._size;
            _capacity = other._capacity;
            _data = other._data;
            
            other._size = 0;
            other._capacity = 0;
            other._data = nullptr;
        }
        return *this;
    }
    
    Array::~Array() noexcept {
        delete[] _data;
    }
}