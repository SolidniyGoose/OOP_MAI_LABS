#include "game.hpp"
#include "factory.hpp"
#include "observer.hpp"
#include <iostream>

Game::Game(int mapX, int mapY, double range) 
    : maxX(mapX), maxY(mapY), battleRange(range), running(false), stopped(false) {
    
    world.addObserver(std::make_shared<ConsoleObserver>());
    world.addObserver(std::make_shared<FileObserver>("game_log.txt"));
}

Game::~Game() {
    stop();
}

void Game::initialize(int npcCount) {
    std::cout << "Создание " << npcCount << " NPC..." << std::endl;
    
    for (int i = 0; i < npcCount; ++i) {
        auto npc = NPCFactory::createRandom("NPC_" + std::to_string(i), maxX, maxY);
        world.addNPC(npc);
    }
    
    std::cout << "Создано " << world.totalNPCs() << " NPC" << std::endl;
}

void Game::initializeFromFile(const std::string& filename) {
    world.loadFromFile(filename);
}

void Game::movementLoop() {
    while (running) {
        world.movementTick(maxX, maxY);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Частота движения
    }
}

void Game::battleLoop() {
    while (running) {
        world.processBattles();
    }
}

void Game::printLoop() {
    while (running) {
        world.printMap(maxX, maxY);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::run(int durationSeconds) {
    running = true;
    stopped = false;
    gameDuration = durationSeconds;
    
    std::cout << "\n=== Запуск игры на " << durationSeconds << " секунд ===" << std::endl;
    std::cout << "Запуск потоков..." << std::endl;
    
    // Запускаем потоки
    movementThread = std::thread(&Game::movementLoop, this);
    battleThread = std::thread(&Game::battleLoop, this);
    printThread = std::thread(&Game::printLoop, this);
    
    std::cout << "Все потоки запущены. Игра началась!" << std::endl;
    
    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(
           std::chrono::steady_clock::now() - startTime).count() < durationSeconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    stop();
    
    printStats();
}

void Game::stop() {
    if (!running) return;
    
    running = false;
    stopped = true;
    
    // Останавливаем мир
    world.stopAsyncBattle();
    
    if (movementThread.joinable()) movementThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (printThread.joinable()) printThread.join();
    
    std::cout << "Все потоки остановлены." << std::endl;
}

void Game::saveGame(const std::string& filename) const {
    world.saveToFile(filename);
}

void Game::loadGame(const std::string& filename) {
    world.loadFromFile(filename);
}

void Game::printStats() const {
    auto survivors = world.getAliveNPCs();
    
    std::cout << "\n=== Игра завершена! ===" << std::endl;
    std::cout << "Длительность: " << gameDuration << " секунд" << std::endl;
    std::cout << "Выживших NPC: " << survivors.size() << std::endl;
    std::cout << "\nСписок выживших:" << std::endl;
    std::cout << "----------------" << std::endl;
    
    int dragonCount = 0, bullCount = 0, frogCount = 0;
    for (const auto& npc : survivors) {
        std::cout << npc->type() << " '" << npc->getName() << "' в ("
                  << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        
        if (npc->type() == "Dragon") dragonCount++;
        else if (npc->type() == "Bull") bullCount++;
        else if (npc->type() == "Frog") frogCount++;
    }
    
    std::cout << "\nСтатистика:" << std::endl;
    std::cout << "Драконов: " << dragonCount << std::endl;
    std::cout << "Быков: " << bullCount << std::endl;
    std::cout << "Жаб: " << frogCount << std::endl;
}