#include "dragon.hpp"
#include "visitor.hpp"
#include "observer.hpp"
#include <iostream>

Dragon::Dragon(const std::string& n, double x_, double y_)
    : NPC(n, x_, y_, 50, 30) {}

std::string Dragon::type() const { return "Dragon"; }

char Dragon::getSymbol() const { return 'D'; }

void Dragon::accept(Visitor& visitor, NPC& other,
                   std::vector<std::shared_ptr<Observer>>& observers) {
    visitor.visit(*this, other, observers);
}