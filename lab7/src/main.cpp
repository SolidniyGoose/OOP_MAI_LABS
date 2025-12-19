#include "game.hpp"
#include "factory.hpp"  // ДОБАВИТЬ ЭТОТ ИНКЛЮД!
#include "world.hpp"    // ДОБАВИТЬ ЭТОТ ИНКЛЮД!
#include "observer.hpp" // ДОБАВИТЬ ЭТОТ ИНКЛЮД!
#include <iostream>
#include <csignal>
#include <atomic>

std::atomic<bool> gRunning{true};

void signalHandler(int signal) {
    gRunning = false;
    std::cout << "\nПолучен сигнал прерывания. Завершение..." << std::endl;
}

int main() {
    // Устанавливаем обработчик сигналов
    std::signal(SIGINT, signalHandler);
    
    const int MAP_X = 100;
    const int MAP_Y = 100;
    const int NPC_COUNT = 50;
    const int GAME_DURATION = 30; // секунды
    
    std::cout << "============================================================" << std::endl;
    std::cout << "       Лабораторная работа №7: Асинхронное программирование" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "Вариант: 20 (Дракон, Бык, Жаба)" << std::endl;
    std::cout << "Правила боя из 6-й лабораторной:" << std::endl;
    std::cout << "  • Дракон ест быков" << std::endl;
    std::cout << "  • Бык толчет жаб" << std::endl;
    std::cout << "  • Жаба спасается как может" << std::endl;
    std::cout << std::endl;
    std::cout << "Параметры движения из таблицы 7-й лабораторной:" << std::endl;
    std::cout << "  • Дракон: расстояние хода = 50, убийства = 30" << std::endl;
    std::cout << "  • Бык: расстояние хода = 30, убийства = 10" << std::endl;
    std::cout << "  • Жаба: расстояние хода = 1, убийства = 10" << std::endl;
    std::cout << std::endl;
    std::cout << "Механика боя:" << std::endl;
    std::cout << "  • Каждый NPC бросает 6-гранный кубик для атаки и защиты" << std::endl;
    std::cout << "  • Убийство происходит если атака > защиты" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "Параметры игры:" << std::endl;
    std::cout << "  • Размер карты: " << MAP_X << "x" << MAP_Y << std::endl;
    std::cout << "  • Количество NPC: " << NPC_COUNT << std::endl;
    std::cout << "  • Длительность игры: " << GAME_DURATION << " секунд" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "Управление:" << std::endl;
    std::cout << "  • Карта выводится каждую секунду" << std::endl;
    std::cout << "  • Нажмите Ctrl+C для досрочного завершения" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    // Демонстрация сохранения/загрузки из 6-й лабы
    std::cout << "\n=== Демонстрация сохранения/загрузки ===" << std::endl;
    {
        World testWorld;
        testWorld.addObserver(std::make_shared<ConsoleObserver>());
        testWorld.addNPC(NPCFactory::create("Dragon", "TestDragon", 10, 10));
        testWorld.addNPC(NPCFactory::create("Bull", "TestBull", 20, 20));
        testWorld.addNPC(NPCFactory::create("Frog", "TestFrog", 30, 30));
        testWorld.saveToFile("test_save.txt");
        testWorld.print();
    }
    
    {
        World loadedWorld;
        loadedWorld.addObserver(std::make_shared<ConsoleObserver>());
        loadedWorld.loadFromFile("test_save.txt");
        std::cout << "\nЗагруженный мир:" << std::endl;
        loadedWorld.print();
    }
    
    // Основная игра
    Game game(MAP_X, MAP_Y, 15.0);
    game.initialize(NPC_COUNT);
    game.run(GAME_DURATION);
    
    return 0;
}