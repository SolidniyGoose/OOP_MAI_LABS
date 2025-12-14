#pragma once
#include <iostream>

class Point {
public:
    double x, y;
    
    Point();
    Point(double x, double y);
    Point(const Point& other);
    Point(Point&& other);
    
    Point& operator=(const Point& other);
    
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    ~Point() = default;
};