#include "Pentagon.hpp"

Pentagon::Pentagon() {
    setVertices(5);
    vertices_[0] = Point(0, 0);
    vertices_[1] = Point(2, 1);
    vertices_[2] = Point(3, 3);
    vertices_[3] = Point(1, 4);
    vertices_[4] = Point(-1, 2);
}

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5) {
    Point vertices[5] = {p1, p2, p3, p4, p5};
    setVertices(5, vertices);
}

Pentagon::Pentagon(const Pentagon& other) : Figure(other) {}

Pentagon::Pentagon(Pentagon&& other) noexcept : Figure(std::move(other)) {}

double Pentagon::Area() const {
    return CalculatePolygonArea(vertices_, vertices_count_);
}

void Pentagon::Read(std::istream& input) {
    Point p1, p2, p3, p4, p5;
    input >> p1 >> p2 >> p3 >> p4 >> p5;
    Point vertices[5] = {p1, p2, p3, p4, p5};
    setVertices(5, vertices);
}

void Pentagon::Print(std::ostream& output) const {
    output << "Pentagon: ";
    for (int i = 0; i < vertices_count_; ++i) {
        output << vertices_[i];
        if (i < vertices_count_ - 1) output << " ";
    }
}

Figure* Pentagon::Copy() const {
    return new Pentagon(*this);
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    if (!otherPentagon || vertices_count_ != otherPentagon->vertices_count_) {
        return false;
    }
    
    for (int i = 0; i < vertices_count_; ++i) {
        if (vertices_[i] != otherPentagon->vertices_[i]) {
            return false;
        }
    }
    return true;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    Figure::operator=(other);
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    Figure::operator=(std::move(other));
    return *this;
}