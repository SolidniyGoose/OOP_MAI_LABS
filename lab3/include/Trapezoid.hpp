#pragma once
#include "Figure.hpp"

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    
    double Area() const override;
    void Read(std::istream& input) override;
    void Print(std::ostream& output) const override;
    Figure* Copy() const override;
    bool operator==(const Figure& other) const override;
    
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    
    ~Trapezoid() override = default;
};