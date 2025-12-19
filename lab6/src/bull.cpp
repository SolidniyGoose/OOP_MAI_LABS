#include "bull.hpp"
#include "visitor.hpp"

std::string Bull::type() const { return "Bull"; }

void Bull::accept(IVisitor& visitor) {
    visitor.visit(*this);
}