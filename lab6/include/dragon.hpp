#pragma once
#include "npc.hpp"

class Dragon : public NPC {
public:
    using NPC::NPC;
    std::string type() const override;
    void accept(IVisitor& visitor) override;
};