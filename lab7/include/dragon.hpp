#pragma once
#include "npc.hpp"

class Dragon : public NPC {
public:
    Dragon(const std::string& n, double x_, double y_);
    std::string type() const override;
    void accept(Visitor& visitor, NPC& other,
               std::vector<std::shared_ptr<Observer>>& observers) override;
    char getSymbol() const override;
};