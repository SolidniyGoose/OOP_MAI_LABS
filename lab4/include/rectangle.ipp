#pragma once

#include "rectangle.hpp"
#include <cmath>
#include <vector>

// Конструкторы

template <typename T>
Rectangle<T>::Rectangle() {
    T w = static_cast<T>(2);
    T h = static_cast<T>(1);

    std::vector<std::unique_ptr<Point<T>>> v;
    v.push_back(std::make_unique<Point<T>>(-w/2, -h/2));
    v.push_back(std::make_unique<Point<T>>( w/2, -h/2));
    v.push_back(std::make_unique<Point<T>>( w/2,  h/2));
    v.push_back(std::make_unique<Point<T>>(-w/2,  h/2));

    this->SetVertices(std::move(v));
}

template <typename T>
Rectangle<T>::Rectangle(const Point<T>& center, T width, T height) {
    T hw = width  / static_cast<T>(2);
    T hh = height / static_cast<T>(2);

    std::vector<std::unique_ptr<Point<T>>> v;
    v.push_back(std::make_unique<Point<T>>(center.x - hw, center.y - hh));
    v.push_back(std::make_unique<Point<T>>(center.x + hw, center.y - hh));
    v.push_back(std::make_unique<Point<T>>(center.x + hw, center.y + hh));
    v.push_back(std::make_unique<Point<T>>(center.x - hw, center.y + hh));

    this->SetVertices(std::move(v));
}

template <typename T>
Rectangle<T>::Rectangle(const Point<T>& a, const Point<T>& b,
                        const Point<T>& c, const Point<T>& d) {
    std::vector<std::unique_ptr<Point<T>>> v;
    v.push_back(std::make_unique<Point<T>>(a));
    v.push_back(std::make_unique<Point<T>>(b));
    v.push_back(std::make_unique<Point<T>>(c));
    v.push_back(std::make_unique<Point<T>>(d));

    this->SetVertices(std::move(v));
}

template <typename T>
double Rectangle<T>::Area() const {
    const Point<T>& p0 = *this->vertices_[0];
    const Point<T>& p1 = *this->vertices_[1];
    const Point<T>& p2 = *this->vertices_[2];

    double width = std::hypot(
        static_cast<double>(p1.x - p0.x),
        static_cast<double>(p1.y - p0.y)
    );
    double height = std::hypot(
        static_cast<double>(p2.x - p1.x),
        static_cast<double>(p2.y - p1.y)
    );
    return width * height;
}

template <typename T>
std::unique_ptr<Figure<T>> Rectangle<T>::Clone() const {
    return std::make_unique<Rectangle<T>>(*this);
}

template <typename T>
void Rectangle<T>::Read(std::istream& is) {
    Point<T> center;
    T w, h;
    is >> center >> w >> h;
    *this = Rectangle<T>(center, w, h);
}

template <typename T>
void Rectangle<T>::Print(std::ostream& os) const {
    os << "Rectangle: ";
    for (std::size_t i = 0; i < this->vertices_.size(); ++i) {
        os << *this->vertices_[i];
        if (i + 1 < this->vertices_.size()) {
            os << " ";
        }
    }
}
