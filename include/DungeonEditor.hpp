#pragma once

#include <iostream>
#include <string>
#include "Game.hpp"
#include "Observer.hpp"

class DungeonEditor {
private:
    Game game;
    
    void displayMenu() const;
    void displayTypes() const;
    void handleAddNPC();
    void handlePrintNPCs() const;
    void handleSaveNPCs();
    void handleLoadNPCs();
    void handleBattle();
    
public:
    DungeonEditor();
    void run();
};
