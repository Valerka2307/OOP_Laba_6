#include "Game.hpp"
#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"
#include "Visitor.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <filesystem>

Game::Game() {
    log_observer = std::make_shared<ObserverLog>();
    console_observer = std::make_shared<ObserverOut>();
}

bool Game::isValidPosition(int x, int y) const {
    return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

void Game::addNPC(NPCType type, int x, int y, const std::string& name) {
    if (!isValidPosition(x, y)) {
        std::cerr << "Error: Invalid position (" << x << ", " << y << "). Allowed range: 0-500." << std::endl;
        return;
    }
    
    auto npc = factory.createNPC(type, x, y);
    if (npc) {
        npc->setName(name);
        npc->subscribe(log_observer);
        npc->subscribe(console_observer);
        npcs.push_back(npc);
        std::cout << "NPC \"" << name << "\" added successfully." << std::endl;
    }
}

void Game::printAllNPCs() const {
    if (npcs.empty()) {
        std::cout << "No NPCs on the map." << std::endl;
        return;
    }
    
    std::cout << "\n=== Current NPCs ===" << std::endl;
    for (const auto& npc : npcs) {
        std::string type_name;
        if (npc->is_robber()) type_name = "Robber";
        else if (npc->is_elf()) type_name = "Elf";
        else if (npc->is_bear()) type_name = "Bear";
        
        std::cout << type_name << " \"" << npc->getName() << "\": (" 
                  << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
    std::cout << "==================\n" << std::endl;
}

void Game::saveToFile(const std::string& filename) {
    std::string filepath = filename;
    if (!std::filesystem::path(filename).is_absolute()) {
        filepath = std::filesystem::current_path().parent_path().string() + "/" + filename;
    }
    
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << " for writing." << std::endl;
        return;
    }
    
    for (const auto& npc : npcs) {
        npc->save(file);
    }
    
    file.close();
    std::cout << "Saved " << npcs.size() << " NPCs to " << filepath << std::endl;
}

void Game::loadFromFile(const std::string& filename) {
    std::string filepath = filename;
    if (!std::filesystem::path(filename).is_absolute()) {
        filepath = std::filesystem::current_path().parent_path().string() + "/" + filename;
    }

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return;
    }

    npcs.clear();

    std::string type_str;
    int x, y;
    std::string name;

    while (file >> type_str >> x >> y) {
        file.ignore();
        std::getline(file, name);

        NPCType type = Unknown;
        if (type_str == "Robber") type = RobberType;
        else if (type_str == "Elf") type = ElfType;
        else if (type_str == "Bear") type = BearType;

        if (type != Unknown) {
            auto npc = factory.createNPC(type, x, y);
            npc->setName(name);
            npc->subscribe(log_observer);
            npc->subscribe(console_observer);
            npcs.push_back(npc);
        }
    }

    std::cout << "Loaded " << npcs.size() << " NPCs from " << filepath << std::endl;
}


void Game::startBattle(size_t distance) {
    if (npcs.size() < 2) {
        std::cout << "Not enough NPCs to start a battle. At least 2 NPCs required." << std::endl;
        return;
    }
    
    std::cout << "\n=== Battle Mode Started (Distance: " << distance << " meters) ===" << std::endl;
    
    // Боевые раунды
    bool battles_occurred = true;
    
    while (battles_occurred && npcs.size() > 1) {
        battles_occurred = false;
        std::vector<bool> alive(npcs.size(), true);
        
        // Каждый NPC сражается с каждым другим в пределах дальности
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!alive[i]) continue;
            
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!alive[j]) continue;
                
                // Проверяем дальность между NPC
                if (npcs[i]->is_close(npcs[j], distance)) {
                    battles_occurred = true;
                    
                    // Выполняем бой: i-ый NPC атакует j-го
                    BattleResult res_attacker = npcs[i]->accept_fight(npcs[j]);
                    BattleResult res_defender = npcs[j]->accept_fight(npcs[i]);
                    
                    if (res_attacker == Victory) {
                        alive[j] = false;  // j-й NPC побежден
                    } else if (res_attacker == Defeat) {
                        alive[i] = false;  // i-й NPC побежден
                    } else if (res_attacker == MutualDestruction) {
                        alive[i] = false;  // оба погибают
                        alive[j] = false;
                    }
                    // BattleResult::PeaceAndLove - оба остаются живы
                }
            }
        }
        
        // Собираем выживших
        std::vector<std::shared_ptr<NPC>> survivors;
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (alive[i]) {
                survivors.push_back(npcs[i]);
            }
        }
        
        npcs = survivors;
    }
    
    std::cout << "=== Battle Ended ===" << std::endl;
    printAllNPCs();
}

size_t Game::getNPCCount() const {
    return npcs.size();
}
