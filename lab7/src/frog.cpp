#include "frog.hpp"
#include "visitor.hpp"
#include "observer.hpp"
#include <iostream>

Frog::Frog(const std::string& n, double x_, double y_)
    : NPC(n, x_, y_, 1, 10) {}

std::string Frog::type() const { return "Frog"; }

char Frog::getSymbol() const { return 'F'; }

void Frog::accept(Visitor& visitor, NPC& other,
                 std::vector<std::shared_ptr<Observer>>& observers) {
    visitor.visit(*this, other, observers);
}