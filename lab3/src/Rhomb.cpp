#include "Rhomb.hpp"

Rhomb::Rhomb() {
    setVertices(4);
    vertices_[0] = Point(0, 0);
    vertices_[1] = Point(2, 3);
    vertices_[2] = Point(4, 0);
    vertices_[3] = Point(2, -3);
}

Rhomb::Rhomb(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    Point vertices[4] = {p1, p2, p3, p4};
    setVertices(4, vertices);
}

Rhomb::Rhomb(const Rhomb& other) : Figure(other) {}

Rhomb::Rhomb(Rhomb&& other) noexcept : Figure(std::move(other)) {}

double Rhomb::Area() const {
    return CalculatePolygonArea(vertices_, vertices_count_);
}

void Rhomb::Read(std::istream& input) {
    Point p1, p2, p3, p4;
    input >> p1 >> p2 >> p3 >> p4;
    Point vertices[4] = {p1, p2, p3, p4};
    setVertices(4, vertices);
}

void Rhomb::Print(std::ostream& output) const {
    output << "Rhomb: ";
    for (int i = 0; i < vertices_count_; ++i) {
        output << vertices_[i];
        if (i < vertices_count_ - 1) output << " ";
    }
}

Figure* Rhomb::Copy() const {
    return new Rhomb(*this);
}

bool Rhomb::operator==(const Figure& other) const {
    const Rhomb* otherRhomb = dynamic_cast<const Rhomb*>(&other);
    if (!otherRhomb || vertices_count_ != otherRhomb->vertices_count_) {
        return false;
    }
    
    for (int i = 0; i < vertices_count_; ++i) {
        if (vertices_[i] != otherRhomb->vertices_[i]) {
            return false;
        }
    }
    return true;
}

Rhomb& Rhomb::operator=(const Rhomb& other) {
    Figure::operator=(other);
    return *this;
}

Rhomb& Rhomb::operator=(Rhomb&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}