#pragma once

#include "figure.hpp"

template <typename T>
class Rectangle : public Figure<T> {
public:
    Rectangle();
    Rectangle(const Point<T>& center, T width, T height);
    Rectangle(const Point<T>& a, const Point<T>& b,
              const Point<T>& c, const Point<T>& d);

    double Area() const override;
    std::unique_ptr<Figure<T>> Clone() const override;

    void Read(std::istream& is) override;
    void Print(std::ostream& os) const override;
};

#include "rectangle.ipp"
