#pragma once
#include "npc.hpp"
#include <memory>
#include <string>
#include <random>

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(
        const std::string& type,
        const std::string& name,
        double x, double y);
    
    static std::shared_ptr<NPC> createFromString(const std::string& data);
    static std::shared_ptr<NPC> createRandom(const std::string& name, int maxX, int maxY);
    
private:
    static std::random_device rd;
    static std::mt19937 gen;
};