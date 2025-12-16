#pragma once

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "NPC.hpp"
#include "Factory.hpp"
#include "Visitor.hpp"
#include "Observer.hpp"

class Game {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    Factory factory;
    std::shared_ptr<ObserverLog> log_observer;
    std::shared_ptr<ObserverOut> console_observer;
    
public:
    Game();
    
    void addNPC(NPCType type, int x, int y, const std::string& name);
    void printAllNPCs() const;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    void startBattle(size_t distance);
    
    bool isValidPosition(int x, int y) const;
    size_t getNPCCount() const;
};
