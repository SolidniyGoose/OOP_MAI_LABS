#pragma once
#include <memory>
#include <vector>
#include <random>

class Dragon;
class Bull;
class Frog;
class NPC;
class Observer;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Dragon& dragon, NPC& other,
                      std::vector<std::shared_ptr<Observer>>& observers) = 0;
    virtual void visit(Bull& bull, NPC& other,
                      std::vector<std::shared_ptr<Observer>>& observers) = 0;
    virtual void visit(Frog& frog, NPC& other,
                      std::vector<std::shared_ptr<Observer>>& observers) = 0;
    
    int rollDice();
    
private:
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dice{1, 6};
};