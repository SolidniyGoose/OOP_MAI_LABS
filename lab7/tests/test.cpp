#include <gtest/gtest.h>
#include "../include/factory.hpp"
#include "../include/world.hpp"
#include "../include/observer.hpp"
#include "../include/game.hpp"
#include <thread>
#include <chrono>
#include <atomic>
#include <fstream>

// Базовые тесты из 6-й лабы (обновленные)
TEST(NPCTest, CreationAndProperties) {
    auto dragon = NPCFactory::create("Dragon", "Smaug", 50, 50);
    EXPECT_EQ(dragon->type(), "Dragon");
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_EQ(dragon->getMoveDistance(), 50);
    EXPECT_EQ(dragon->getKillDistance(), 30);
    
    auto bull = NPCFactory::create("Bull", "Taurus", 60, 60);
    EXPECT_EQ(bull->type(), "Bull");
    EXPECT_EQ(bull->getMoveDistance(), 30);
    EXPECT_EQ(bull->getKillDistance(), 10);
    
    auto frog = NPCFactory::create("Frog", "Kermit", 70, 70);
    EXPECT_EQ(frog->type(), "Frog");
    EXPECT_EQ(frog->getMoveDistance(), 1);
    EXPECT_EQ(frog->getKillDistance(), 10);
}

TEST(NPCTest, DistanceCalculation) {
    auto npc1 = NPCFactory::create("Dragon", "D1", 0, 0);
    auto npc2 = NPCFactory::create("Bull", "B1", 3, 4);
    
    EXPECT_NEAR(npc1->distance(*npc2), 5.0, 0.001);
}

TEST(NPCTest, Movement) {
    auto npc = NPCFactory::create("Dragon", "Test", 50, 50);
    
    // Многократно двигаем NPC и проверяем границы
    for (int i = 0; i < 10; ++i) {
        npc->move(100, 100);
        auto [x, y] = npc->getPosition();
        EXPECT_GE(x, 0);
        EXPECT_LE(x, 100);
        EXPECT_GE(y, 0);
        EXPECT_LE(y, 100);
    }
}

TEST(NPCTest, InvalidCoordinates) {
    EXPECT_THROW(
        NPCFactory::create("Dragon", "Invalid", 600, 600),
        std::out_of_range
    );
}

TEST(FactoryTest, InvalidType) {
    EXPECT_THROW(
        NPCFactory::create("UnknownType", "Test", 10, 10),
        std::runtime_error
    );
}

TEST(WorldTest, AddAndRemoveNPCs) {
    World world;
    EXPECT_EQ(world.countAlive(), 0);
    
    world.addNPC(NPCFactory::create("Dragon", "D1", 10, 10));
    world.addNPC(NPCFactory::create("Bull", "B1", 20, 20));
    
    EXPECT_EQ(world.countAlive(), 2);
    
    // Убиваем NPC и проверяем удаление
    auto npcs = world.getAliveNPCs();
    npcs[0]->die();
    world.removeDeadNPCs();
    
    EXPECT_EQ(world.countAlive(), 1);
}

TEST(WorldTest, SaveAndLoad) {
    World world1;
    world1.addObserver(std::make_shared<ConsoleObserver>());
    
    world1.addNPC(NPCFactory::create("Dragon", "SaveTest", 100, 100));
    world1.addNPC(NPCFactory::create("Bull", "BullTest", 150, 150));
    world1.addNPC(NPCFactory::create("Frog", "FrogTest", 200, 200));
    
    world1.saveToFile("test_save_lab7.txt");
    
    World world2;
    world2.addObserver(std::make_shared<ConsoleObserver>());
    world2.loadFromFile("test_save_lab7.txt");
    
    EXPECT_EQ(world2.countAlive(), 3);
    
    // Проверяем, что загруженные NPC имеют правильные координаты
    auto npcs = world2.getAliveNPCs();
    EXPECT_EQ(npcs.size(), 3);
    
    // Удаляем временный файл
    std::remove("test_save_lab7.txt");
}

