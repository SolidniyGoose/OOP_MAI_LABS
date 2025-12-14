#pragma once
#include "Figure.hpp"

class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;
    
    double Area() const override;
    void Read(std::istream& input) override;
    void Print(std::ostream& output) const override;
    Figure* Copy() const override;
    bool operator==(const Figure& other) const override;
    
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
    
    ~Pentagon() override = default;
};