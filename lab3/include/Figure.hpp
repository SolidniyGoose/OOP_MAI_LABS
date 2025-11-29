#pragma once 
#include <cmath>
#include <iostream>
#include "Point.hpp"

bool AreEqual(double a, double b, double epsilon);
double CalculatePolygonArea(const Point* vertices, int count);
Point CalculatePolygonCenter(const Point* vertices, int count);

class Figure {
protected:
    Point* vertices_;
    int vertices_count_;
    
    void setVertices(int count, const Point* vertices = nullptr);
   
public:
    Figure();
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;

    virtual double Area() const = 0;
    virtual void Read(std::istream& input) = 0;
    virtual void Print(std::ostream& output) const = 0;
    virtual Figure* Copy() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    Point Center() const;

    int VerticesCount() const { return vertices_count_; }
    Point& operator[](int index);
    const Point& operator[](int index) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);

    virtual ~Figure();
};