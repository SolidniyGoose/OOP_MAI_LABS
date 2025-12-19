#include "bull.hpp"
#include "visitor.hpp"
#include "observer.hpp"
#include <iostream>

Bull::Bull(const std::string& n, double x_, double y_)
    : NPC(n, x_, y_, 30, 10) {}  // Из таблицы: ход=30, убийство=10

std::string Bull::type() const { return "Bull"; }

char Bull::getSymbol() const { return 'B'; }

void Bull::accept(Visitor& visitor, NPC& other,
                 std::vector<std::shared_ptr<Observer>>& observers) {
    visitor.visit(*this, other, observers);
}