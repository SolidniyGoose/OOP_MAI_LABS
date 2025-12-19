#include "visitor.hpp"
#include "dragon.hpp"
#include "bull.hpp"
#include "frog.hpp"
#include "npc.hpp"
#include "observer.hpp"
#include <iostream>

BattleVisitor::BattleVisitor(NPC* opp, std::vector<std::shared_ptr<Observer>>& obs) 
    : opponent(opp), observers(obs) {}

void BattleVisitor::visit(Dragon& dragon) {
    // Дракон атакует быка
    if (opponent && opponent->type() == "Bull" && opponent->isAlive()) {
        opponent->die();
        for (auto& obs : observers) {
            obs->onKill(dragon.getName() + "(Dragon)", 
                       opponent->getName() + "(Bull)");
        }
    }
}

void BattleVisitor::visit(Bull& bull) {
    // Бык атакует жабу
    if (opponent && opponent->type() == "Frog" && opponent->isAlive()) {
        opponent->die();
        for (auto& obs : observers) {
            obs->onKill(bull.getName() + "(Bull)", 
                       opponent->getName() + "(Frog)");
        }
    }
}

void BattleVisitor::visit(Frog& frog) {
    // Жаба никого не атакует
}