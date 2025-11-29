#include "Figure.hpp"
#include <cmath>
#include <algorithm>

bool AreEqual(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}

double CalculatePolygonArea(const Point* vertices, int count) {
    if (count < 3) {
        return 0.0;
    }
    double area = 0.0;
    for (int i = 0; i < count; ++i) {
        int j = (i + 1) % count;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    
    return std::abs(area) / 2.0;
}

Point CalculatePolygonCenter(const Point* vertices, int count) {
    if (count == 0) {
        return Point();
    }
    double center_x = 0.0, center_y = 0.0;
    for (int i = 0; i < count; ++i) {
        center_x += vertices[i].x;
        center_y += vertices[i].y;
    }
    
    return Point(center_x / count, center_y / count);
}

Figure::Figure() : vertices_(nullptr), vertices_count_(0) {}

Figure::Figure(const Figure& other) : vertices_count_(other.vertices_count_) {
    if (vertices_count_ > 0) {
        vertices_ = new Point[vertices_count_];
        for (int i = 0; i < vertices_count_; ++i) {
            vertices_[i] = other.vertices_[i];
        }
    } else {
        vertices_ = nullptr;
    }
}

Figure::Figure(Figure&& other) noexcept 
    : vertices_(other.vertices_), vertices_count_(other.vertices_count_) {
    other.vertices_ = nullptr;
    other.vertices_count_ = 0;
}

Figure::~Figure() {
    delete[] vertices_;
}

void Figure::setVertices(int count, const Point* vertices) {
    delete[] vertices_;
    
    vertices_count_ = count;
    if (count > 0) {
        vertices_ = new Point[count];
        if (vertices != nullptr) {
            for (int i = 0; i < count; ++i) {
                vertices_[i] = vertices[i];
            }
        }
    } else {
        vertices_ = nullptr;
    }
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        delete[] vertices_;
        
        vertices_count_ = other.vertices_count_;
        if (vertices_count_ > 0) {
            vertices_ = new Point[vertices_count_];
            for (int i = 0; i < vertices_count_; ++i) {
                vertices_[i] = other.vertices_[i];
            }
        } else {
            vertices_ = nullptr;
        }
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        delete[] vertices_;
        
        vertices_ = other.vertices_;
        vertices_count_ = other.vertices_count_;
        
        other.vertices_ = nullptr;
        other.vertices_count_ = 0;
    }
    return *this;
}

Point Figure::Center() const {
    return CalculatePolygonCenter(vertices_, vertices_count_);
}

Point& Figure::operator[](int index) {
    if (index < 0 || index >= vertices_count_) {
        throw std::out_of_range("Index out of range");
    }
    return vertices_[index];
}

const Point& Figure::operator[](int index) const {
    if (index < 0 || index >= vertices_count_) {
        throw std::out_of_range("Index out of range");
    }
    return vertices_[index];
}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.Print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.Read(is);
    return is;
}