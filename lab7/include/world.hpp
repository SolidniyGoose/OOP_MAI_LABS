#pragma once
#include "npc.hpp"
#include "visitor.hpp"
#include "observer.hpp"
#include <vector>
#include <memory>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <condition_variable>
#include <atomic>

class World {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;
    std::shared_ptr<Visitor> battleVisitor;
    
    mutable std::shared_mutex worldMutex;
    std::mutex battleMutex;
    std::condition_variable battleCV;
    
    std::queue<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> battleQueue;
    std::atomic<bool> running;
    
public:
    World();
    ~World();
    
    void addNPC(const std::shared_ptr<NPC>& npc);
    void addObserver(const std::shared_ptr<Observer>& observer);
    void print() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    void battle(double range);
    
    void startAsyncBattle(double range);
    void stopAsyncBattle();
    void movementTick(int maxX, int maxY);
    void processBattles();
    
    std::vector<std::shared_ptr<NPC>> getAliveNPCs() const;
    void removeDeadNPCs();
    size_t countAlive() const;
    size_t totalNPCs() const;
    
    // Для отображения карты
    void printMap(int maxX, int maxY) const;
};