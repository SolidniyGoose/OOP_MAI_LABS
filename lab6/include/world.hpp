#pragma once
#include <vector>
#include <memory>
#include <string>
#include "npc.hpp"
#include "observer.hpp"

class World {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;
    
public:
    void addNPC(const std::shared_ptr<NPC>& npc);
    void addObserver(const std::shared_ptr<Observer>& obs);
    
    // Боевой режим
    void battle(double range);
    
    // Вывести состояния
    void print() const;
    
    // Сохранение и загрузка
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    // Утилиты
    void removeDeadNPCs();
    size_t countAlive() const;
    size_t totalNPCs() const { return npcs.size(); }
    
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const { return npcs; }
    const std::vector<std::shared_ptr<Observer>>& getObservers() const { return observers; }
};