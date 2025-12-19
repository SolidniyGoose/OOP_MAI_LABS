#pragma once
#include "world.hpp"
#include <thread>
#include <atomic>
#include <chrono>

class Game {
private:
    World world;
    std::atomic<bool> running;
    std::atomic<bool> stopped;
    
    std::thread movementThread;
    std::thread battleThread;
    std::thread printThread;
    
    // Параметры игры
    int maxX, maxY;
    double battleRange;
    int gameDuration;  // в секундах
    
    // Методы потоков
    void movementLoop();
    void battleLoop();
    void printLoop();
    
public:
    Game(int mapX = 100, int mapY = 100, double range = 10.0);
    ~Game();
    
    // Инициализация
    void initialize(int npcCount = 50);
    void initializeFromFile(const std::string& filename);
    
    void run(int durationSeconds = 30);
    void stop();
    
    void saveGame(const std::string& filename) const;
    void loadGame(const std::string& filename);
    
    // Статистика
    void printStats() const;
};