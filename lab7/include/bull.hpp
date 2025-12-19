#pragma once
#include "npc.hpp"

class Bull : public NPC {
public:
    Bull(const std::string& n, double x_, double y_);
    std::string type() const override;
    void accept(Visitor& visitor, NPC& other,
               std::vector<std::shared_ptr<Observer>>& observers) override;
    char getSymbol() const override;
};