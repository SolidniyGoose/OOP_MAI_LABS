#pragma once
#include "point.hpp"

template <typename T>
Point<T>::Point() : x{}, y{} {}

template <typename T>
Point<T>::Point(T x_val, T y_val) : x(x_val), y(y_val) {}

template <typename T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template <typename T>
bool operator==(const Point<T>& lhs, const Point<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T>
bool operator!=(const Point<T>& lhs, const Point<T>& rhs) {
    return !(lhs == rhs);
}