// Тесты для многопоточности 7-й лабы
TEST(MultithreadingTest, ThreadSafety) {
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    // Создаем несколько NPC
    for (int i = 0; i < 10; ++i) {
        world.addNPC(NPCFactory::createRandom("NPC_" + std::to_string(i), 100, 100));
    }
    
    // Запускаем движение в отдельном потоке
    std::thread movementThread([&world]() {
        for (int i = 0; i < 10; ++i) {
            world.movementTick(100, 100);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    
    // Запускаем обработку боев в отдельном потоке
    std::thread battleThread([&world]() {
        world.startAsyncBattle(15.0);
        for (int i = 0; i < 5; ++i) {
            world.processBattles();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        world.stopAsyncBattle();
    });
    
    movementThread.join();
    battleThread.join();
    
    // Проверяем, что мир в корректном состоянии
    EXPECT_LE(world.countAlive(), 10); // Могли быть убийства
    EXPECT_GE(world.countAlive(), 0);
}

TEST(MultithreadingTest, ConcurrentAccess) {
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    // Добавляем NPC из нескольких потоков
    std::vector<std::thread> threads;
    const int threadCount = 5;
    const int npcsPerThread = 10;
    
    for (int t = 0; t < threadCount; ++t) {
        threads.emplace_back([&world, t]() {
            for (int i = 0; i < npcsPerThread; ++i) {
                auto npc = NPCFactory::createRandom(
                    "Thread" + std::to_string(t) + "_NPC" + std::to_string(i), 100, 100);
                world.addNPC(npc);
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Проверяем, что все NPC добавлены
    EXPECT_EQ(world.totalNPCs(), threadCount * npcsPerThread);
}

TEST(GameTest, GameInitialization) {
    Game game(50, 50, 10.0);
    game.initialize(20);
    
    // Создаем временный мир для проверки
    World testWorld;
    testWorld.addObserver(std::make_shared<ConsoleObserver>());
    
    // Проверяем, что инициализация создала NPC
    // (В реальной игре нужно получить доступ к миру, но он приватный)
    // Для теста можно сохранить и загрузить
    game.saveGame("game_test_save.txt");
    testWorld.loadFromFile("game_test_save.txt");
    
    EXPECT_EQ(testWorld.countAlive(), 20);
    
    std::remove("game_test_save.txt");
}

TEST(GameTest, ShortGameSession) {
    // Тестируем короткую игровую сессию
    Game game(30, 30, 10.0);
    game.initialize(10);
    
    // Запускаем игру на 1 секунду
    auto start = std::chrono::steady_clock::now();
    
    // В отдельном потоке, чтобы не блокировать тест
    std::thread gameThread([&game]() {
        game.run(1);
    });
    
    gameThread.join();
    
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    
    // Игра должна завершиться примерно через 1 секунду
    EXPECT_GE(duration, 1);
    EXPECT_LE(duration, 2); // С небольшим запасом
}

TEST(ObserverTest, ConsoleObserver) {
    ConsoleObserver observer;
    
    // Тестируем вывод (можно перенаправить cout)
    testing::internal::CaptureStdout();
    observer.onKill("Дракон(Smaug)", "Бык(Taurus)", 5, 3);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Дракон(Smaug)") != std::string::npos);
    EXPECT_TRUE(output.find("Бык(Taurus)") != std::string::npos);
    EXPECT_TRUE(output.find("атака: 5") != std::string::npos);
    EXPECT_TRUE(output.find("защита: 3") != std::string::npos);
}

TEST(ObserverTest, FileObserver) {
    const std::string testFile = "test_observer_log.txt";
    FileObserver observer(testFile);
    
    observer.onKill("Дракон(Smaug)", "Бык(Taurus)", 6, 2);
    observer.onMove("Жаба(Kermit)", 25.5, 30.5);
    
    // Проверяем, что файл создан и содержит записи
    std::ifstream file(testFile);
    ASSERT_TRUE(file.is_open());
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_TRUE(content.find("Дракон(Smaug)") != std::string::npos);
    EXPECT_TRUE(content.find("Жаба(Kermit)") != std::string::npos);
    
    file.close();
    std::remove(testFile.c_str());
}

// Тест на правильность правил боя с кубиками
TEST(BattleTest, DiceMechanics) {
    // Создаем мир с наблюдателем
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    // Создаем NPC для теста
    auto dragon = NPCFactory::create("Dragon", "TestDragon", 0, 0);
    auto bull = NPCFactory::create("Bull", "TestBull", 1, 1); // В пределах дистанции
    
    world.addNPC(dragon);
    world.addNPC(bull);
    
    // Запускаем бой
    world.battle(10.0);
    
    // Проверяем, что либо оба живы, либо один убит
    // (зависит от броска кубика)
    bool dragonAlive = dragon->isAlive();
    bool bullAlive = bull->isAlive();
    
    // Не могут быть оба мертвы после одного раунда
    EXPECT_FALSE(!dragonAlive && !bullAlive);
    
    // Дракон может убить быка, бык не может убить дракона
    if (!bullAlive) {
        // Если бык мертв, дракон должен быть жив
        EXPECT_TRUE(dragonAlive);
    }
}

// Тест на многократные движения
TEST(MovementTest, BoundaryCheck) {
    auto npc = NPCFactory::create("Dragon", "BoundaryTest", 0, 0);
    
    // Двигаем NPC много раз, проверяем границы
    for (int i = 0; i < 100; ++i) {
        npc->move(10, 10);
        auto [x, y] = npc->getPosition();
        
        EXPECT_GE(x, 0);
        EXPECT_LE(x, 10);
        EXPECT_GE(y, 0);
        EXPECT_LE(y, 10);
    }
}

// Тест на производительность многопоточности
TEST(PerformanceTest, ConcurrentMovement) {
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    // Создаем много NPC
    const int npcCount = 100;
    for (int i = 0; i < npcCount; ++i) {
        world.addNPC(NPCFactory::createRandom("NPC_" + std::to_string(i), 100, 100));
    }
    
    // Замеряем время синхронного движения
    auto startSync = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) {
        world.movementTick(100, 100);
    }
    auto endSync = std::chrono::high_resolution_clock::now();
    auto syncDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
        endSync - startSync).count();
    
    // В реальном приложении здесь бы сравнивали с многопоточной версией
    // Для теста просто проверяем, что операция завершается
    EXPECT_GT(world.countAlive(), 0);
    EXPECT_LE(syncDuration, 1000); // Не должно занимать больше секунды
}

// Тест на обработку исключений
TEST(ExceptionTest, InvalidOperations) {
    World world;
    
    // Попытка загрузить несуществующий файл
    EXPECT_THROW(
        world.loadFromFile("non_existent_file.txt"),
        std::runtime_error
    );
    
    // Попытка сохранить в недоступную директорию
    EXPECT_THROW(
        world.saveToFile("/nonexistent/path/file.txt"),
        std::runtime_error
    );
}

// Тест на корректность сериализации
TEST(SerializationTest, NPCStringRepresentation) {
    auto dragon = NPCFactory::create("Dragon", "SerializeTest", 123.45, 67.89);
    std::string serialized = dragon->serialize();
    
    // Ожидаемый формат: "Dragon SerializeTest 123.45 67.89"
    EXPECT_TRUE(serialized.find("Dragon") != std::string::npos);
    EXPECT_TRUE(serialized.find("SerializeTest") != std::string::npos);
    EXPECT_TRUE(serialized.find("123.45") != std::string::npos);
    EXPECT_TRUE(serialized.find("67.89") != std::string::npos);
    
    // Десериализация через фабрику
    auto deserialized = NPCFactory::createFromString(serialized);
    EXPECT_EQ(deserialized->type(), "Dragon");
    EXPECT_EQ(deserialized->getName(), "SerializeTest");
    
    auto [x, y] = deserialized->getPosition();
    EXPECT_NEAR(x, 123.45, 0.001);
    EXPECT_NEAR(y, 67.89, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    std::cout << "========================================" << std::endl;
    std::cout << "Тесты для лабораторной работы №7" << std::endl;
    std::cout << "Вариант 20: Дракон, Бык, Жаба" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return RUN_ALL_TESTS();
}