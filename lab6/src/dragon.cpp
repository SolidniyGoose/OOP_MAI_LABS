#include "dragon.hpp"
#include "visitor.hpp"

std::string Dragon::type() const { return "Dragon"; }

void Dragon::accept(IVisitor& visitor) {
    visitor.visit(*this);
}