#include "Trapezoid.hpp"

Trapezoid::Trapezoid() {
    setVertices(4);
    vertices_[0] = Point(0, 0);
    vertices_[1] = Point(4, 0);
    vertices_[2] = Point(3, 2);
    vertices_[3] = Point(1, 2);
}

Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    Point vertices[4] = {p1, p2, p3, p4};
    setVertices(4, vertices);
}

Trapezoid::Trapezoid(const Trapezoid& other) : Figure(other) {}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept : Figure(std::move(other)) {}

double Trapezoid::Area() const {
    return CalculatePolygonArea(vertices_, vertices_count_);
}

void Trapezoid::Read(std::istream& input) {
    Point p1, p2, p3, p4;
    input >> p1 >> p2 >> p3 >> p4;
    Point vertices[4] = {p1, p2, p3, p4};
    setVertices(4, vertices);
}

void Trapezoid::Print(std::ostream& output) const {
    output << "Trapezoid: ";
    for (int i = 0; i < vertices_count_; ++i) {
        output << vertices_[i];
        if (i < vertices_count_ - 1) output << " ";
    }
}

Figure* Trapezoid::Copy() const {
    return new Trapezoid(*this);
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    if (!otherTrapezoid || vertices_count_ != otherTrapezoid->vertices_count_) {
        return false;
    }
    
    for (int i = 0; i < vertices_count_; ++i) {
        if (vertices_[i] != otherTrapezoid->vertices_[i]) {
            return false;
        }
    }
    return true;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    Figure::operator=(other);
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}