#pragma once

#include "figure.hpp"

template <typename T>
class Square : public Figure<T> {
public:
    Square();
    Square(const Point<T>& center, T side);
    Square(const Point<T>& a, const Point<T>& b,
           const Point<T>& c, const Point<T>& d);

    double Area() const override;
    std::unique_ptr<Figure<T>> Clone() const override;

    void Read(std::istream& is) override;
    void Print(std::ostream& os) const override;
};

#include "square.ipp"
