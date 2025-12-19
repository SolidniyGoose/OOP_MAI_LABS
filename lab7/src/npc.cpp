#include "npc.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <random>
#include <iostream>

NPC::NPC(const std::string& n, double x_, double y_, int moveDist, int killDist)
    : name(n), x(x_), y(y_), moveDistance(moveDist), killDistance(killDist) {
    if (x < 0 || x > 100 || y < 0 || y > 100) {  // Карта 100x100 по условию 7-й лабы
        throw std::out_of_range("Coordinates must be in range [0, 100]");
    }
}

double NPC::distance(const NPC& other) const {
    std::lock_guard<std::mutex> lock(mtx);
    return std::hypot(x - other.x, y - other.y);
}

bool NPC::isAlive() const {
    std::lock_guard<std::mutex> lock(mtx);
    return alive;
}

void NPC::die() {
    std::lock_guard<std::mutex> lock(mtx);
    alive = false;
}

std::string NPC::getName() const {
    std::lock_guard<std::mutex> lock(mtx);
    return name;
}

double NPC::getX() const {
    std::lock_guard<std::mutex> lock(mtx);
    return x;
}

double NPC::getY() const {
    std::lock_guard<std::mutex> lock(mtx);
    return y;
}

int NPC::getMoveDistance() const {
    return moveDistance;
}

int NPC::getKillDistance() const {
    return killDistance;
}

void NPC::move(int maxX, int maxY) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!alive) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-moveDistance, moveDistance);
    
    double dx = dist(gen);
    double dy = dist(gen);
    
    // Проверяем границы
    x = std::max(0.0, std::min(static_cast<double>(maxX), x + dx));
    y = std::max(0.0, std::min(static_cast<double>(maxY), y + dy));
}

std::string NPC::serialize() const {
    std::lock_guard<std::mutex> lock(mtx);
    std::stringstream ss;
    ss << type() << " " << name << " " << x << " " << y;
    return ss.str();
}