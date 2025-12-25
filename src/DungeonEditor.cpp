#include "DungeonEditor.hpp"

DungeonEditor::DungeonEditor() {
    std::cout << "Welcome to Balagur Fate 3 Dungeon Editor!" << std::endl;
    
    // Dependency Injection - add observers to game
    game.addObserver(ObserverLog::get());
    game.addObserver(ObserverOut::get());
}

void DungeonEditor::displayMenu() const {
    std::cout << "\n========== Dungeon Editor Menu ==========" << std::endl;
    std::cout << "1. Add NPC" << std::endl;
    std::cout << "2. Print all NPCs" << std::endl;
    std::cout << "3. Save NPCs to file" << std::endl;
    std::cout << "4. Load NPCs from file" << std::endl;
    std::cout << "5. Start battle" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "========================================" << std::endl;
}

void DungeonEditor::displayTypes() const {
    std::cout << "NPC Types: 1=Robber, 2=Elf, 3=Bear" << std::endl;
}

void DungeonEditor::handleAddNPC() {
    displayTypes();
    std::cout << "Enter type (1-3): ";
    int type;
    std::cin >> type;
    
    std::cout << "Enter X coordinate (0-500): ";
    int x;
    std::cin >> x;
    
    std::cout << "Enter Y coordinate (0-500): ";
    int y;
    std::cin >> y;
    
    std::cout << "Enter NPC name: ";
    std::cin.ignore();
    std::string name;
    std::getline(std::cin, name);
    
    NPCType npc_type = Unknown;
    if (type == 1) npc_type = RobberType;
    else if (type == 2) npc_type = ElfType;
    else if (type == 3) npc_type = BearType;
    
    if (npc_type != Unknown) {
        game.addNPC(npc_type, x, y, name);
    } else {
        std::cout << "Invalid type!" << std::endl;
    }
}

void DungeonEditor::handlePrintNPCs() const {
    game.printAllNPCs();
}

void DungeonEditor::handleSaveNPCs() {
    std::cout << "Enter filename (default: npc_data.txt): ";
    std::cin.ignore();
    std::string filename;
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "npc_data.txt";
    game.saveToFile(filename);
}

void DungeonEditor::handleLoadNPCs() {
    std::cout << "Enter filename (default: npc_data.txt): ";
    std::cin.ignore();
    std::string filename;
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "npc_data.txt";
    game.loadFromFile(filename);
}

void DungeonEditor::handleBattle() {
    std::cout << "Enter battle distance (in meters): ";
    size_t distance;
    std::cin >> distance;
    std::cin.ignore();
    game.startBattle(distance);
}

void DungeonEditor::run() {
    int command;
    
    while (true) {
        displayMenu();
        std::cout << "Enter command (1-6): ";
        std::cin >> command;
        
        if (command == 1) {
            handleAddNPC();
        }
        else if (command == 2) {
            handlePrintNPCs();
        }
        else if (command == 3) {
            handleSaveNPCs();
        }
        else if (command == 4) {
            handleLoadNPCs();
        }
        else if (command == 5) {
            handleBattle();
        }
        else if (command == 6) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
}
