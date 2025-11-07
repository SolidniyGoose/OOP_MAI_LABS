#include "octal.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace octal {
    void Octal::validateDigit(unsigned char digit) const {
        if (digit > 7) {
            throw std::invalid_argument("Invalid octal digit");
        }
    }

    void Octal::removeLeadingZeros() {
        while (digits.Size() > 1 && digits.Back() == 0) {
            digits.PopBack();
        }
        if (digits.Size() == 0) {
            digits.PushBack(0);
        }
    }

    Octal::Octal() : digits(1, 0) {}

    Octal::Octal(const size_t& n, unsigned char t) : digits(n, t) {
        if (t > 7) {
            throw std::invalid_argument("Invalid octal digit");
        }
        removeLeadingZeros();
    }


    Octal::Octal(const std::initializer_list<unsigned char>& digitList) : digits(digitList) {
        for (auto digit : digitList) {
            validateDigit(digit);
        }
        removeLeadingZeros();
    }

    Octal::Octal(const std::string& str) {
        if (str.empty()) {
            digits.PushBack(0);
            return;
        }
        
        for (auto it = str.rbegin(); it != str.rend(); ++it) {
            char c = *it;
            if (c < '0' || c > '7') {
                throw std::invalid_argument("Invalid octal digit");
            }
            digits.PushBack(static_cast<unsigned char>(c - '0'));
        }
        removeLeadingZeros();
    }

    Octal::Octal(const Octal& other) : digits(other.digits) {
        if (digits.Size() == 0) {
            digits.PushBack(0);
        }
    }

    Octal::Octal(Octal&& other) noexcept : digits(std::move(other.digits)) {
        if (other.digits.Size() == 0) {
            other.digits.PushBack(0);
        }
    }

    Octal::~Octal() noexcept {
    }

    Octal Octal::Add(const Octal& other1, const Octal& other2) {
        Octal result;
        result.digits.Clear();
        
        size_t maxSize = std::max(other1.digits.Size(), other2.digits.Size());
        unsigned char carry = 0;
        
        for (size_t i = 0; i < maxSize || carry > 0; ++i) {
            unsigned char sum = other1.digitAt(i) + other2.digitAt(i) + carry;
            result.digits.PushBack(sum % 8);
            carry = sum / 8;
        }
        
        result.removeLeadingZeros();
        return result;
    }

    Octal Octal::Sub(const Octal& other1, const Octal& other2) {
        if (other1.LessThen(other2)) {
            throw std::underflow_error("Negative result");
        }
        
        Octal result;
        result.digits.Clear();
        
        size_t maxSize = other1.digits.Size();
        unsigned char borrow = 0;
        
        for (size_t i = 0; i < maxSize; ++i) {
            int digit1 = other1.digitAt(i);
            int digit2 = other2.digitAt(i);
            int diff = digit1 - digit2 - borrow;
            
            if (diff < 0) {
                diff += 8;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.PushBack(static_cast<unsigned char>(diff));
        }
        
        if (borrow > 0) {
            throw std::underflow_error("Negative result detected during subtraction");
        }
        
        result.removeLeadingZeros();
        return result;
    }

    Octal Octal::Multiply(const Octal& other1, const Octal& other2) {
        if (other1.isZero() || other2.isZero()) {
            return Octal();
        }
        
        size_t resultSize = other1.digits.Size() + other2.digits.Size();
        Array::Array resultArray(resultSize, 0);
        
        for (size_t i = 0; i < other2.digits.Size(); ++i) {
            unsigned char carry = 0;
            for (size_t j = 0; j < other1.digits.Size(); ++j) {
                size_t pos = i + j;
                unsigned char product = resultArray.at(pos) + other2.digitAt(i) * other1.digitAt(j) + carry;
                resultArray.Set(pos, product % 8);
                carry = product / 8;
            }
            
            if (carry > 0) {
                size_t pos = i + other1.digits.Size();
                while (carry > 0 && pos < resultSize) {
                    unsigned char sum = resultArray.at(pos) + carry;
                    resultArray.Set(pos, sum % 8);
                    carry = sum / 8;
                    pos++;
                }
            }
        }
        
        Octal result;
        result.digits = resultArray;
        result.removeLeadingZeros();
        return result;
    }

    std::string Octal::ShowNumber() const {
        if (isZero()) {
            return "0";
        }
        
        std::string result;
        for (size_t i = digits.Size(); i > 0; --i) {
            result += std::to_string(static_cast<int>(digits.at(i - 1)));
        }
        return result;
    }

    void Octal::Copy(const Octal& other) {
        digits = other.digits;
    }

    bool Octal::GreaterThen(const Octal& other) const {
        if (digits.Size() != other.digits.Size()) {
            return digits.Size() > other.digits.Size();
        }
        
        for (size_t i = digits.Size(); i > 0; --i) {
            size_t idx = i - 1;
            if (digits.at(idx) != other.digits.at(idx)) {
                return digits.at(idx) > other.digits.at(idx);
            }
        }
        return false;
    }

    bool Octal::LessThen(const Octal& other) const {
        if (digits.Size() != other.digits.Size()) {
            return digits.Size() < other.digits.Size();
        }
        
        for (size_t i = digits.Size(); i > 0; --i) {
            size_t idx = i - 1;
            if (digits.at(idx) != other.digits.at(idx)) {
                return digits.at(idx) < other.digits.at(idx);
            }
        }
        return false;
    }

    bool Octal::Equal(const Octal& other) const {
        if (digits.Size() != other.digits.Size()) {
            return false;
        }
        
        for (size_t i = 0; i < digits.Size(); ++i) {
            if (digits.at(i) != other.digits.at(i)) {
                return false;
            }
        }
        return true;
    }

    size_t Octal::size() const noexcept {
        return digits.Size();
    }

    bool Octal::isZero() const noexcept {
        return digits.Size() == 1 && digits.at(0) == 0;
    }

    unsigned char Octal::digitAt(size_t position) const {
        if (position >= digits.Size()) {
            return 0;
        }
        return digits.at(position);
    }
}