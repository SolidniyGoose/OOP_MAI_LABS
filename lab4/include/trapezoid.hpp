#pragma once

#include "figure.hpp"

template <typename T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid();
    Trapezoid(const Point<T>& a, const Point<T>& b,
              const Point<T>& c, const Point<T>& d);

    double Area() const override;
    std::unique_ptr<Figure<T>> Clone() const override;

    void Read(std::istream& is) override;
    void Print(std::ostream& os) const override;
};

#include "trapezoid.ipp"