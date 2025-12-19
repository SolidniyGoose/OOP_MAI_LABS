#pragma once
#include "visitor.hpp"
#include "observer.hpp"
#include <mutex>

class BattleVisitor : public Visitor {
private:
    std::mutex coutMutex;
    
public:
    void visit(Dragon& dragon, NPC& other,
              std::vector<std::shared_ptr<Observer>>& observers) override;
    void visit(Bull& bull, NPC& other,
              std::vector<std::shared_ptr<Observer>>& observers) override;
    void visit(Frog& frog, NPC& other,
              std::vector<std::shared_ptr<Observer>>& observers) override;
};