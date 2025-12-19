#include "world.hpp"
#include "factory.hpp"
#include "observer.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

void demoScenario1() {
    std::cout << "\n=== Demo 1: Basic Battle ===" << std::endl;
    World world;
    
    // Добавляем наблюдателей
    world.addObserver(std::make_shared<ConsoleObserver>());
    world.addObserver(std::make_shared<FileObserver>("battle_log.txt"));
    
    // Создаем NPC через Factory
    world.addNPC(NPCFactory::create("Dragon", "Smaug", 100, 100));
    world.addNPC(NPCFactory::create("Bull", "Taurus", 105, 100));  // В пределах дистанции
    world.addNPC(NPCFactory::create("Frog", "Kermit", 200, 200));  // Далеко
    
    std::cout << "\nInitial state:" << std::endl;
    world.print();
    
    // Запускаем бой с дистанцией 10 метров
    std::cout << "\nStarting battle with range 10m..." << std::endl;
    world.battle(10.0);
    
    std::cout << "\nAfter battle:" << std::endl;
    world.print();
}

void demoScenario2() {
    std::cout << "\n=== Demo 2: Bull vs Frog ===" << std::endl;
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    world.addNPC(NPCFactory::create("Bull", "Brave", 50, 50));
    world.addNPC(NPCFactory::create("Frog", "Green", 55, 50));
    world.addNPC(NPCFactory::create("Frog", "Blue", 60, 50));
    
    std::cout << "\nInitial state:" << std::endl;
    world.print();
    
    std::cout << "\nStarting battle with range 8m..." << std::endl;
    world.battle(8.0);
    
    std::cout << "\nAfter battle:" << std::endl;
    world.print();
}

void demoScenario3() {
    std::cout << "\n=== Demo 3: File Operations ===" << std::endl;
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    // Создаем несколько NPC
    for (int i = 0; i < 10; ++i) {
        double x = rand() % 500;
        double y = rand() % 500;
        
        switch (i % 3) {
            case 0:
                world.addNPC(NPCFactory::create("Dragon", 
                    "Dragon_" + std::to_string(i), x, y));
                break;
            case 1:
                world.addNPC(NPCFactory::create("Bull",
                    "Bull_" + std::to_string(i), x, y));
                break;
            case 2:
                world.addNPC(NPCFactory::create("Frog",
                    "Frog_" + std::to_string(i), x, y));
                break;
        }
    }
    
    std::cout << "\nCreated world with " << world.totalNPCs() << " NPCs" << std::endl;
    world.print();
    
    // Сохраняем в файл
    try {
        world.saveToFile("dungeon_save.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error saving: " << e.what() << std::endl;
    }
    
    // Загружаем из файла в новый мир
    World loadedWorld;
    loadedWorld.addObserver(std::make_shared<ConsoleObserver>());
    
    try {
        loadedWorld.loadFromFile("dungeon_save.txt");
        std::cout << "\nLoaded world:" << std::endl;
        loadedWorld.print();
    } catch (const std::exception& e) {
        std::cerr << "Error loading: " << e.what() << std::endl;
    }
    
    std::cout << "\nStarting battle in loaded world with range 50m..." << std::endl;
    loadedWorld.battle(50.0);
    loadedWorld.print();
}

void testInvalidNPC() {
    std::cout << "\n=== Test: Invalid NPC Creation ===" << std::endl;
    try {
        auto npc = NPCFactory::create("Unknown", "Test", 10, 10);
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Correctly caught exception: " << e.what() << std::endl;
    }
    
    try {
        auto npc = NPCFactory::create("Dragon", "InvalidCoord", 600, 600);
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Correctly caught exception: " << e.what() << std::endl;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    std::cout << "=========================================" << std::endl;
    std::cout << " RPG Dungeon Editor - Variant 20" << std::endl;
    std::cout << " NPC Types: Dragon, Bull, Frog" << std::endl;
    std::cout << " Rules:" << std::endl;
    std::cout << "   - Dragon eats Bulls" << std::endl;
    std::cout << "   - Bull stomps Frogs" << std::endl;
    std::cout << "   - Frogs escape as they can" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    demoScenario1();
    demoScenario2();
    demoScenario3();
    testInvalidNPC();
    
    std::cout << "\n=== Program Complete ===" << std::endl;
    std::cout << "Check 'battle_log.txt' for battle history." << std::endl;
    
    return 0;
}