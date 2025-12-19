#pragma once
#include <memory>
#include <vector>

class Dragon;
class Bull;
class Frog;
class NPC;
class Observer;

class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void visit(Dragon& dragon) = 0;
    virtual void visit(Bull& bull) = 0;
    virtual void visit(Frog& frog) = 0;
};

class BattleVisitor : public IVisitor {
private:
    NPC* opponent;  // Второй NPC в битве
    std::vector<std::shared_ptr<Observer>>& observers;
    
public:
    BattleVisitor(NPC* opp, std::vector<std::shared_ptr<Observer>>& obs);
    
    void visit(Dragon& dragon) override;
    void visit(Bull& bull) override;
    void visit(Frog& frog) override;
};