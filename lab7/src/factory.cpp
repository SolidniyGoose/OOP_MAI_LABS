#include "factory.hpp"
#include "dragon.hpp"
#include "bull.hpp"
#include "frog.hpp"
#include <sstream>
#include <stdexcept>

std::random_device NPCFactory::rd;
std::mt19937 NPCFactory::gen(NPCFactory::rd());

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
    
    throw std::runtime_error("Invalid NPC data: " + data);
}

std::shared_ptr<NPC> NPCFactory::createRandom(const std::string& name, int maxX, int maxY) {
    static std::uniform_int_distribution<> typeDist(0, 2);
    static std::uniform_int_distribution<> coordDist(0, maxX);
    
    std::string type;
    switch (typeDist(gen)) {
        case 0: type = "Dragon"; break;
        case 1: type = "Bull"; break;
        case 2: type = "Frog"; break;
    }
    
    double x = coordDist(gen);
    double y = coordDist(gen);
    
    return create(type, name, x, y);
}