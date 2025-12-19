#include <gtest/gtest.h>
#include "world.hpp"
#include "factory.hpp"
#include "observer.hpp"
#include "visitor.hpp"

TEST(NPCTest, CreationAndProperties) {
    auto dragon = NPCFactory::create("Dragon", "TestDragon", 100, 100);
    EXPECT_EQ(dragon->type(), "Dragon");
    EXPECT_EQ(dragon->getName(), "TestDragon");
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_EQ(dragon->getX(), 100);
    EXPECT_EQ(dragon->getY(), 100);
}

TEST(NPCTest, DistanceCalculation) {
    auto npc1 = NPCFactory::create("Dragon", "D1", 0, 0);
    auto npc2 = NPCFactory::create("Bull", "B1", 3, 4);
    
    EXPECT_DOUBLE_EQ(npc1->distance(*npc2), 5.0);
}

TEST(NPCTest, InvalidCoordinates) {
    EXPECT_THROW(
        NPCFactory::create("Dragon", "Invalid", 600, 600),
        std::out_of_range
    );
}

TEST(VisitorTest, DragonKillsBull) {
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    auto dragon = NPCFactory::create("Dragon", "Dragon", 0, 0);
    auto bull = NPCFactory::create("Bull", "Bull", 1, 1);
    
    world.addNPC(dragon);
    world.addNPC(bull);
    
    // Проверяем, что оба живы до боя
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_TRUE(bull->isAlive());
    
    world.battle(10.0);
    
    // Дракон должен остаться жив, бык должен умереть
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_EQ(world.countAlive(), 1);
}

TEST(VisitorTest, BullKillsFrog) {
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    auto bull = NPCFactory::create("Bull", "Bull", 0, 0);
    auto frog = NPCFactory::create("Frog", "Frog", 2, 2);
    
    world.addNPC(bull);
    world.addNPC(frog);
    
    world.battle(5.0);
    
    // Бык должен остаться жив, жаба должна умереть
    EXPECT_TRUE(bull->isAlive());
    EXPECT_EQ(world.countAlive(), 1);
}

TEST(VisitorTest, FrogDoesNothing) {
    World world;
    world.addObserver(std::make_shared<ConsoleObserver>());
    
    auto frog = NPCFactory::create("Frog", "Frog1", 0, 0);
    auto dragon = NPCFactory::create("Dragon", "Dragon1", 1, 1);
    
    world.addNPC(frog);
    world.addNPC(dragon);
    
    world.battle(5.0);
    
    // Жаба никого не убивает, оба должны остаться живы
    EXPECT_TRUE(frog->isAlive());
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_EQ(world.countAlive(), 2);
}

TEST(WorldTest, SaveAndLoad) {
    World world1;
    world1.addNPC(NPCFactory::create("Dragon", "SaveTest", 100, 100));
    world1.addNPC(NPCFactory::create("Bull", "BullTest", 200, 200));
    
    world1.saveToFile("test_save.txt");
    
    World world2;
    world2.loadFromFile("test_save.txt");
    
    EXPECT_EQ(world2.totalNPCs(), 2);
    EXPECT_EQ(world2.countAlive(), 2);
}

TEST(ObserverTest, ConsoleObserver) {
    ConsoleObserver observer;
    testing::internal::CaptureStdout();
    observer.onKill("Dragon(Smaug)", "Bull(Taurus)");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Dragon(Smaug) killed Bull(Taurus)") != std::string::npos);
}

TEST(FactoryTest, InvalidType) {
    EXPECT_THROW(
        NPCFactory::create("UnknownType", "Test", 10, 10),
        std::runtime_error
    );
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}