#include "npc.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>

NPC::NPC(const std::string& n, double x_, double y_)
    : name(n), x(x_), y(y_) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::out_of_range("Coordinates must be in range [0, 500]");
    }
}

double NPC::distance(const NPC& other) const {
    return std::hypot(x - other.x, y - other.y);
}

bool NPC::isAlive() const { return alive; }
void NPC::die() { alive = false; }
std::string NPC::getName() const { return name; }
double NPC::getX() const { return x; }
double NPC::getY() const { return y; }

std::string NPC::serialize() const {
    std::stringstream ss;
    ss << type() << " " << name << " " << x << " " << y;
    return ss.str();
}