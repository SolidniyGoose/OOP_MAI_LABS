#pragma once
#include <string>
#include <memory>

class IVisitor;

class NPC {
protected:
    std::string name;
    double x{}, y{};
    bool alive{true};
    
public:
    NPC(const std::string& n, double x_, double y_);
    virtual ~NPC() = default;

    virtual std::string type() const = 0;
    
    virtual void accept(IVisitor& visitor) = 0;
    
    double distance(const NPC& other) const;
    bool isAlive() const;
    void die();
    std::string getName() const;
    double getX() const;
    double getY() const;
    
    virtual std::string serialize() const;
};