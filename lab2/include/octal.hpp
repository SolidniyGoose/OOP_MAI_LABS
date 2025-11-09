#pragma once

#include "array.hpp"
#include <string>
#include <stdexcept>

namespace octal {
    class Octal {
    private:
        Array::Array digits;

        void removeLeadingZeros();
        void validateDigit(unsigned char digit) const;

    public:
        Octal();
        Octal(const size_t& n, unsigned char t = 0);
        Octal(const std::initializer_list<unsigned char>& t);
        Octal(const std::string& t);
        Octal(const Octal& other);
        Octal(Octal&& other) noexcept;
        ~Octal() noexcept;

        static Octal Add(const Octal& other1, const Octal& other2);
        static Octal Sub(const Octal& other1, const Octal& other2);
        static Octal Multiply(const Octal& other1, const Octal& other2);

        std::string ShowNumber() const;
        void Copy(const Octal& other);

        bool GreaterThen(const Octal& other) const;
        bool LessThen(const Octal& other) const;
        bool Equal(const Octal& other) const;

        size_t size() const noexcept;
        bool isZero() const noexcept;
        unsigned char digitAt(size_t position) const;
    };
}