#pragma once

#include "figure.hpp"

template <typename T>
Figure<T>::Figure() = default;

template <typename T>
Figure<T>::Figure(const Figure& other) {
    vertices_.reserve(other.vertices_.size());
    for (const auto& v : other.vertices_) {
        vertices_.push_back(std::make_unique<Point<T>>(*v));
    }
}

template <typename T>
Figure<T>::Figure(Figure&& other) noexcept
    : vertices_(std::move(other.vertices_)) {}

template <typename T>
Figure<T>& Figure<T>::operator=(const Figure& other) {
    if (this != &other) {
        vertices_.clear();
        vertices_.reserve(other.vertices_.size());
        for (const auto& v : other.vertices_) {
            vertices_.push_back(std::make_unique<Point<T>>(*v));
        }
    }
    return *this;
}

template <typename T>
Figure<T>& Figure<T>::operator=(Figure&& other) noexcept {
    if (this != &other) {
        vertices_ = std::move(other.vertices_);
    }
    return *this;
}

template <typename T>
std::size_t Figure<T>::VerticesCount() const noexcept {
    return vertices_.size();
}

template <typename T>
const Point<T>& Figure<T>::Vertex(std::size_t index) const {
    if (index >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    return *vertices_[index];
}

template <typename T>
Point<T> Figure<T>::Center() const {
    if (vertices_.empty()) {
        return Point<T>();
    }

    T cx{};
    T cy{};
    for (const auto& v : vertices_) {
        cx += v->x;
        cy += v->y;
    }

    return Point<T>(
        cx / static_cast<T>(vertices_.size()),
        cy / static_cast<T>(vertices_.size())
    );
}

template <typename T>
bool Figure<T>::operator==(const Figure& other) const {
    if (vertices_.size() != other.vertices_.size()) {
        return false;
    }

    for (std::size_t i = 0; i < vertices_.size(); ++i) {
        if (*vertices_[i] != *other.vertices_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void Figure<T>::SetVertices(std::vector<std::unique_ptr<Point<T>>>&& vertices) {
    vertices_ = std::move(vertices);
}
