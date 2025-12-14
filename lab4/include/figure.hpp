#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

#include "point.hpp"

template <typename T>
class Figure {
public:
    Figure();
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    virtual ~Figure() = default;

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    virtual double Area() const = 0;
    virtual std::unique_ptr<Figure<T>> Clone() const = 0;

    virtual void Read(std::istream& is) = 0;
    virtual void Print(std::ostream& os) const = 0;

    Point<T> Center() const;

    std::size_t VerticesCount() const noexcept;
    const Point<T>& Vertex(std::size_t index) const;

    bool operator==(const Figure& other) const;
    explicit operator double() const { return Area(); }

protected:
    void SetVertices(std::vector<std::unique_ptr<Point<T>>>&& vertices);

    std::vector<std::unique_ptr<Point<T>>> vertices_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.Print(os);
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.Read(is);
    return is;
}

#include "figure.ipp"
