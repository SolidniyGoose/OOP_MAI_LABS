#include "world.hpp"
#include "factory.hpp"
#include "battle_visitor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>

World::World() : running(false) {
    battleVisitor = std::make_shared<BattleVisitor>();
}

World::~World() {
    stopAsyncBattle();
}

void World::addNPC(const std::shared_ptr<NPC>& npc) {
    std::unique_lock<std::shared_mutex> lock(worldMutex);
    npcs.push_back(npc);
}

void World::addObserver(const std::shared_ptr<Observer>& observer) {
    observers.push_back(observer);
}

void World::print() const {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    
    std::cout << "\n=== Список NPC ===" << std::endl;
    for (const auto& npc : npcs) {
        std::cout << npc->type() << " '" << npc->getName() << "' в ("
                  << npc->getX() << ", " << npc->getY() << ") - "
                  << (npc->isAlive() ? "ЖИВ" : "МЕРТВ") << std::endl;
    }
    std::cout << "Всего: " << npcs.size() << " NPC, Живых: " << countAlive() << std::endl;
}

void World::saveToFile(const std::string& filename) const {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << npc->serialize() << std::endl;
        }
    }
    
    std::cout << "Сохранено " << countAlive() << " NPC в " << filename << std::endl;
}

void World::loadFromFile(const std::string& filename) {
    std::unique_lock<std::shared_mutex> lock(worldMutex);
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    npcs.clear();
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        try {
            auto npc = NPCFactory::createFromString(line);
            npcs.push_back(npc);
            count++;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка загрузки NPC: " << e.what() << std::endl;
        }
    }
    
    std::cout << "Загружено " << count << " NPC из " << filename << std::endl;
}

// Синхронная версия боя из 6-й лабы
void World::battle(double range) {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (npcs[i]->isAlive() && npcs[j]->isAlive() &&
                npcs[i]->distance(*npcs[j]) <= range) {
                
                npcs[i]->accept(*battleVisitor, *npcs[j], observers);
                npcs[j]->accept(*battleVisitor, *npcs[i], observers);
            }
        }
    }
    
    removeDeadNPCs();
}

void World::startAsyncBattle(double range) {
    running = true;
}

void World::stopAsyncBattle() {
    running = false;
    battleCV.notify_all();
}

void World::movementTick(int maxX, int maxY) {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    
    // Двигаем NPC
    for (auto& npc : npcs) {
        if (npc->isAlive()) {
            npc->move(maxX, maxY);
        }
    }
    
    // Находим потенциальные бои
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (npcs[i]->isAlive() && npcs[j]->isAlive() &&
                npcs[i]->distance(*npcs[j]) <= npcs[i]->getKillDistance()) {
                
                // Добавляем в очередь
                std::lock_guard<std::mutex> battleLock(battleMutex);
                battleQueue.push({npcs[i], npcs[j]});
                battleCV.notify_one();
            }
        }
    }
}

void World::processBattles() {
    std::unique_lock<std::mutex> lock(battleMutex);
    battleCV.wait(lock, [this]() { return !battleQueue.empty() || !running; });
    
    while (!battleQueue.empty()) {
        auto [npc1, npc2] = battleQueue.front();
        battleQueue.pop();
        lock.unlock();
        
        if (npc1->isAlive() && npc2->isAlive()) {
            npc1->accept(*battleVisitor, *npc2, observers);
            npc2->accept(*battleVisitor, *npc1, observers);
        }
        
        lock.lock();
    }
}

std::vector<std::shared_ptr<NPC>> World::getAliveNPCs() const {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    std::vector<std::shared_ptr<NPC>> alive;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            alive.push_back(npc);
        }
    }
    return alive;
}

void World::removeDeadNPCs() {
    std::unique_lock<std::shared_mutex> lock(worldMutex);
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); }), npcs.end());
}

size_t World::countAlive() const {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    return std::count_if(npcs.begin(), npcs.end(),
        [](const std::shared_ptr<NPC>& npc) { return npc->isAlive(); });
}

size_t World::totalNPCs() const {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    return npcs.size();
}

void World::printMap(int maxX, int maxY) const {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    
    // Создаем сетку для карты
    std::vector<std::vector<char>> grid(maxX + 1, std::vector<char>(maxY + 1, '.'));
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            int x = static_cast<int>(npc->getX());
            int y = static_cast<int>(npc->getY());
            if (x >= 0 && x <= maxX && y >= 0 && y <= maxY) {
                grid[x][y] = npc->getSymbol();
            }
        }
    }
    
    std::cout << "\n=== Карта мира (" << maxX << "x" << maxY << ") ===" << std::endl;
    std::cout << "Легенда: D-Дракон, B-Бык, F-Жаба, .-пусто" << std::endl;
    std::cout << "Живых NPC: " << countAlive() << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    // Выводим карту
    for (int y = 0; y <= maxY; ++y) {
        for (int x = 0; x <= maxX; ++x) {
            std::cout << grid[x][y] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "=========================" << std::endl;
}