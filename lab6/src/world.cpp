#include "world.hpp"
#include "factory.hpp"
#include "visitor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void World::addNPC(const std::shared_ptr<NPC>& npc) {
    npcs.push_back(npc);
}

void World::addObserver(const std::shared_ptr<Observer>& obs) {
    observers.push_back(obs);
}

void World::battle(double range) {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            auto& npc1 = npcs[i];
            auto& npc2 = npcs[j];
            
            if (!npc1->isAlive() || !npc2->isAlive()) continue;
            
            // Проверяем дистанцию
            if (npc1->distance(*npc2) <= range) {
                // NPC1 атакует NPC2 через Visitor
                BattleVisitor visitor1(npc2.get(), observers);
                npc1->accept(visitor1);
                
                // NPC2 атакует NPC1 через Visitor
                BattleVisitor visitor2(npc1.get(), observers);
                npc2->accept(visitor2);
            }
        }
    }
    
    removeDeadNPCs();
}

void World::print() const {
    std::cout << "=== Current World State ===" << std::endl;
    std::cout << "Total NPCs: " << npcs.size() << std::endl;
    std::cout << "Alive: " << countAlive() << std::endl;
    std::cout << "--------------------------" << std::endl;
    
    for (const auto& npc : npcs) {
        std::cout << "- " << npc->type() << " '" << npc->getName() 
                  << "' at (" << npc->getX() << ", " << npc->getY() << ") - "
                  << (npc->isAlive() ? "ALIVE" : "DEAD") << std::endl;
    }
    std::cout << "==========================" << std::endl;
}

void World::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << npc->serialize() << std::endl;
        }
    }
    
    std::cout << "Saved " << countAlive() << " NPCs to " << filename << std::endl;
}

void World::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    npcs.clear();
    std::string line;
    size_t loadedCount = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        try {
            auto npc = NPCFactory::createFromString(line);
            npcs.push_back(npc);
            loadedCount++;
        } catch (const std::exception& e) {
            std::cerr << "Error loading NPC from line: " << line << std::endl;
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    std::cout << "Loaded " << loadedCount << " NPCs from " << filename << std::endl;
}

void World::removeDeadNPCs() {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
                      [](const std::shared_ptr<NPC>& npc) {
                          return !npc->isAlive();
                      }),
        npcs.end()
    );
}

size_t World::countAlive() const {
    return std::count_if(npcs.begin(), npcs.end(),
                        [](const std::shared_ptr<NPC>& npc) {
                            return npc->isAlive();
                        });
}