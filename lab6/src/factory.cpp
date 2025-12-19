#include "factory.hpp"
#include "dragon.hpp"
#include "bull.hpp"
#include "frog.hpp"
#include <sstream>
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::create(
    const std::string& type,
    const std::string& name,
    double x, double y) {
    
    if (type == "Dragon") return std::make_shared<Dragon>(name, x, y);
    if (type == "Bull")   return std::make_shared<Bull>(name, x, y);
    if (type == "Frog")   return std::make_shared<Frog>(name, x, y);
    
    throw std::runtime_error("Unknown NPC type: " + type);
}

std::shared_ptr<NPC> NPCFactory::createFromString(const std::string& data) {
    std::istringstream iss(data);
    std::string type, name;
    double x, y;
    
    if (iss >> type >> name >> x >> y) {
        return create(type, name, x, y);
    }
    
    throw std::runtime_error("Invalid NPC data format: " + data);
}