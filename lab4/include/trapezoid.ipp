// trapezoid.ipp
#pragma once

#include "trapezoid.hpp"
#include <cmath>
#include <vector>
#include <memory>

template <typename T>
Trapezoid<T>::Trapezoid() {
    std::vector<std::unique_ptr<Point<T>>> vertices;
    vertices.push_back(std::make_unique<Point<T>>(0, 0));
    vertices.push_back(std::make_unique<Point<T>>(4, 0));
    vertices.push_back(std::make_unique<Point<T>>(3, 2));
    vertices.push_back(std::make_unique<Point<T>>(1, 2));
    this->SetVertices(std::move(vertices));
}

template <typename T>
Trapezoid<T>::Trapezoid(const Point<T>& a, const Point<T>& b,
                        const Point<T>& c, const Point<T>& d) {
    std::vector<std::unique_ptr<Point<T>>> vertices;
    vertices.push_back(std::make_unique<Point<T>>(a));
    vertices.push_back(std::make_unique<Point<T>>(b));
    vertices.push_back(std::make_unique<Point<T>>(c));
    vertices.push_back(std::make_unique<Point<T>>(d));
    this->SetVertices(std::move(vertices));
}

template <typename T>
double Trapezoid<T>::Area() const {
    const auto& v = this->vertices_;
    if (v.size() != 4) return 0.0;
    
    double area = 0.0;
    for (size_t i = 0; i < 4; ++i) {
        const Point<T>& p1 = *v[i];
        const Point<T>& p2 = *v[(i + 1) % 4];
        area += static_cast<double>(p1.x * p2.y - p2.x * p1.y);
    }
    
    return std::abs(area) / 2.0;
}

template <typename T>
std::unique_ptr<Figure<T>> Trapezoid<T>::Clone() const {
    return std::make_unique<Trapezoid<T>>(*this);
}

template <typename T>
void Trapezoid<T>::Read(std::istream& is) {
    Point<T> a, b, c, d;
    is >> a >> b >> c >> d;
    *this = Trapezoid<T>(a, b, c, d);
}

template <typename T>
void Trapezoid<T>::Print(std::ostream& os) const {
    os << "Trapezoid: ";
    for (size_t i = 0; i < this->vertices_.size(); ++i) {
        os << *this->vertices_[i];
        if (i + 1 < this->vertices_.size()) os << " ";
    }
}