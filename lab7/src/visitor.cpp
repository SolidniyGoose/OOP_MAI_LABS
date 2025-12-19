#include "visitor.hpp"
#include "dragon.hpp"
#include "bull.hpp"
#include "frog.hpp"
#include "npc.hpp"
#include "observer.hpp"
#include <iostream>
#include <mutex>

int Visitor::rollDice() {
    return dice(gen);
}

class BattleVisitor : public Visitor {
private:
    std::mutex coutMutex;
    
public:
    void visit(Dragon& dragon, NPC& other,
              std::vector<std::shared_ptr<Observer>>& observers) override {
        std::lock_guard<std::mutex> lock(coutMutex);
        if (!other.isAlive()) return;
        
        // Дракон атакует быка
        if (other.type() == "Bull") {
            int attack = rollDice();
            int defense = rollDice();
            
            if (attack > defense) {
                other.die();
                for (auto& obs : observers) {
                    obs->onKill(dragon.getName() + "(Dragon)",
                               other.getName() + "(Bull)",
                               attack, defense);
                }
            } else {
                std::cout << "[БОЙ] Дракон " << dragon.getName() 
                          << " не смог убить быка " << other.getName()
                          << " (атака: " << attack << " <= защита: " << defense << ")" << std::endl;
            }
        }
    }
    
    void visit(Bull& bull, NPC& other,
              std::vector<std::shared_ptr<Observer>>& observers) override {
        std::lock_guard<std::mutex> lock(coutMutex);
        if (!other.isAlive()) return;
        
        // Бык атакует жабу
        if (other.type() == "Frog") {
            int attack = rollDice();
            int defense = rollDice();
            
            if (attack > defense) {
                other.die();
                for (auto& obs : observers) {
                    obs->onKill(bull.getName() + "(Bull)",
                               other.getName() + "(Frog)",
                               attack, defense);
                }
            } else {
                std::cout << "[БОЙ] Бык " << bull.getName() 
                          << " не смог убить жабу " << other.getName()
                          << " (атака: " << attack << " <= защита: " << defense << ")" << std::endl;
            }
        }
    }
    
    void visit(Frog& frog, NPC& other,
              std::vector<std::shared_ptr<Observer>>& observers) override {
        // Жаба никого не убивает
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[БОЙ] Жаба " << frog.getName() << " спасается как может!" << std::endl;
    }
};