#pragma once
#include "Figure.hpp"

class Rhomb : public Figure {
public:
    Rhomb();
    Rhomb(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Rhomb(const Rhomb& other);
    Rhomb(Rhomb&& other) noexcept;
    
    double Area() const override;
    void Read(std::istream& input) override;
    void Print(std::ostream& output) const override;
    Figure* Copy() const override;
    bool operator==(const Figure& other) const override;
    
    Rhomb& operator=(const Rhomb& other);
    Rhomb& operator=(Rhomb&& other) noexcept;
    
    ~Rhomb() override = default;
};