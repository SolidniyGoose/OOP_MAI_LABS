#pragma once
#include <memory>
#include <string>
#include "npc.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(
        const std::string& type,
        const std::string& name,
        double x, double y);
    
    static std::shared_ptr<NPC> createFromString(const std::string& data);
};