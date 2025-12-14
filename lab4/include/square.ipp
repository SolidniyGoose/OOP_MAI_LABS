#pragma once

#include "square.hpp"
#include <cmath>
#include <vector>

//Конструкторы

template <typename T>
Square<T>::Square() {
    T half = static_cast<T>(1);

    std::vector<std::unique_ptr<Point<T>>> v;
    v.push_back(std::make_unique<Point<T>>(-half, -half));
    v.push_back(std::make_unique<Point<T>>( half, -half));
    v.push_back(std::make_unique<Point<T>>( half,  half));
    v.push_back(std::make_unique<Point<T>>(-half,  half));

    this->SetVertices(std::move(v));
}

template <typename T>
Square<T>::Square(const Point<T>& center, T side) {
    T half = side / static_cast<T>(2);

    std::vector<std::unique_ptr<Point<T>>> v;
    v.push_back(std::make_unique<Point<T>>(center.x - half, center.y - half));
    v.push_back(std::make_unique<Point<T>>(center.x + half, center.y - half));
    v.push_back(std::make_unique<Point<T>>(center.x + half, center.y + half));
    v.push_back(std::make_unique<Point<T>>(center.x - half, center.y + half));

    this->SetVertices(std::move(v));
}

template <typename T>
Square<T>::Square(const Point<T>& a, const Point<T>& b,
                  const Point<T>& c, const Point<T>& d) {
    std::vector<std::unique_ptr<Point<T>>> v;
    v.push_back(std::make_unique<Point<T>>(a));
    v.push_back(std::make_unique<Point<T>>(b));
    v.push_back(std::make_unique<Point<T>>(c));
    v.push_back(std::make_unique<Point<T>>(d));

    this->SetVertices(std::move(v));
}

template <typename T>
double Square<T>::Area() const {
    const Point<T>& p0 = *this->vertices_[0];
    const Point<T>& p1 = *this->vertices_[1];

    double side = std::hypot(
        static_cast<double>(p1.x - p0.x),
        static_cast<double>(p1.y - p0.y)
    );
    return side * side;
}

template <typename T>
std::unique_ptr<Figure<T>> Square<T>::Clone() const {
    return std::make_unique<Square<T>>(*this);
}

template <typename T>
void Square<T>::Read(std::istream& is) {
    Point<T> center;
    T side;
    is >> center >> side;
    *this = Square<T>(center, side);
}

template <typename T>
void Square<T>::Print(std::ostream& os) const {
    os << "Square: ";
    for (std::size_t i = 0; i < this->vertices_.size(); ++i) {
        os << *this->vertices_[i];
        if (i + 1 < this->vertices_.size()) {
            os << " ";
        }
    }
}
