#pragma once

#include <iostream>

template <typename T>
class Point;

template <typename T>
std::istream& operator>>(std::istream&, Point<T>&);

template <typename T>
std::ostream& operator<<(std::ostream&, const Point<T>&);

template <typename T>
bool operator==(const Point<T>&, const Point<T>&);

template <typename T>
bool operator!=(const Point<T>&, const Point<T>&);

template <typename T>
class Point {
public:
    T x, y;

    Point();
    Point(T x_val, T y_val);

    friend std::istream& operator>> <>(std::istream&, Point<T>&);
    friend std::ostream& operator<< <>(std::ostream&, const Point<T>&);
    friend bool operator== <>(const Point<T>&, const Point<T>&);
    friend bool operator!= <>(const Point<T>&, const Point<T>&);
};

#include "point.ipp"
