#include "frog.hpp"
#include "visitor.hpp"

std::string Frog::type() const { return "Frog"; }

void Frog::accept(IVisitor& visitor) {
    visitor.visit(*this);
}