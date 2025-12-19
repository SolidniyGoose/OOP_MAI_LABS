#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <random>

class Visitor;
class Observer;

class NPC {
protected:
    std::string name;
    double x{}, y{};
    bool alive{true};
    int moveDistance;
    int killDistance;
    mutable std::mutex mtx;
    
public:
    NPC(const std::string& n, double x_, double y_, int moveDist, int killDist);
    virtual ~NPC() = default;

    virtual std::string type() const = 0;
    virtual void accept(Visitor& visitor, NPC& other,
                       std::vector<std::shared_ptr<Observer>>& observers) = 0;
    virtual char getSymbol() const = 0;

    double distance(const NPC& other) const;
    bool isAlive() const;
    void die();
    std::string getName() const;
    double getX() const;
    double getY() const;
    int getMoveDistance() const;
    int getKillDistance() const;
    
    void move(int maxX, int maxY);
    
    std::string serialize() const;
};